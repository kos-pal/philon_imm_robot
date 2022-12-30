# v 0.1

import global_vars as global_vars
import time
import serial
import funct as funct





funct.parse_config_file()

hands = [19, 13, 6, 5, 0, 11]
funct.Gcleanup()
funct.Ginitialise(26, hands)

global_vars.led_status = 1
funct.set_leds(global_vars.led_status)
funct.parse_config_file()
global_vars.raspb_state = "CONTACT"
#global_vars.raspb_state = "STUCK"
#global_vars.raspb_state = "DEBUG"


while True:

    while (global_vars.raspb_state == "STUCK"):
        # stuck state

        funct.run_update_functions(1, 1, 0)

    while (global_vars.raspb_state == "CONTACT"):
        # establish coms with arduinos

        print("contacting slaves")
        if funct.first_contact(hands, 1) == 1:
            # slaves not contacted , state changed
            print("failed contacting all slaves")
            global_vars.raspb_state = "STUCK"
            break

        # turn leds red until config is complete
        global_vars.led_status = 0b1

        global_vars.raspb_state = "CONFIG"

    while (global_vars.raspb_state == "CONFIG"):
        # set up arduinos

        # set up imm (assuming robot is in mould area)
        print("setting up imm")
        if funct.set_and_confirm(2, "00001100", 1, 5) == 1:
            # unable to set imm
            print("setting up imm failed")
            print("Setting state to STUCK")
            global_vars.raspb_state = "STUCK"
            break

        # set up servo

        # get servo mode
        if funct.wait_var_update(9, 0.1, 1) == 1:
            # unable to get servo mode info
            print("getting servo mode failed")
            print("Setting state to STUCK")
            global_vars.raspb_state = "STUCK"
            break

        if global_vars.servo_mode != 0:
            # set servo to manual mode
            print("setting servo to manual")
            if funct.set_and_confirm(9, 0, 1, 5) == 1:
                # unable to set manual mode
                print("unable to set servo mode to manual")
                print("Setting state to STUCK")
                global_vars.raspb_state = "STUCK"
                break

        # turn leds red until config is complete
        global_vars.led_status = 0b1


        # check if robot is not zeroed
        if (global_vars.servo_errors >> 5) & 1 == 1:
            print("zeroing robot (force zero 0)")
            if funct.zero(0) == 1:
                print("Unable to zero robot")
                print("Setting state to STUCK")
                global_vars.raspb_state = "STUCK"
                break
        else:
            # zero robot anyway
            print("zeroing robot (force zero 1)")
            if funct.zero(1) == 1:
                print("Unable to zero robot")
                print("Setting state to STUCK")
                global_vars.raspb_state = "STUCK"
                break

        # set up imm (robot has exited mould area)
        print("setting up imm")
        if funct.set_and_confirm(2, "00001111", 1, 5) == 1:
            # unable to set imm
            print("setting up imm failed")
            print("Setting state to STUCK")
            global_vars.raspb_state = "STUCK"
            break

        # set up zmod
        print("setting up zmod")
        if funct.set_and_confirm(14, "000", 1, 5) == 1:
            # unable to set zmod
            print("unable to set zmod")
            print("Setting state to STUCK")
            global_vars.raspb_state = "STUCK"
            break

        print("init successful")
        global_vars.raspb_state = "PROGRAM"

        # turn leds green to indicate that config was completed
        global_vars.led_status = 0b10
    while (global_vars.raspb_state == "PROGRAM"):
        # program robot moves to servo
        print("programming servo moves")
        if funct.program_servo_moves() == 1:
            # unable to program moves
            print("programming moves on servo failed ")
            print("Setting state to STUCK")
            global_vars.raspb_state = "STUCK"
            break
        global_vars.raspb_state = "MANUAL"
        
    while (global_vars.raspb_state == "MANUAL"):
        # manual operation state

        # check serial , ui and automatic switch
        funct.run_update_functions(1, 1, 1)

    while (global_vars.raspb_state == "AUTO"):
        # automatic operation state

        # check serial , ui and automatic switch
        funct.run_update_functions(1, 1, 1)

        # run automatic mode
        funct.run_auto()

    while (global_vars.raspb_state == "ALARM"):
        # alarm state

        # check serial and ui
        funct.run_update_functions(1, 1, 0)

    while (global_vars.raspb_state == "DEBUG"):
        # debugging state
        funct.run_update_functions(1, 1, 0)