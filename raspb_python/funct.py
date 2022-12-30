#v 0.1

import global_vars as global_vars
import RPi.GPIO as GPIO
import serial
import time
import msgbuilder as msb
import interface

import random


baud_rate = 57600
ser = serial.Serial('/dev/serial0', baud_rate, timeout=0)
ser.flush()

def Scleanup():
    ser.close()


def Gcleanup(spec=99):
    GPIO.setwarnings(False)
    if spec == 99:
        GPIO.cleanup()
    else:
        GPIO.cleanup(spec)


def Ginitialise(ctrlpin, hands):
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(ctrlpin, GPIO.OUT, initial=0)
    GPIO.setup(hands, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    # init automatic mode switch
    # GPIO.setup(18,GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    # init led pins
    GPIO.setup(9, GPIO.OUT, initial=0)
    GPIO.setup(10, GPIO.OUT, initial=0)
    GPIO.setup(22, GPIO.OUT, initial=0)
    # update auto_switch value based on switch position

    if (GPIO.input(24) == True):
        global_vars.auto_switch = 1
    elif (GPIO.input(24) == False):
        global_vars.auto_switch = 0
    
    #set up 36V detection pin
    GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    
    # set up a debug pin
    GPIO.setup(21, GPIO.OUT, initial=0)


def parse_config_file():
    f = open(global_vars.folder_path+"robot_config.txt", "r")
    config_lines = f.readlines()
    if len(config_lines) == 0:
        global_vars.selected_program = ""
        return 1
    global_vars.selected_program = config_lines[0].strip()
    print("found set config file "+global_vars.selected_program)
    if interface.check_if_folder_exists(global_vars.selected_program) == 1:
        #folder matching the set program in robot_config does not exist
        global_vars.selected_program = ""
    interface.create_program_selection_widgets(0)


def check_serial():
    # if there are outgoing messages and there is no repeat request, send them
    if ((len(global_vars.coms_out) > 0) and
        (global_vars.master_receiving == False) and
        (check_serial.request_repeat == 0)
        ):
        #print("attempting coms_send()")
        if coms_send() == 0:
            #message sent succesfully , remove it
            del global_vars.coms_out[0]

    # if not busy, check if there is a request for repeat
    # or if any slave wants to transmit
    if (global_vars.master_receiving == False):
        
        if check_serial.request_repeat == 1:
            print("repeating request")
            repeat_message = 0
            if check_serial.responding_slave == 1:
                repeat_message = "1.5"   
            elif check_serial.responding_slave == 2:
                repeat_message = "2.5"
            elif check_serial.responding_slave == 3:
                repeat_message = "3.5"
            if prpMsg(repeat_message) == "Sent ok!":
                #reset request_repeat flag
                check_serial.request_repeat = 0
            else:
                print("REPEAT failed")
        else:
            ack_message = 0
            if (GPIO.input(6) == 1):
                # zmod wants to transmit
                ack_message = "7.3"
                check_serial.responding_slave = 3
            elif (GPIO.input(13) == 1):
                # servo wants to transmit
                ack_message = "7.2"
                check_serial.responding_slave = 2
            elif (GPIO.input(19) == 1):
                # imm wants to transmit
                ack_message = "7.1"
                check_serial.responding_slave = 1
            if ack_message != 0:
                if prpMsg(ack_message) == "Sent ok!":
                    global_vars.master_receiving = True
                    #set incoming_bytes and received_bytes to 0 after ACKing the slave
                    check_serial.incoming_bytes = 0
                    check_serial.received_bytes = 0
                    check_serial.response_ts = time.time()
                else:
                    print("ACK failed")

    # check if there are bytes available in serial
    if ser.in_waiting > 0:

        led_status = 0b111
        set_leds(led_status)
        received_byte = int.from_bytes(ser.read(), "big")
        check_serial.message = (check_serial.message << 8) + received_byte
        check_serial.received_bytes += 1
        if (check_serial.received_bytes == 1):
            # this is the first byte received, check how many additional bytes to expect
            # and which slave is responding
            check_serial.incoming_bytes = (received_byte >> 3) & 0b11
            if ((received_byte >> 5) & 0b111)!= check_serial.responding_slave:
                print("response from other slave or corrupted :"+str(bin(received_byte)))
                #this response will time out
                check_serial.error = 1
                
        if ((check_serial.received_bytes == check_serial.incoming_bytes + 1) and
           (check_serial.error == 0)):
            # got the whole message
            check_serial.error |= msb.readmsg(check_serial.message, check_serial.received_bytes)
            if check_serial.error == 1:
                #error reading the bytes
                #set repeat flag
                print("error receiving message")
                check_serial.request_repeat = 1
                check_serial.error = 0
                
            else:
                #message received correctly
                check_serial.responding_slave = 0
                
            check_serial.message = 0
            check_serial.received_bytes = 0
            check_serial.incoming_bytes = 0
            global_vars.master_receiving = False
            check_serial.response_ts = 0
        set_leds(global_vars.led_status)

    # if a response has timed out , set master_receiving to false
    if (check_serial.response_ts != 0) and (myTimer(check_serial.response_ts, 0.020)):
        #reset the message
        check_serial.message = 0
        check_serial.error = 0
        print("response timed out"+str(time.time()))
        global_vars.master_receiving = False
        check_serial.response_ts = 0
        #set incoming_bytes and received_bytes to 0 after a timeout
        check_serial.incoming_bytes = 0
        check_serial.received_bytes = 0
        #set repeat flag
        check_serial.request_repeat = 1

# init a variable for check_serial
check_serial.received_bytes = 0
check_serial.incoming_bytes = 0
check_serial.responding_slave = 0
check_serial.error = 0
check_serial.request_repeat = 0
check_serial.message = 0
check_serial.response_ts = 0
check_serial.ack = 0


def test_coms_2(test_num):
    test_index = 0
    while(test_index < test_num):
        message = format(int(test_index%255), '08b')
        #if set_and_confirm(2, message, 0.1, 2) == 1:
        #    print("error")
        #    return 1
        operation = test_index%4
        if operation == 0:
            message = "****0001"
            print("OP 0")
            #append_message("1.0")
            #append_and_send("2.0.0",0.4)
            #append_message("3.0")
            if set_and_confirm(2, message, 0.05, 2) == 1:
                print("error op 0 set")
                return 1
            if wait_until_var_equal(2, message, 0.4, 0) == 1:
                print("error op 0 wait")
                return 1
            
        elif operation == 1:
            print("OP 1")
            #append_and_send("3.0",0.4)
            #append_message("2.0.0")
            #append_message("1.0")
            if set_and_confirm(14, "000", 0.05, 2) == 1:
                print("error op 1 set")
                return 1
            
        elif operation == 2:
            print("OP 2")
            #append_and_send("2.0.0",0.4)
            #append_message("3.0")
            #append_and_send("1.0",0.4)
            if set_and_confirm(9, 0, 0.05, 2) == 1:
                print("error op 2 set")
                return 1
        elif operation == 3:
            print("OP 3")
            #append_message("2.0.0")
            #append_message("1.0")
            #append_and_send("3.0",0.4)
            if wait_until_var_equal(9, 0, 0.4, 0) == 1:
                print("error op 3 wait servo")
                return 1
            if wait_until_var_equal(13, "110", 0.4, 0) == 1:
                print("error op 3 wait zmod")
                return 1
        test_index += 1
    print("test successful")
        
    #if wait_until_var_equal(1, value, 30, 0) == 1:
    
    #if wait_until_var_equal(11, end_check_str, 30, 0) == 1:
    #if wait_delay(delay) == 1:
        
        
def test_coms(attempts, target):
    var = 0
    message = 0
    if target == 1:
        var = 2
        message = "00001100"
    elif target == 2:
        var = 10
        message = 0
    elif target == 3:
        var = 14
        message = "001"
    for x in range(attempts):
        global_vars.imm_relays = -1
        global_vars.servo_command_index = -1
        global_vars.z_mod_outputs = -1
        if set_and_confirm(var, message, 0.05, 2) == 1:
            print("test failed")
            return
        x += 1


def read_user_input(user_input):
    if (user_input == "globals"):
        print_globals()
    elif (user_input == "files"):
        print_files()
    elif (user_input == "red,on"):
        global_vars.led_status |= 1
        set_leds(global_vars.led_status)
    elif (user_input == "red,off"):
        global_vars.led_status &= ~1
        set_leds(global_vars.led_status)
    elif (user_input == "green,on"):
        global_vars.led_status |= (1 << 1)
        set_leds(global_vars.led_status)
    elif (user_input == "green,off"):
        global_vars.led_status &= ~(1 << 1)
        set_leds(global_vars.led_status)
    elif (user_input == "blue,on"):
        global_vars.led_status |= (1 << 2)
        set_leds(global_vars.led_status)
    elif (user_input == "blue,off"):
        global_vars.led_status &= ~(1 << 2)
        set_leds(global_vars.led_status)
    elif (user_input == "com"):
        # prpMsg("2.8")
        append_message("2.8")
    elif (user_input == "test_i"):
        test_coms(1000, 1)
    elif (user_input == "test_s"):
        test_coms(1000, 2)
    elif (user_input == "test_z"):
        test_coms(1000, 3)
    elif (user_input == "test"):
        test_coms_2(5000)
    elif (user_input == "discard"):
        discard_item(0)
    elif (user_input == "discard q"):
        discard_item(1)
    elif (user_input == "move"):
        print("move")
    elif (user_input == "fs"):
        interface.toggle_fullscreen()
    else:
        print(user_input)
        append_message(user_input)


def run_update_functions(serial, ui, switch):
    result = 0
    if serial == 1:
        check_serial()

    #if (ui == 1) and (global_vars.disable_ui_updates == 0):
    #    interface.update_ui()
    if (ui == 1) and (global_vars.master_receiving == False) and (global_vars.master_transmiting == False):
        interface.update_ui()
    
    # check raspb_state for alarm indication
    if global_vars.raspb_state == "ALARM":
        # stop execution and return 1 to indicate the state change
        return 1

    if global_vars.ignore_physical_switch == 0:
        if switch == 1:
            result = check_auto_switch()
    
    #monitor 36V rail
    if (GPIO.input(27) == True) and (global_vars.raspb_state != "ALARM") :
        global_vars.raspb_state = "ALARM"
        print("36V supply interrupted!")
        #set emergency pin on IMM
        message = "1.1."+replace_stars(2, "*****0**")
        append_message(message)
        #return 1 to indicate state change
        return 1
    
    return result


def first_contact(hands, timeout):
    # reset variables (incase we call first_contact again)
    global_vars.imm_signals = -1
    global_vars.servo_errors = -1
    global_vars.z_mod_inputs = -1

    for x in hands:
        if x == 5 or x == 0 or x == 11:
            # not implemented slaves, pass
            pass
        else:

            if GPIO.input(x) == 0:

                # pin is low, send a status report
                if x == 19:
                    var = 1
                elif x == 13:
                    var = 3
                elif x == 6:
                    var = 13

                if wait_var_update(var, timeout, 1) == 1:
                    print("error contacting arduino on pin " + str(x))
            else:
                # wait a bit for coms to complete and then check if the value was updated
                if wait_delay(1) == 1:
                    print("error while waiting for coms to complete")
                    return 1

                if x == 19:
                    if global_vars.imm_signals == -1:
                        print("imm not contacted")
                        return 1
                elif x == 13:
                    if global_vars.servo_errors == -1:
                        print("servo not contacted")
                        return 1
                elif x == 6:
                    if global_vars.z_mod_inputs == -1:
                        print("zmod not contacted")
                        return 1

    print("all arduinos contacted")

    return 0


def read_robot_states(states_file):
    f = open(states_file, "r")
    file_contents = f.readlines()
    global_vars.robot_states.clear()
    for i in range(len(file_contents)):
        if i > 0:
            global_vars.robot_states.append(file_contents[i].strip())
            actual_index = i - 1
            states_split = global_vars.robot_states[actual_index].split(".")
            if states_split[0] == "s":
                if states_split[1] == "move":
                    if states_split[2] != "0":
                        # check if robot moves for that index has a delay of 1201
                        # indicating that servo will wait for a next command
                        previous_move_index = int(states_split[2]) - 1
                        moves_split = global_vars.robot_moves[previous_move_index].split(".")
                        if moves_split[3] != "1201":
                            print("error , robot move : " + states_split[
                                2] + " does not require a \"next\" as indicated by robot states : " + str(actual_index))
                            return 1
            if states_split[0] == "r" and states_split[1] == "disc":
                global_vars.num_discard = int(states_split[2])
                discard_coords_file_path = global_vars.folder_path+"saved_programs/"+global_vars.selected_program+"/discard_coords.txt"
                ds = open(discard_coords_file_path, "r")
                coords = ds.readlines()
                global_vars.x_discard_position = int(coords[0])
                global_vars.y_discard_position = int(coords[1])
                global_vars.z_discard_position = int(coords[2])
                ds.close()
                print("found discard positions")
                print(str(global_vars.x_discard_position))
                print(str(global_vars.y_discard_position))
                print(str(global_vars.z_discard_position))
    f.close()
    return 0


def program_servo_moves():
    if global_vars.selected_program == "":
        global_vars.raspb_state = "MANUAL"
        print("programming failed, no saved file")
        return 1
    moves_path = global_vars.folder_path+"saved_programs/"+global_vars.selected_program+"/robot_moves.txt"
    states_path = global_vars.folder_path+"saved_programs/"+global_vars.selected_program+"/robot_states.txt"
    f = open(moves_path, "r")
    file_contents = f.readlines()
    global_vars.robot_moves.clear()
    for i in range(len(file_contents)):
        if i > 0:
            global_vars.robot_moves.append(file_contents[i].strip())
    f.close()

    if read_robot_states(states_path) == 1:
        print("Error in programming logic")
        global_vars.raspb_state = "STUCK"
        return 1

    available_moves = len(global_vars.robot_moves)
    if available_moves:
        message = "2.1.0." + str(available_moves)
        append_message(message)
        

        for i in range(available_moves):
            move_data = global_vars.robot_moves[i].split(".")
            index = i
            axis = move_data[0]
            position = move_data[1]
            speed = move_data[2]
            delay = move_data[3]

            if axis == "1":
                global_vars.x_start_position = int(move_data[1])
            elif axis == "2":
                global_vars.y_start_position = int(move_data[1])
            elif axis == "3":
                global_vars.z_start_position = int(move_data[1])

            message = "2.1.1." + str(index)
            append_message(message)
            
            message = "2.1.2." + str(axis) + "." + str(position) + "." + speed
            append_message(message)
            message = "2.1.3." + str(delay).strip()
            append_message(message)
    else:
        print("moves file was empty")
        global_vars.raspb_state = "MANUAL"
        return 1

    # request an update of servo errors to check the moves programming bit
    if wait_var_update(3, 1, 1) == 1:
        print("error requesting servo_errors update")
        return 1

    if wait_until_var_equal(3, "0*******", 5, 0) == 1:
        return 1
    return 0



def zero(force_zero):
    if force_zero == 1:
        # trick raspberry into thinking the servo is not zeroed
        global_vars.servo_errors |= (1 << 5)

    # zero z axis
    if append_and_send("2.6.100", 0.1) == 1:
        print("timed out while sending zero z to servo ")
        global_vars.raspb_state = "STUCK"
        return 1
    if force_zero == 1:
        # servo board will command the servos to stop , so they will report back
        # their positions. wait for a while for positioning variables to be updated
        # and then force them to -1 so that the following wait_until_var_equal functions
        # will function properly
        if wait_delay(0.1) == 1:
            # state change
            print("state change while waiting in forced zeroing")
            return 1
        global_vars.x_position = -1
        global_vars.y_position = -1
        global_vars.z_position = -1

    if wait_until_var_equal(7, -1, 30, 1) == 1:
        # servo was unable to zero z axis
        print("unable to zero z axis")
        return 1

    # zero x and y axes
    if append_and_send("2.6.011", 0.1) == 1:
        print("timed out while sending zero x , y to servo ")
        global_vars.raspb_state = "STUCK"
        return 1
    if wait_until_var_equal(6, -1, 30, 1) == 1:
        # servo was unable to zero y axis
        print("unable to zero y axis")
        return 1

    if wait_until_var_equal(5, -1, 60, 1) == 1:
        # servo was unable to zero x axis
        print("unable to zero x axis")
        return 1

    # confirm that servo is zeroed by checking the axis have not been zeroed bit
    if wait_until_var_equal(3, "**0*****", 10, 0) == 1:
        # servo was unable to zero all axes
        print("unable to zero all axes ")
        return 1

    return 0


def set_servo_mode(mode):
    if mode == 0:
        # set servo to manual mode

        # turn leds red until mode change is complete
        global_vars.led_status = 0b1

        # reset global_vars.states_index
        global_vars.states_index = 0

        # set imm to indicate that the robot is exiting automatic mode
        if set_and_confirm(2, "****1***", 1, 5) == 1:
            # unable to set imm correctly
            print("unable to set imm correctly")
            return

        if global_vars.servo_mode == 1:
            if set_and_confirm(9, 0, 1, 5) == 1:
                # unable to set servo mode
                print("unable to set servo mode to manual")
                return

                # servo is in manual mode

        # turn leds red until mode change is complete
        global_vars.led_status = 0b1

        # set servo index to 0
        if set_and_confirm(10, 0, 1, 5) == 1:
            # unable to set index to 0
            print("unable to set index to 0")
            return

            # set servo_command_index to -1 for the raspberry so that it can send
        # the first next command when it reenters auto mode
        global_vars.servo_command_index = -1

        # get the current position of z axis
        if wait_var_update(7, 0.1, 1) == 1:
            print("error while getting z position")
            return 1

        # get the current position of y axis
        if wait_var_update(6, 0.1, 1) == 1:
            print("error while getting y position")
            return 1

        # get the current position of x axis
        if wait_var_update(5, 0.1, 1) == 1:
            print("error while getting x position")
            return 1

        if move_to_position_safe(0, 0, 0, 20, 10, 10) == 1:
            print("error while returning to 0.0.0")
            return 1

        # set imm to indicate that the robot is outside the mould area
        if set_and_confirm(2, "******11", 1, 5) == 1:
            # unable to set imm correctly
            print("unable to set imm correctly")
            return 1

            # turn leds green to indicate the mode change was completed
        global_vars.led_status = 0b10

        # servo in manual mode and axes returned to zero, set state to manual
        global_vars.raspb_state = "MANUAL"
        print("Raspberry State -- MANUAL")

    elif mode == 1:
        # set servo to automatic mode

        # reset global_vars.states_index
        global_vars.states_index = 0

        # send a status report to check if a move in going on
        if wait_var_update(4, 0.1, 1) == 1:
            print("timed out while requesting update of servo status")
            return 1

        # turn leds red until mode change is complete
        global_vars.led_status = 0b1

        # get temporary axes positions incase they are moving
        x_pos_temp = global_vars.x_position
        y_pos_temp = global_vars.y_position
        z_pos_temp = global_vars.z_position

        # for any axis that is moving, check to see if it stopped
        if global_vars.x_status != "IDLE":
            print("X axis currently moving , waiting for move to stop")
            if wait_until_var_equal(5, x_pos_temp, 30, 1) == 1:
                # timed out waiting for x to stop moving or state changed
                print("error while waiting for x axis to stop")
                return 1
        if global_vars.y_status != "IDLE":
            print("Y axis currently moving , waiting for move to stop")
            if wait_until_var_equal(6, y_pos_temp, 30, 1) == 1:
                # timed out waiting for y to stop moving or state changed
                print("error while waiting for y axis to stop")
                return 1
        if global_vars.z_status != "IDLE":
            print("Z axis currently moving , waiting for move to stop")
            if wait_until_var_equal(7, z_pos_temp, 30, 1) == 1:
                # timed out waiting for x to stop moving or state changed
                print("error while waiting for z axis to stop")
                return 1

        # get location of each axis
        if wait_var_update(5, 0.1, 1) == 1:
            print("timed out while requesting update of x position")
            return 1

        if wait_var_update(6, 0.1, 1) == 1:
            print("timed out while requesting update of y position")
            return 1

        if wait_var_update(7, 0.1, 1) == 1:
            print("timed out while requesting update of z position")
            return 1

        x_pos = global_vars.x_start_position
        y_pos = global_vars.y_start_position
        z_pos = global_vars.z_start_position
        if move_to_position_safe(x_pos, y_pos, z_pos, 20, 10, 10) == 1:
            print("error while getting to starting position")
            return 1

        # set IMM relays (indicate that the robot is in auto mode) CORRECT POSITION
        if set_and_confirm(2, "****0***", 1, 5) == 1:
            print("failed to set imm")
            return 1
        
        #wait for imm to enter automatic mode
        #if wait_until_var_equal(1, "*1*****", 30, 0) == 1:
        #        print("Timed out waiting for IMM to switch to auto mode")
        #        return 1
        
        #wait for mold to fully close and for imm to enter automatic mode
        
        if wait_until_var_equal(1, "11*****", 30, 0) == 1:
                print("Timed out waiting for mold to close before entering auto mode")
                return 1
        
        if set_and_confirm(10, 0, 1, 5) == 1:
            # unable to set servo index to 0
            print("unable to set servo index to 0")
            return 1

        if set_and_confirm(9, 1, 1, 5) == 1:
            # unable to set servo mode
            print("unable to set servo mode to automatic")
            return 1
            # servo is in auto mode

        # set auto_move_ended bits to 111 so that auto moves can start
        global_vars.auto_move_ended = 0b111


        global_vars.raspb_state = "AUTO"
        print("Raspberry State -- AUTO")

    elif mode == 2:
        # set servo to service mode
        pass
    else:
        # not supported mode , set to state to stuck
        print("requested mode not supported, setting state to stuck")
        global_vars.raspb_state = "STUCK"


def check_auto_switch():
    # update auto_switch value based on switch position
    if (myTimer(check_auto_switch.debounce_ts, 0.05)):
        if ((GPIO.input(24) == True) and global_vars.auto_switch == 0):

            if check_auto_switch.samples < 5:
                check_auto_switch.samples += 1
                global_vars.button_noise_r += 1
            else:
                global_vars.auto_switch = 1
                check_auto_switch.samples = 0
                print("Exiting auto mode")
                set_servo_mode(0)
                return 1

        elif ((GPIO.input(24) == False) and global_vars.auto_switch == 1):

            if check_auto_switch.samples < 5:
                check_auto_switch.samples += 1
                global_vars.button_noise_f += 1
            else:
                global_vars.auto_switch = 0
                check_auto_switch.samples = 0
                print("Entering auto mode")
                set_servo_mode(1)
                return 1

        check_auto_switch.debounce_ts = time.time()
    # no changes , return 0
    return 0


check_auto_switch.debounce_ts = 0
check_auto_switch.samples = 0


def discard_item(qc_flag):
    if global_vars.raspb_state == "AUTO":
        # set axes positions variables to -1
        global_vars.x_position = -1
        global_vars.y_position = -1
        global_vars.z_position = -1

        # set servo to manual mode
        if set_and_confirm(9, 0, 1, 5) == 1:
            # unable to set servo mode
            print("unable to set servo mode to manual")
            return

            # servo is in manual mode , it will run stop() and send back axes positions
        if wait_var_update(5, 0.1, 0) == 1:
            # did not get x position
            print("did not get x position")
            return 1

        if wait_var_update(6, 0.1, 0) == 1:
            # did not get y position
            print("did not get y position")
            return 1

        if wait_var_update(7, 0.1, 0) == 1:
            # did not get z position
            print("did not get z position")
            return 1

    # check if axes are at the discard position , if not move x and y then z
    if qc_flag == 1:
        discard_x = global_vars.x_qc_discard_position
        discard_y = global_vars.y_qc_discard_position
        discard_z = global_vars.z_qc_discard_position
    else:
        discard_x = global_vars.x_discard_position
        discard_y = global_vars.y_discard_position
        discard_z = global_vars.z_discard_position

    # move to discard position
    if move_to_position_safe(discard_x, discard_y, discard_z, 20, 10, 10) == 1:
        print("move to position failed")
        return 1

    # drop item
    if set_and_confirm(14, "000", 0.1, 5) == 1:
        print("dropping item failed, timeout or state change")
        return 1

    if qc_flag == 1:
        print("discarded item for quality control")
        global_vars.items_for_qc += 1
    else:
        global_vars.items_discarded += 1
        print("discarded item no : " + str(global_vars.items_discarded))
    # if mode was auto return to start position, if manual return to 0.0.0
    if global_vars.raspb_state == "AUTO":
        x_pos = global_vars.x_start_position
        y_pos = global_vars.y_start_position
        z_pos = global_vars.z_start_position
        if move_to_position_safe(x_pos, y_pos, z_pos, 20, 10, 10) == 1:
            print("move to start position failed")
            return 1

        # set global_vars.states_index equal to the length of robot_states to count the cycle
        global_vars.states_index = len(global_vars.robot_states)

        if set_and_confirm(10, 0, 1, 5) == 1:
            # unable to set servo index to 0
            print("unable to set servo index to 0")
            return

        if set_and_confirm(9, 1, 1, 5) == 1:
            # unable to set servo mode
            print("unable to set servo mode to automatic")
            return
            # servo is in auto mode

        # set auto_move_ended bits to 111 so that auto moves can start
        global_vars.auto_move_ended = 0b111


    elif global_vars.raspb_state == "MANUAL":
        if move_to_position_safe(0, 0, 0, 20, 10, 10) == 1:
            print("move to position 0.0.0 failed")
            return 1

        # moves to the position requested , always raises z axis first,


# then gets x and y to position and then lowers z
def move_to_position_safe(x_pos, y_pos, z_pos, x_speed, y_speed, z_speed):
    # check if z axis is at 0 , if not move z to 0
    if global_vars.z_position != 0:
        if append_and_send("2.3.3.0." + str(z_speed), 0.1) == 1:
            print("timed out while sending move z to 0 ")
            global_vars.raspb_state = "STUCK"
            return 1

        if wait_until_var_equal(7, 0, 30, 0) == 1:
            # z was unable to get to 0
            print("Z unable to get to 0")
            return 1

    if global_vars.x_position != x_pos:
        if append_and_send("2.3.1." + str(x_pos) + "." + str(x_speed), 0.1) == 1:
            print("timed out while sending move x")
            global_vars.raspb_state = "STUCK"
            return 1

    if global_vars.y_position != y_pos:
        if append_and_send("2.3.2." + str(y_pos) + "." + str(y_speed), 0.1) == 1:
            print("timed out while sending move y")
            global_vars.raspb_state = "STUCK"
            return 1

    if wait_until_var_equal(6, y_pos, 30, 0) == 1:
        # y was unable to get to position
        print("Y was unable to get to position")
        return 1

    if wait_until_var_equal(5, x_pos, 30, 0) == 1:
        # x was unable to get to position
        print("X was unable to get to position")
        return 1

    if global_vars.z_position != z_pos:
        if append_and_send("2.3.3." + str(z_pos) + "." + str(z_speed), 0.1) == 1:
            print("timed out while sending move z")
            global_vars.raspb_state = "STUCK"
            return 1

    if wait_until_var_equal(7, z_pos, 30, 0) == 1:
        # z was unable to get to position
        print("Z was unable to get to position")
        return 1

    return 0

#moves robot to position
def move_to_position(x_pos, y_pos, z_pos, x_speed, y_speed, z_speed):
    if global_vars.x_position != x_pos:
        if append_and_send("2.3.1." + str(x_pos) + "." + str(x_speed), 0.1) == 1:
            print("timed out while sending move x")
            global_vars.raspb_state = "STUCK"
            return 1

    if global_vars.y_position != y_pos:
        if append_and_send("2.3.2." + str(y_pos) + "." + str(y_speed), 0.1) == 1:
            print("timed out while sending move y")
            global_vars.raspb_state = "STUCK"
            return 1

    if global_vars.z_position != z_pos:
        if append_and_send("2.3.3." + str(z_pos) + "." + str(z_speed), 0.1) == 1:
            print("timed out while sending move z")
            global_vars.raspb_state = "STUCK"
            return 1

    if wait_until_var_equal(5, x_pos, 30, 0) == 1:
        # x was unable to get to position
        print("X was unable to get to position")
        return 1

    if wait_until_var_equal(6, y_pos, 30, 0) == 1:
        # y was unable to get to position
        print("Y was unable to get to position")
        return 1

    if wait_until_var_equal(7, z_pos, 30, 0) == 1:
        # z was unable to get to position
        print("Z was unable to get to position")
        return 1

    return 0



def run_auto():
    if global_vars.states_index >= len(global_vars.robot_states):
        # a cycle was complete , reset states_index
        global_vars.states_index = 0
        global_vars.cycles += 1
        interface.update_item_stats()
    #print("states index is : " + str(global_vars.states_index))
    print("robot_state is : " + global_vars.robot_states[global_vars.states_index])

    robot_states_split = global_vars.robot_states[global_vars.states_index].split(".")
    target = robot_states_split[0]

    if target == "i":
        operation = robot_states_split[1]
        value = robot_states_split[2]
        if operation == "in":
            if wait_until_var_equal(1, value, 30, 0) == 1:
                print("index : " + str(global_vars.states_index) + " ,imm in failed, timeout or state change")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            global_vars.states_index += 1

        elif operation == "out":
            if set_and_confirm(2, value, 0.1, 2) == 1:
                print("index : " + str(global_vars.states_index) + " ,imm out failed, timeout or state change")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            global_vars.states_index += 1

        else:
            print("Command at robot_state index : " + str(global_vars.states_index) + " not recognized")
            global_vars.raspb_state = "STUCK"
            return

    elif target == "s":
        operation = robot_states_split[1]
        value = robot_states_split[2]
        if operation == "move":
            if send_next(value) == 1:
                print("error during send next , index : " + str(global_vars.states_index))
                return
            global_vars.states_index += 1

        elif operation == "compl":
            # check which axis to wait for
            end_check_str = ""
            axis = global_vars.robot_moves[int(value)].split(".")
            axis = int(axis[0])
            if axis == 1:
                end_check_str = "**1"
            elif axis == 2:
                end_check_str = "*1*"
            elif axis == 3:
                end_check_str = "1**"
            else:
                print("invalid axis selection")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            if global_vars.auto_move_started & (1 << (axis - 1)) == 0:
                # axis has not started moving yet, wait for it
                # print("waiting for axis to start")
                if wait_until_var_equal(11, end_check_str, 30, 0) == 1:
                    print("failed while waiting for axis to start in s.compl")
                    global_vars.raspb_state = "STUCK"
                    print("Setting state to STUCK")
                    return
            if wait_until_var_equal(12, end_check_str, 30, 0) == 1:
                print("failed while waiting for axis to stop in s.compl")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            global_vars.states_index += 1

        else:
            print("Command at robot_state index : " + str(global_vars.states_index) + " no recognized")
            global_vars.raspb_state = "STUCK"
            print("Setting state to STUCK")
            return


    elif target == "z":
        operation = robot_states_split[1]
        value = robot_states_split[2]
        if operation == "in":
            if wait_until_var_equal(13, value, 30, 0) == 1:
                print("index : " + str(global_vars.states_index) + " ,zmod in failed, timeout or state change")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            global_vars.states_index += 1

        elif operation == "out":
            if set_and_confirm(14, value, 0.1, 5) == 1:
                print("index : " + str(global_vars.states_index) + " ,zmod out failed, timeout or state change")
                global_vars.raspb_state = "STUCK"
                print("Setting state to STUCK")
                return
            global_vars.states_index += 1

        else:
            print("Command at robot_state index : " + str(global_vars.states_index) + " no recognized")
            global_vars.raspb_state = "STUCK"
            print("Setting state to STUCK")
            return

    elif target == "d":
        delay = int(robot_states_split[1]) / 1000
        if wait_delay(delay) == 1:
            print("index : " + str(global_vars.states_index) + " , delay failed, state change")
            global_vars.raspb_state = "STUCK"
            print("Setting state to STUCK")
        global_vars.states_index += 1

    elif target == "r":
        operation = robot_states_split[1]
        if operation == "disc":
            if (global_vars.items_discarded < global_vars.num_discard):
                # discard current item
                if discard_item(0) == 1:
                    print("failed to discard item")
                    global_vars.raspb_state = "STUCK"
                    print("Setting state to STUCK")
                    return
                global_vars.states_index += 1
            else:
                global_vars.states_index += 1
        elif operation == "qc":
            if global_vars.items_discarded < global_vars.num_discard:
                # machine is still discarding items, pass
                global_vars.states_index += 1
            else:
                qc_type = robot_states_split[2]
                value = robot_states_split[3]
                if qc_type == "s":
                    if ((global_vars.cycles + 1) - global_vars.items_discarded) % int(value) == 0:
                        # discard current item for quality control
                        if discard_item(1) == 1:
                            print("failed to discard item for quality control")
                            global_vars.raspb_state = "STUCK"
                            print("Setting state to STUCK")
                            return
                        global_vars.states_index += 1
                    else:
                        print("no QC")
                        global_vars.states_index += 1
                else:
                    print("percent QC not implemented yet")
                    global_vars.states_index += 1

def send_next(next_index):
    # check if axes have completed their last auto move
    if wait_until_var_equal(12, "111", 15, 0) == 1:
        print("axes have not completed their last auto move")
        global_vars.raspb_state = "STUCK"
        print("Setting state to STUCK")
        return 1
    # print("axes completed their last auto move")

    # check if index is correct
    next_index = int(next_index)
    if next_index == 0:
        # special case because current index might be len(global_vars.robot_moves)-1
        # or 0 depending on if it's the first time running the auto loop
        if global_vars.servo_command_index != 0 and global_vars.servo_command_index != len(global_vars.robot_moves) - 1:
            # index error
            print("index 0 error")
            global_vars.raspb_state = "STUCK"
            print("Setting state to STUCK")
            return 1
    else:
        if global_vars.servo_command_index != next_index - 1:
            # index error
            print("index " + str(next_index) + " error")
            global_vars.raspb_state = "STUCK"
            print("Setting state to STUCK")
            return 1

    next_move_axis = global_vars.robot_moves[next_index]
    next_move_axis = next_move_axis.split(".")[0]
    # print("next move axis is : " + next_move_axis)
    start_check_str = ""
    if next_move_axis == "1":
        start_check_str = "**1"
    elif next_move_axis == "2":
        start_check_str = "*1*"
    elif next_move_axis == "3":
        start_check_str = "1**"
    else:
        print("invalid axis selection")
        global_vars.raspb_state = "STUCK"
        print("Setting state to STUCK")
        return 1

    # send next
    append_message("2.2")
    # wait for auto_move_started to be set
    if wait_until_var_equal(11, start_check_str, 1, 0) == 1:
        print("move with index : " + str(next_index) + " failed to start")
        global_vars.raspb_state = "STUCK"
        print("Setting state to STUCK")
        return 1

    return 0


def replace_stars(variable, input_string):
    output_string = ""

    if input_string == "":
        return output_string

    var_len = 0
    if variable == 1:
        variable = global_vars.imm_signals
        var_len = 7
    elif variable == 2:
        variable = global_vars.imm_relays
        var_len = 8
    elif variable == 3:
        variable = global_vars.servo_errors
        var_len = 8
    elif variable == 4:
        variable = global_vars.servo_status
        var_len = 16
    elif variable == 8:
        # not implemented yet
        var_len = 0
        # variable = global_vars.servo_params
    elif variable == 11:
        variable = global_vars.auto_move_started
        var_len = 3
    elif variable == 12:
        variable = global_vars.auto_move_ended
        var_len = 3
    elif variable == 13:
        variable = global_vars.z_mod_inputs
        var_len = 3
    elif variable == 14:
        variable = global_vars.z_mod_outputs
        var_len = 3

        # deal with variables that are used as numbers instead of bit flags
    if var_len == 0:
        return str(input_string)

    # replace * with the current bit value of the variable
    for i in range(var_len):
        if input_string[i] == "*":
            if (variable >> ((var_len - 1) - i)) & 1 == 1:
                output_string += "1"
            else:
                output_string += "0"
        else:
            output_string += input_string[i]

    return output_string


def compare_var(var, var_value, not_equal_flag):
    updated_var_value = 0
    if var == 1:
        updated_var_value = global_vars.imm_signals
    elif var == 2:
        updated_var_value = global_vars.imm_relays
    elif var == 3:
        updated_var_value = global_vars.servo_errors
    elif var == 4:
        updated_var_value = global_vars.servo_status
    elif var == 5:
        updated_var_value = global_vars.x_position
    elif var == 6:
        updated_var_value = global_vars.y_position
    elif var == 7:
        updated_var_value = global_vars.z_position
    elif var == 8:
        # not implemented correctly yet
        updated_var_value = global_vars.servo_params[0]
    elif var == 9:
        updated_var_value = global_vars.servo_mode
    elif var == 10:
        updated_var_value = global_vars.servo_command_index
    elif var == 11:
        updated_var_value = global_vars.auto_move_started
    elif var == 12:
        updated_var_value = global_vars.auto_move_ended
    elif var == 13:
        updated_var_value = global_vars.z_mod_inputs
    elif var == 14:
        updated_var_value = global_vars.z_mod_outputs
    if not_equal_flag == 0:
        if updated_var_value == var_value:
            # print("variables matched")
            return 0
        else:
            return 1
    elif not_equal_flag == 1:
        if updated_var_value != var_value:
            # print("variables not equal anymore")
            return 0
        else:
            return 1


# var : according to global_vars.py vars list
# var_value : binary string for values that can have * , int otherwise
# timeout_s : timeout in seconds , use 0 for no timeout
# not_equal_flag : if 1 checks if var is not equal to var_value anymore

# returns 0 if executed correctly , 1 if it times out or a raspb_state change occurs
def wait_until_var_equal(var, var_value, timeout_s, not_equal_flag):
    loop = 1
    replace_stars_flag = 0
    if var == 1 or var == 2 or var == 3 or var == 4 or var == 11 or var == 12 or var == 13 or var == 14:
        # var_value might have stars , set flag to replace them
        replace_stars_flag = 1
    if replace_stars_flag == 1:
        confirm_val = int(replace_stars(var, var_value), 2)
    else:
        confirm_val = var_value
    timeout_timestamp = time.time()
    while loop == 1:

        if timeout_s != 0:
            if myTimer(timeout_timestamp, timeout_s):
                print("timed out while waiting for variable " + str(var) + " update")
                #global_vars.raspb_state = "STUCK"
                return 1

        if global_vars.raspb_state == "AUTO":
            # check serial , ui and switch
            if run_update_functions(1, 1, 1) == 1:
                # mode changed , return
                return 1
        else:
            # only check serial and ui if not in auto mode
            if run_update_functions(1, 1, 0) == 1:
                # alarm, return
                return 1

        # in cases where stars are used as wild cards, confirm_val has to be recalculated
        # because these bits might change while wait for update is running
        if replace_stars_flag == 1:
            confirm_val = int(replace_stars(var, var_value), 2)

        if compare_var(var, confirm_val, not_equal_flag) == 0:
            # print("wait_until_var_equal "+ str(var)+ " successful")
            return 0


# returns 0 if executed correctly , 1 if it cannot set value out or a raspb_state change occurs
def set_and_confirm(var, var_value, repeat_delay, attempts_limit):
    attempts = 0
    loop = 1
    message_str = ""
    confirm_val = 0
    if var == 2:
        # set imm relays
        message_str = "1.1."
        str_value = replace_stars(var, var_value)
        message_str += str_value
        confirm_val = int(str_value, 2)
        global_vars.imm_relays = -1

    elif var == 9:
        # set servo mode
        message_str = "2.4." + str(var_value)
        confirm_val = var_value
        global_vars.servo_mode = -1

    elif var == 10:
        # set servo index
        message_str = "2.1.5." + str(var_value)
        confirm_val = var_value
        global_vars.servo_command_index = -1

    elif var == 14:
        # set zmod outputs
        message_str = "3.1."
        str_value = replace_stars(var, var_value)
        message_str += str_value
        confirm_val = int(str_value, 2)
        global_vars.z_mod_outputs = -1

    else:
        print("incorrect set_and_confirm() call, only used with variables 2,9,10 or 14 ")
        global_vars.raspb_state = "STUCK"
        return 1
    #print("first append"+str(time.time()))
    append_message(message_str)
    set_and_confirm.ts = time.time()
    attempts = 1
    while loop == 1:
        if (myTimer(set_and_confirm.ts, repeat_delay)):
            # send message to set outputs
            if attempts > attempts_limit:
                print("unable to set variable " + str(var) +"  to " + message_str)
                #global_vars.raspb_state = "STUCK"
                return 1
            print("appending"+str(time.time()))
            append_message(message_str)
            set_and_confirm.ts = time.time()
            # print("this was the "+str(attempts)+" attempt to send "+str(message_str))
            attempts += 1

        if global_vars.raspb_state == "AUTO":
            if run_update_functions(1, 1, 1) == 1:
                # mode changed or alarm , return
                return 1
        else:
            if run_update_functions(1, 1, 0) == 1:
                # alarm , return
                return 1

        if compare_var(var, confirm_val, 0) == 0:
            # print("set_and_confirm "+ str(var)+ " successful")
            set_and_confirm.ts = 0
            loop = 0

    return 0


set_and_confirm.ts = 0


# if used with request_update_flag = 0 , the user must
# set the variable he is interrested in to -1 before sending
# the command that prompts an automatic request from the slave
def wait_var_update(var, timeout, request_update_flag):
    if request_update_flag == 1:
        if var == 1 or var == 2:
            message = "1.0"
            global_vars.imm_relays = -1
            global_vars.imm_signals = -1
        elif var == 3 or var == 4:
            message = "2.0.0"
            global_vars.servo_errors = -1
            global_vars.servo_status = -1
        elif var == 5:
            message = "2.0.1"
            global_vars.x_position = -1
        elif var == 6:
            message = "2.0.2"
            global_vars.y_position = -1
        elif var == 7:
            message = "2.0.3"
            global_vars.z_position = -1
        elif var == 8:
            # not implemented
            global_vars.raspb_state = "STUCK"
            return 1
        elif var == 9:
            message = "2.0.5"
            global_vars.servo_mode = -1
        elif var == 10:
            message = "2.0.6"
            global_vars.servo_command_index = -1
        elif var == 13 or var == 14:
            message = "3.0"
            global_vars.z_mod_inputs = -1
            global_vars.z_mod_outputs = -1

        if append_and_send(message, timeout) == 1:
            print("append_and_send timeout in wait_var_update : " + message)
            return 1

    request_ts = time.time()
    while 1:
        # wait until variable gets update or the function times out
        if myTimer(request_ts, timeout) == 1:
            print("timed out waiting for request " + str(var))
            #global_vars.raspb_state = "STUCK"
            return 1

        if run_update_functions(1, 1, 1) == 1:
            # mode changed or alarm, return
            print("state changed during append_and_send")
            return 1

        if var == 1 or var == 2:
            if global_vars.imm_relays != -1 and global_vars.imm_signals != -1:
                return 0
        elif var == 3 or var == 4:
            if global_vars.servo_errors != -1 and global_vars.servo_status != -1:
                return 0
        elif var == 5:
            if global_vars.x_position != -1:
                return 0
        elif var == 6:
            if global_vars.y_position != -1:
                return 0
        elif var == 7:
            if global_vars.z_position != -1:
                return 0
        elif var == 9:
            if global_vars.servo_mode != -1:
                return 0
        elif var == 10:
            if global_vars.servo_command_index != -1:
                return 0
        elif var == 13 or var == 14:
            if global_vars.z_mod_inputs != -1 and global_vars.z_mod_outputs != -1:
                return 0


def append_and_send(message, timeout):
    append_message(message)
    #GPIO.output(21, 1)
    timeout_ts = time.time()
    while 1:
        
        if run_update_functions(1, 1, 1) == 1:
            # mode changed or alarm, return
            print("state changed during append_and_send")
            return 1

        if message not in global_vars.coms_out:
            # message was sent, return 0
            return 0

        if myTimer(timeout_ts, timeout):
            print("message "+message+" was not sent before timeout")
            #global_vars.raspb_state = "STUCK"
            return 1


def wait_delay(delay):
    delay_ts = time.time()
    while (1):
        if myTimer(delay_ts, delay):
            return 0
        if run_update_functions(1, 1, 1) == 1:
            # mode changed or alarm, return
            print("state changed during wait_delay")
            return 1


def append_message(message):
    # print("added "+message)
    global_vars.coms_out.append(message)

    

def coms_send():
    if prpMsg(global_vars.coms_out[0]) == "Sent ok!":
        # print("sent successful")
        return 0
    elif prpMsg(global_vars.coms_out[0]) == "Unknown message":
        return 1
    elif prpMsg(global_vars.coms_out[0]) == "Invalid message":
        return 1
    elif prpMsg(global_vars.coms_out[0]) == "Missing parameters":
        return 1


def sendMsg(msg, length):
    #rand = random.randint(1,100)
    
    rs_485_on_time = length * 0.000235
    # print(str(global_vars.rs485_timeout))
    global_vars.master_transmiting = True
    global_vars.rs_485_high_ts = 0
    global_vars.rs_485_low_ts = 0
    global_vars.rs_485_high_ts = time.time()
    GPIO.output(26, 1)
    ser.write(msg)
    # print(msg)
    # get a timestamp to lower the rs485 pin
    rs_485_on_ts = time.time()
    while(myTimer(rs_485_on_ts,rs_485_on_time) == 0):
        #do nothing
        pass
    #if rand <= 25 and global_vars.raspb_state == "MANUAL":
    #    print("creating error on :"+str(msg))
    #    GPIO.output(21, 1)
    #    while(myTimer(rs_485_on_ts,4*rs_485_on_time) == 0):
    #        #create a problem
    #        pass
    #    GPIO.output(21, 0)
    
    
    GPIO.output(26,0)
    global_vars.master_transmiting = False
    


def prpMsg(msg):
    bmsg = msb.buildmsg(msg)
    if bmsg[0] == "Valid-Execution":
        try:
            fnlmsg = int(bmsg[1]).to_bytes(bmsg[2], "big")
        except AttributeError:
            fnlmsg = bytearray(0)
            fnlmsg.append(bmsg[1])
        if global_vars.master_receiving:
            return "unable to send message , master receiving atm"
        if global_vars.master_transmiting:
            return "unable to send message , master transmiting atm"
        sendMsg(fnlmsg, bmsg[2])
        return "Sent ok!"

    else:
        return bmsg[0]


def myTimer(stamp, gap):
    if time.time() - stamp < gap:
        return False
    return True


def set_leds(led_status):
    GPIO.output(10, led_status & 1)
    GPIO.output(9, (led_status >> 1) & 1)
    GPIO.output(22, (led_status >> 2) & 1)


def print_files():
    print("robot moves : ")
    print(*global_vars.robot_moves)

    print("robot states : ")
    print(*global_vars.robot_states)


def print_globals():
    print("state : " + global_vars.raspb_state)
    print("master receiving : " + str(global_vars.master_receiving))
    print("master transmiting : " + str(global_vars.master_transmiting))
    print("master_transm_ts : " + str(global_vars.master_transm_ts))
    print("coms_slave_requests : ", end='')
    print(*global_vars.coms_slave_requests)

    print("coms_release : ", end='')
    print(*global_vars.coms_release)

    print("coms_timestamps : ")
    for x in range(6):
        print("ts :" + str(x) + " " + str(global_vars.coms_timestamps[x]))

    print("led status : " + str(global_vars.led_status))
    # print("update_received : "+str(global_vars.update_received))
    print("auto_switch : " + str(global_vars.auto_switch))
    print("Imm relays (1-8) : ", end='')
    print(bin(global_vars.imm_relays))
    print("Imm signals (1-7) : ", end='')
    print(bin(global_vars.imm_signals))
    print("Imm restart : " + str(global_vars.imm_restart))
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("Servo errors (0-7) : ", end='')
    print(bin(global_vars.servo_errors))
    print("Servo status (0-15) :", end='')
    print(bin(global_vars.servo_status))
    print("X status : " + str(global_vars.x_status))
    print("Y status : " + str(global_vars.y_status))
    print("Z status : " + str(global_vars.z_status))
    print("X position : " + str(global_vars.x_position))
    print("Y position : " + str(global_vars.y_position))
    print("Z position : " + str(global_vars.z_position))
    print("Servo Parameters (0-20) :")
    print(*global_vars.servo_params)
    print("Servo mode : " + str(global_vars.servo_mode))
    print("Automatic move index : " + str(global_vars.servo_command_index))
    # print("Auto move complete index : "+str(global_vars.auto_move_compl_index))
    # print("Auto move complete axis : "+str(global_vars.auto_move_compl_axis))
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("Z_mod inputs (0-2) : ", end='')
    print(bin(global_vars.z_mod_inputs))
    print("Z_mod outputs (0-2) : ", end='')
    print(bin(global_vars.z_mod_outputs))
    print("Z_mod restart : " + str(global_vars.z_mod_restart))

    print("Noise rising : " + str(global_vars.button_noise_r))
    print("Noise falling : " + str(global_vars.button_noise_f))

    print(" Outgoing : ")
    print(*global_vars.coms_out)
