#v 0.1
import global_vars
import funct
import interface

def buildmsg(msg):
    msgar=msg.split(".")
    bmsg=["Incorrect message"]
    bitmsg=0
    lngth=1
    
    try:
        slv=int(msgar[0])
        cmnd=int(msgar[1])
        if slv== 7:
            #ack
            bmsg[0] = "Valid-Execution"
            bitmsg=bitmsg | slv <<5
            bitmsg=bitmsg | cmnd
        if slv==1 and cmnd==0:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
        if slv==1 and cmnd==1:
            lngth=2
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 13
            bitmsg=bitmsg | 1 << 11
            bitmsg=bitmsg | cmnd << 8
            flg=1
            for x in msgar[2]:
                bitmsg=bitmsg | int(x) << (8-flg)
                flg+=1
        if slv==1 and cmnd==5:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
            bitmsg=bitmsg | cmnd << 0
            
        if slv==2 and cmnd==0:
            rep=int(msgar[2])
            lngth=2
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 13
            bitmsg=bitmsg | 1 << 11
            bitmsg=bitmsg | cmnd << 8
            bitmsg=bitmsg | rep << 0
        if slv==2 and cmnd==1:
            rep=int(msgar[2])
            if not (rep==2 or rep==4):
                indx=int(msgar[3])
                lngth=3
                bmsg[0]="Valid-Execution"
                bitmsg=bitmsg | slv << 21
                bitmsg=bitmsg | 2 << 19
                bitmsg=bitmsg | cmnd << 16
                bitmsg=bitmsg | rep << 13
                bitmsg=bitmsg | indx << 0
            elif rep==2:
                lngth=4
                axs=int(msgar[3])
                pst=int(msgar[4])
                spd=int(msgar[5])
                bmsg[0]="Valid-Execution"
                bitmsg=bitmsg | slv << 29
                bitmsg=bitmsg | 3 << 27
                bitmsg=bitmsg | cmnd << 24
                bitmsg=bitmsg | rep << 21
                bitmsg=bitmsg | axs << 19
                bitmsg=bitmsg | pst << 7
                bitmsg=bitmsg | spd << 0
            elif rep==4:
                lngth=4
                param_index=int(msgar[3])
                param_value=int(msgar[4])
                bmsg[0]="Valid-Execution"
                bitmsg=bitmsg | slv << 29
                bitmsg=bitmsg | 3 << 27
                bitmsg=bitmsg | cmnd <<24
                bitmsg=bitmsg | rep << 21
                bitmsg=bitmsg | param_index << 16
                bitmsg=bitmsg | param_value
        if slv==2 and cmnd==2:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
            bitmsg=bitmsg | cmnd << 0
        if slv==2 and cmnd==3:
            axs=int(msgar[2])
            pst=int(msgar[3])
            spd=int(msgar[4])
            lngth=4
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 29
            bitmsg=bitmsg | 3 << 27
            bitmsg=bitmsg | cmnd << 24
            bitmsg=bitmsg | axs << 19
            bitmsg=bitmsg | pst << 7
            bitmsg=bitmsg | spd << 0
        if slv==2 and cmnd==4:
            rep=int(msgar[2])
            lngth=2
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 13
            bitmsg=bitmsg | 1 << 11
            bitmsg=bitmsg | cmnd << 8
            bitmsg=bitmsg | rep << 0
        if slv==2 and cmnd==5:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
            bitmsg=bitmsg | cmnd << 0
        if slv==2 and cmnd==6:
            lngth=2
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 13
            bitmsg=bitmsg | 1 << 11
            bitmsg=bitmsg | cmnd << 8
            flg=1
            for x in msgar[2]:
                bitmsg=bitmsg | int(x) << (3-flg)
                flg+=1
        if slv==2 and cmnd==7:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
            bitmsg=bitmsg | cmnd << 0
        if slv==2 and cmnd==8:
            bmsg[0]="Valid-Execution"
            bitmsg=0b00000000
        if slv==3 and cmnd==0:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
        if slv==3 and cmnd==1:
            lngth=2
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 13
            bitmsg=bitmsg | 1 << 11
            bitmsg=bitmsg | cmnd << 8
            flg=1
            for x in msgar[2]:
                bitmsg=bitmsg | int(x) << (3-flg)
                flg+=1
        if slv==3 and cmnd==5:
            bmsg[0]="Valid-Execution"
            bitmsg=bitmsg | slv << 5
            bitmsg=bitmsg | cmnd << 0
            
        if slv==0 :
            lngth=4
            bmsg[0]="Valid-Execution"
            bitmsg=0b00000000000000000000000000000000
            
        if bmsg[0]=="Valid-Execution":
            bmsg.append(bitmsg)
            bmsg.append(lngth)
        else:
            bmsg[0]="Unknown message"
        
    except ValueError:
        bmsg[0]="Invalid message"
        
    except IndexError:
        bmsg[0]="Missing parameters"
        
    #print(bmsg)
    return bmsg

def readmsg(msg,mslng):
    #print("received message was : "+str(bin(msg))+" , message length was :" +str(mslng))
    if(mslng == 0 ):
        return 1
    slave_id = (msg>>(8*(mslng-1)))>>5
    response_type = (msg>>(8*(mslng-1)))&0b111
    #print("responding slave was : " +str(slave_id))
    #print("response type was : "+str(response_type))
    if(slave_id == 1):
        #print("I")
        if(response_type == 0):
            #imm status response
            global_vars.imm_restart = msg & 1
            global_vars.imm_relays = (msg>>8)&0xFF
            
            #global_vars.imm_signals = (msg>>1)&0x7F
            global_vars.imm_signals = (~(msg>>1))&0x7F
            
            #if (global_vars.imm_signals & 1) == 1:
            if (global_vars.imm_signals & 1) == 0:
                #emergency stop
                #print("EMERGENCY")
                #global_vars.raspb_state = "STUCK"
                pass
            if ((global_vars.imm_signals>>5 & 1) == 0) and (global_vars.raspb_state == "AUTO"):
                #imm was set to manual mode , change raspb mode to manual
                print("IMM CHANGED TO MANUAL MODE")
                funct.set_servo_mode(0)
            
            print("Imm relays : "+str(bin(global_vars.imm_relays)))
            print("Imm signals : "+str(bin(global_vars.imm_signals)))

            if (global_vars.imm_restart == 1):
                print("imm has restarted")
                pass
            interface.update_ui_var("IMM_INPUTS")
            interface.update_ui_var("IMM_OUTPUTS")
            return 0
        
        else:
            print("Unknown Imm slave response type : "+str(response_type))
            return 1
        
    elif(slave_id == 2):
        #print("S")
        if(response_type==0):
            
            global_vars.servo_errors = (msg>>16)&0xFF
            global_vars.servo_status = msg&0xFFFF
            print("Servo errors : " + str(bin(global_vars.servo_errors)))
            print("Servo status : " + str(bin(global_vars.servo_status)))
            if((global_vars.servo_errors>>7)&1==1):
                #print("Automatic loop not set up , unable to enter automatic mode")
                pass
            if((global_vars.servo_errors>>6)&1==1):
                #print("Servo board has restarted")
                #servo should now be in manual mode without any saved commands
                global_vars.servo_mode = 0
                global_vars.servo_command_index = 0
            if((global_vars.servo_errors>>5)&1==1):
                #print("Axes not zeroed, unable to enter automatic mode")
                pass
            if((global_vars.servo_errors>>4)&1==1):
                #print("Move aborted , axis currently getting pulses")
                pass
            if((global_vars.servo_errors>>3)&1==1):
                #print("Unable to enter automatic mode because of servo position")
                pass
            if((global_vars.servo_errors>>2)&1==1):
                #print("Invalid servo mode for requested command")
                pass
            if((global_vars.servo_errors>>1)&1==1):
                #print("Move aborted , out of axis bounds")
                pass
            if(global_vars.servo_errors&1==1):
                #print("Alarm!")
                global_vars.raspb_state = "ALARM"
                funct.set_and_confirm(2,"00001000",0.05,5)
                global_vars.led_status = 1
                pass
            if(global_vars.servo_errors != 0):
                #if there are errors and raspb is in auto or manual mode, set leds to red
                if global_vars.raspb_state == "MANUAL" or global_vars.raspb_state == "AUTO":
                    global_vars.led_status = 1
            else:
                #no errors and raspb is in auto or manual mode, set leds to green
                if global_vars.raspb_state == "MANUAL" or global_vars.raspb_state == "AUTO":
                    global_vars.led_status = 0b10
                
            if(((global_vars.servo_status>>3)&1==1)&((global_vars.servo_status&1)==0)):
                #print("X axis is idle")
                global_vars.x_status = "IDLE"
            elif(((global_vars.servo_status>>3)&1==1)&((global_vars.servo_status&1)==1)):
                #print("X axis is getting pulses")
                global_vars.x_status = "MOVING"
            else:
                #print("X axis is slowing down")
                global_vars.x_status = "SLOWING"
            if(((global_vars.servo_status>>4)&1==1)&((global_vars.servo_status>>1)&1==0)):
                #print("Y axis is idle")
                global_vars.y_status = "IDLE"
            elif(((global_vars.servo_status>>4)&1==1)&((global_vars.servo_status>>1)&1==1)):
                #print("Y axis is getting pulses")
                global_vars.y_status = "MOVING"
            else:
                #print("Y axis is slowing down")
                global_vars.y_status = "SLOWING"
            if(((global_vars.servo_status>>5)&1==1)&((global_vars.servo_status>>2)&1==0)):
                #print("Z axis is idle")
                global_vars.z_status = "IDLE"
            elif(((global_vars.servo_status>>5)&1==1)&((global_vars.servo_status>>2)&1==1)):
                #print("Z axis is getting pulses")
                global_vars.y_status = "MOVING"
            else:
                #print("Z axis is slowing down")
                global_vars.z_status = "SLOWING"

            interface.update_ui_var("SERVO_ERRORS")
            #interface.update_ui_var("SERVO_STATUS")
            return 0
        
        elif(response_type==1):
            global_vars.x_position= msg&0x7FF
            #print("X position : "+str(global_vars.x_position)+"mm")
            interface.set_position_labels(1)
            return 0
        
        elif(response_type==2):
            global_vars.y_position= msg&0x7FF
            #print("Y position : "+str(global_vars.y_position)+"mm")
            interface.set_position_labels(2)
            return 0
        
        elif(response_type==3):
            global_vars.z_position= msg&0x7FF
            #print("Z position : "+str(global_vars.z_position)+"mm")
            interface.set_position_labels(3)
            return 0
        
        elif(response_type==4):
            servo_parameter_index = (msg>>16)&0b11111
            servo_parameter_value = msg&0xFFFF
            global_vars.servo_params[servo_parameter_index]=servo_parameter_value
            print("Parameter "+str(servo_parameter_index)+" : "+str(global_vars.servo_params[servo_parameter_index]))
            return 0
        
        elif(response_type==5):
            global_vars.servo_mode = msg&0xFF
            interface.change_mode(global_vars.servo_mode, 0)
            if(global_vars.servo_mode==0):
                #print("Servo in Manual mode")
                if(global_vars.servo_errors != 0):
                    global_vars.led_status = 1
                else:
                    global_vars.led_status = 0b10
                return 0
            elif(global_vars.servo_mode==1):
                #print("Servo in Automatic mode")
                global_vars.led_status = 0b100
                return 0
            elif(global_vars.servo_mode==2):
                #print("Servo in Service mode")
                global_vars.led_status = 0b101
                return 0
            else:
                print("Servo in UNKNOWN mode")
                return 1
                
        elif(response_type==6):
            global_vars.servo_command_index = msg&0xFF
            #print("Current servo command index : "+str(global_vars.servo_command_index))
            return 0
        
        elif(response_type==7):
            auto_move_axis = (msg>>8)&0b11
            if(auto_move_axis == 1):
                if((msg>>10)&1 == 0):
                    x_start_index = msg&0xFF
                    global_vars.auto_move_started |= 1
                    global_vars.auto_move_ended &= ~1
                    
                    #print("X started moving for index "+str(x_start_index))
                else:
                    x_start_index = msg&0xFF
                    global_vars.auto_move_started &= ~1
                    global_vars.auto_move_ended |= 1
                    
                    #print("X ended moving for index "+str(x_start_index))
                return 0
                
            elif(auto_move_axis == 2):
                if((msg>>10)&1 == 0):
                    y_start_index = msg&0xFF
                    global_vars.auto_move_started |= (1<<1)
                    global_vars.auto_move_ended &= ~(1<<1)
                    
                    #print("Y started moving for index "+str(y_start_index))
                else:
                    y_start_index = msg&0xFF
                    global_vars.auto_move_started &= ~(1<<1)
                    global_vars.auto_move_ended |= (1<<1)
                    
                    #print("Y ended moving for index "+str(y_start_index))
                return 0        
                    
            elif(auto_move_axis == 3):
                if((msg>>10)&1 == 0):
                    z_start_index = msg&0xFF
                    global_vars.auto_move_started |= (1<<2)
                    global_vars.auto_move_ended &= ~(1<<2)
                    
                    #print("Z started moving for index "+str(z_start_index))
                else:
                    z_start_index = msg&0xFF
                    global_vars.auto_move_started &= ~(1<<2)
                    global_vars.auto_move_ended |= (1<<2)
                    
                    #print("Z ended moving for index "+str(z_start_index))
                return 0
            
        else:
            print("Unknown Servo slave response type : "+str(response_type))
            return 1
        
    elif(slave_id == 3):
        #print("Z")
        if(response_type==0):
            global_vars.z_mod_restart = msg&1
            global_vars.z_mod_inputs = (msg>>4)&0b111
            global_vars.z_mod_outputs = (msg>>1)&0b111
            print("Z_mod outputs : "+str(bin(global_vars.z_mod_outputs)))
            print("Z_mod inputs : "+str(bin(global_vars.z_mod_inputs)))
            if(global_vars.z_mod_restart==1):
                print("z_mod has restarted")
                pass
            interface.update_ui_var("ZMOD_INPUTS")
            interface.update_ui_var("ZMOD_OUTPUTS")
            return 0
        
    else:
        print("responding slave not recognised")
        print("slave id : " +str(bin(slave_id)))
        print("msg : "+str(bin(msg)))
        return 1
                          
