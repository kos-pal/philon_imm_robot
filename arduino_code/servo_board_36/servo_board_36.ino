
//#define INIT_EEPROM     //have to run it at once on every new arduino


//defines for pin setup
#define SET_RS485_CONTR_OUTPUT    DDRD|=(1<<2)
#define SET_SLAVE_R_INPUT         DDRD&=~(1<<3)
#define SET_SLAVE_R_OUTPUT        DDRD|=(1<<3)
#define SET_Z_PULSE_OUTPUT        DDRD|=(1<<6)
#define SET_Y_PULSE_OUTPUT        DDRB|=(1<<1)
#define SET_X_PULSE_OUTPUT        DDRB|=(1<<3)
#define SET_Z_DIR_OUTPUT          DDRD|=(1<<4)
#define SET_Y_DIR_OUTPUT          DDRB|=(1)
#define SET_X_DIR_OUTPUT          DDRB|=(1<<4)
#define SET_Z_COMPL_PULLUP        PORTD|=(1<<5)
#define SET_Y_COMPL_PULLUP        PORTB|=(1<<2) 
#define SET_X_COMPL_PULLUP        PORTC|=(1)
#define SET_Z_COMPL_INPUT         DDRD&=~(1<<5)
#define SET_Y_COMPL_INPUT         DDRB&=~(1<<2)  
#define SET_X_COMPL_INPUT         DDRC&=~(1)
#define SET_Z_COMPL_OUTPUT        DDRD|=(1<<5)
#define SET_Y_COMPL_OUTPUT        DDRB|=(1<<2)
#define SET_X_COMPL_OUTPUT        DDRC|=(1)
#define SET_Z_BRAKE_OUTPUT        DDRD|=(1<<7)
#define SET_ALARM_INPUT_PULLUP    PORTC|=(1<<1)


//defines for pin outputs (set pin HIGH)
#define RS485_CONTROL_PIN_HIGH      PORTD|=(1<<2)
#define SLAVE_R_HIGH              PORTD|=(1<<3)
#define X_PULSE_PIN_HIGH            PORTB|=(1<<3)
#define Y_PULSE_PIN_HIGH            PORTB|=(1<<1)
#define Z_PULSE_PIN_HIGH            PORTD|=(1<<6)
#define X_DIR_PIN_HIGH              PORTB|=(1<<4)
#define Y_DIR_PIN_HIGH              PORTB|=(1)
#define Z_DIR_PIN_HIGH              PORTD|=(1<<4)
#define Z_AXIS_BRAKE_DISABLE        PORTD|=(1<<7) 
#define X_AXIS_MOVE_COMPL_PIN_HIGH  PORTC|=1
#define Y_AXIS_MOVE_COMPL_PIN_HIGH  PORTB|=(1<<2)
#define Z_AXIS_MOVE_COMPL_PIN_HIGH  PORTD|=(1<<5)


//defines for pin outputs (set pin LOW)
#define RS485_CONTROL_PIN_LOW       PORTD&=~(1<<2)
#define SLAVE_R_LOW               PORTD&=~(1<<3)
#define X_PULSE_PIN_LOW             PORTB&=~(1<<3)   
#define Y_PULSE_PIN_LOW             PORTB&=~(1<<1)
#define Z_PULSE_PIN_LOW             PORTD&=~(1<<6)
#define X_DIR_PIN_LOW               PORTB&=~(1<<4)
#define Y_DIR_PIN_LOW               PORTB&=~(1)
#define Z_DIR_PIN_LOW               PORTD&=~(1<<4)
#define Z_AXIS_BRAKE_ENABLE         PORTD&=~(1<<7)
#define X_AXIS_MOVE_COMPL_PIN_LOW   PORTC&=~1
#define Y_AXIS_MOVE_COMPL_PIN_LOW   PORTB&=~(1<<2)
#define Z_AXIS_MOVE_COMPL_PIN_LOW   PORTD&=~(1<<5)


//defines for pin inputs (returns 0 for LOW and 1 for HIGH)
#define SLAVE_R_PIN_CHECK           ((PIND>>3)&1)
#define X_AXIS_MOVE_COMPL_PIN_CHECK ((PINC&1))
#define Y_AXIS_MOVE_COMPL_PIN_CHECK ((PINB>>2)&1)
#define Z_AXIS_MOVE_COMPL_PIN_CHECK ((PIND>>5)&1)
#define ALARM_PIN_CHECK             ((PINC>>1)&1)
#define X_AXIS_INDUCTIVE_PIN_CHECK  ((PINC>>4)&1)
#define Y_AXIS_INDUCTIVE_PIN_CHECK  ((PINC>>3)&1)
#define Z_AXIS_INDUCTIVE_PIN_CHECK  ((PINC>>2)&1)
#define X_PULSE_PIN_CHECK           ((PINB>>3)&1)
#define Y_PULSE_PIN_CHECK           ((PINB>>1)&1)
#define Z_PULSE_PIN_CHECK           ((PIND>>6)&1)


#define ARDUINO_CLOCK_IN_HZ 16000000    //get_prescaler_for_axis() has to change if we
                                        //want to support different clock speeds


//#define DEBUGGING
#ifdef DEBUGGING
  #define DEBUG_SERIAL(x)         Serial.print(x)
  #define DEBUG_SERIAL_LN(x)      Serial.println(x)
  #define DEBUG_SERIAL_BIN(x)     Serial.print(x,BIN)
  #define DEBUG_SERIAL_LN_BIN(x)  Serial.println(x,BIN)
  #define DEBUG_SERIAL_FLUSH      Serial.flush()
#else
  #define DEBUG_SERIAL(x)
  #define DEBUG_SERIAL_LN(x)
  #define DEBUG_SERIAL_BIN(x)
  #define DEBUG_SERIAL_LN_BIN(x)
  #define DEBUG_SERIAL_FLUSH
#endif


//default servo parameter values
#define VERSION_INT_VAL 0
#define VERSION_FRACT_VAL 1
#define ARDUINO_ID_VAL 2
#define X_PULSES_PER_REV_VAL 100
#define Y_PULSES_PER_REV_VAL 100
#define Z_PULSES_PER_REV_VAL 100
#define ACCEL_FILTER_MS_VAL 100
#define MAX_RPM_VAL 3000
#define ZEROING_SPEED_VAL 5   //5% of MAX_RPM
#define X_GEAR_RATIO_VAL 20
#define Y_GEAR_RATIO_VAL 10
#define Z_GEAR_RATIO_VAL 10
#define MM_PER_PULLEY_ROTATION_VAL 200
#define X_MM_PER_PULLEY_ROT_VAL 200
#define Y_MM_PER_PULLEY_ROT_VAL 200
#define Z_MM_PER_PULLEY_ROT_VAL 200
#define X_MM_LEN_VAL 1000
#define Y_MM_LEN_VAL 300
#define Z_MM_LEN_VAL 740
#define NO_COMPL_FEED_VAL 0b100   //bit2: z axis, bit1: y axis , bit0: x axis
                              //defines if an axis misses a movement complete pin
                              //if a bit is set to 1 , the corresponding pin will be set 
                              //as an output, so disconnect any cables to that pin
#define X_COMPL_DELAY_MS_VAL  200
#define Y_COMPL_DELAY_MS_VAL  300
#define Z_COMPL_DELAY_MS_VAL  400


//parameter indexes defines
#define VERSION_INT           0
#define VERSION_FRACT         1
#define ARDUINO_ID            2
#define ZEROING_SPEED         3
#define X_GEAR_RATIO          4
#define Y_GEAR_RATIO          5
#define Z_GEAR_RATIO          6
#define NO_COMPL_FEED         7
#define X_PULSES_PER_REV      8   
#define Y_PULSES_PER_REV      9   
#define Z_PULSES_PER_REV      10 
#define MAX_RPM               11  
#define X_MM_PER_PULLEY_ROT   12 
#define Y_MM_PER_PULLEY_ROT   13  
#define Z_MM_PER_PULLEY_ROT   14  
#define X_MM_LEN              15  
#define Y_MM_LEN              16 
#define Z_MM_LEN              17  
#define X_COMPL_DELAY_MS      18  
#define Y_COMPL_DELAY_MS      19 
#define Z_COMPL_DELAY_MS      20  



#define PARAM_INDEX_NUM         21
//EEPROM base addresses
#define SINGLE_BYTE_PARAM_BASE  500
#define TWO_BYTE_PARAM_BASE     550
#define TWO_BYTE_PARAM_START    8


#define AUTO_MOVE_CHECK (DELAY_SAVED_COM != 1201 )


//servo_params struct defines
#define X_NO_COMPL_FEED_CHECK  (servo_params.no_compl_feed&1)
#define Y_NO_COMPL_FEED_CHECK  ((servo_params.no_compl_feed>>1)&1)
#define Z_NO_COMPL_FEED_CHECK  ((servo_params.no_compl_feed>>2)&1)


//defines to get Move struct data  from Saved_commands.move_info (saved data in EEPROM)
#define END_MM_SAVED_COM      ((saved_commands.move_info[saved_commands.index]>>7)&0x7FF) 
#define SERVO_SPEED_SAVED_COM (saved_commands.move_info[saved_commands.index]&0x7F)
#define AXIS_SAVED_COM        ((saved_commands.move_info[saved_commands.index]>>19)&0b11)
#define SIGN_SAVED_COM        (1-(2*((saved_commands.move_info[saved_commands.index]>>18)&1)))
#define DELAY_SAVED_COM       (saved_commands.delay_info[saved_commands.index])  
//defines to get Move struct data from serial
#define END_MM_SERIAL   ((serial_data>>7)&0x7FF)
#define SERVO_SPEED_SERIAL (serial_data&0x7F)
#define AXIS_SERIAL       ((serial_data>>19)&0b11)
#define SIGN_SERIAL       (1-(2*((serial_data>>18)&1)))


//Servo_board.servo_status set defines
#define AUTO_TRIGGER_SET   servo_board.servo_status|=(1<<15)
#define ALL_AXES_ZEROING_SET    servo_board.servo_status|=(0b111<<12)
#define ZEROING_Z_SET           servo_board.servo_status|=(1<<14)
#define ZEROING_Y_SET           servo_board.servo_status|=(1<<13)
#define ZEROING_X_SET           servo_board.servo_status|=(1<<12)
#define ALL_AXES_DIR_SET        servo_board.servo_status|=(0b111<<9)
#define Z_AXIS_DIR_SET          servo_board.servo_status|=(1<<11)
#define Y_AXIS_DIR_SET          servo_board.servo_status|=(1<<10)
#define X_AXIS_DIR_SET          servo_board.servo_status|=(1<<9)
#define Z_AXIS_INDUCTIVE_SET    servo_board.servo_status|=(1<<8)
#define Y_AXIS_INDUCTIVE_SET    servo_board.servo_status|=(1<<7)
#define X_AXIS_INDUCTIVE_SET    servo_board.servo_status|=(1<<6)
#define ALL_AXES_MOVE_END_SET   servo_board.servo_status|=(0b111<<3)
#define Z_AXIS_MOVE_END_SET     servo_board.servo_status|=(1<<5)
#define Y_AXIS_MOVE_END_SET     servo_board.servo_status|=(1<<4)
#define X_AXIS_MOVE_END_SET     servo_board.servo_status|=(1<<3)
#define ALL_AXES_MOVE_START_SET servo_board.servo_status|=(0b111)
#define Z_AXIS_MOVE_START_SET   servo_board.servo_status|=(1<<2)
#define Y_AXIS_MOVE_START_SET   servo_board.servo_status|=(1<<1)
#define X_AXIS_MOVE_START_SET   servo_board.servo_status|=(1<<0)
//Servo_board.servo_status reset defines
#define AUTO_TRIGGER_RESET   servo_board.servo_status&=~(1<<15)
#define ALL_AXES_ZEROING_RESET    servo_board.servo_status&=~(0b111<<12)
#define ZEROING_Z_RESET           servo_board.servo_status&=~(1<<14)
#define ZEROING_Y_RESET           servo_board.servo_status&=~(1<<13)
#define ZEROING_X_RESET           servo_board.servo_status&=~(1<<12)
#define ALL_AXES_DIR_RESET        servo_board.servo_status&=~(0b111<<9)
#define Z_AXIS_DIR_RESET          servo_board.servo_status&=~(1<<11)
#define Y_AXIS_DIR_RESET          servo_board.servo_status&=~(1<<10)
#define X_AXIS_DIR_RESET          servo_board.servo_status&=~(1<<9)
#define Z_AXIS_INDUCTIVE_RESET    servo_board.servo_status&=~(1<<8)
#define Y_AXIS_INDUCTIVE_RESET    servo_board.servo_status&=~(1<<7)
#define X_AXIS_INDUCTIVE_RESET    servo_board.servo_status&=~(1<<6)
#define ALL_AXES_MOVE_END_RESET   servo_board.servo_status&=~(0b111<<3)
#define Z_AXIS_MOVE_END_RESET     servo_board.servo_status&=~(1<<5)
#define Y_AXIS_MOVE_END_RESET     servo_board.servo_status&=~(1<<4)
#define X_AXIS_MOVE_END_RESET     servo_board.servo_status&=~(1<<3)
#define ALL_AXES_MOVE_START_RESET servo_board.servo_status&=~(0b111)
#define Z_AXIS_MOVE_START_RESET   servo_board.servo_status&=~(1<<2)
#define Y_AXIS_MOVE_START_RESET   servo_board.servo_status&=~(1<<1)
#define X_AXIS_MOVE_START_RESET   servo_board.servo_status&=~(1<<0)
//Servo_board.servo_status set/reset based on Move.axis
#define AXIS_MOVE_START_SET servo_board.servo_status|=(1<<((req_move->axis)-1))  //sets @_AXIS_MOVE_START bit in servo_status based on req_move->axis
#define AXIS_MOVE_START_RESET servo_board.servo_status&=~(1<<((req_move->axis)-1))  //resets @_AXIS_MOVE_START bit in servo_status based on req_move->axis
#define AXIS_MOVE_END_SET servo_board.servo_status|=(1<<((req_move->axis)+2))  //sets @AXIS_MOVE_END bit in servo_status based on req_move->axis
#define AXIS_MOVE_END_RESET servo_board.servo_status&=~(1<<((req_move->axis)+2))  //resets @AXIS_MOVE_END bit in servo_status based on req_move->axis
//servo_board.servo_status check if set defines
#define AUTO_TRIGGER_CHECK ((servo_board.servo_status>>15)&1)
#define ZEROING_Z_CHECK         ((servo_board.servo_status>>14)&1)
#define ZEROING_Y_CHECK         ((servo_board.servo_status>>13)&1)
#define ZEROING_X_CHECK         ((servo_board.servo_status>>12)&1)
//#define ZEROING_AXES_CHECK       ((servo_board.servo_status>>12)&1)
#define Z_AXIS_DIR_CHECK        ((servo_board.servo_status>>11)& 1)
#define Y_AXIS_DIR_CHECK        ((servo_board.servo_status>>10)& 1)
#define X_AXIS_DIR_CHECK        ((servo_board.servo_status>>9)&1)
#define Z_AXIS_INDUCTIVE_CHECK  ((servo_board.servo_status>>8)&1)
#define Y_AXIS_INDUCTIVE_CHECK  ((servo_board.servo_status>>7)&1)
#define X_AXIS_INDUCTIVE_CHECK  ((servo_board.servo_status>>6)&1)
#define Z_AXIS_MOVE_END_CHECK   ((servo_board.servo_status>>5)&1)
#define Y_AXIS_MOVE_END_CHECK   ((servo_board.servo_status>>4)&1)
#define X_AXIS_MOVE_END_CHECK   ((servo_board.servo_status>>3)&1)
#define Z_AXIS_MOVE_START_CHECK ((servo_board.servo_status>>2)&1)
#define Y_AXIS_MOVE_START_CHECK ((servo_board.servo_status>>1)&1)
#define X_AXIS_MOVE_START_CHECK (servo_board.servo_status&1)
//check if axis is moving based on req_move->axis
#define AXIS_MOVE_START_CHECK (((servo_board.servo_status&0b111)>>(req_move->axis-1))&1)  
//check if axis is moving based on current_move.axis
#define AXIS_MOVE_START_CURRENT_CHECK (((servo_board.servo_status&0b111)>>(current_move.axis-1))&1)  
//check if axis is zeroing based on req_move->axis
#define AXIS_ZEROING_CHECK ((((servo_board.servo_status>>12)&0b111)>>(req_move->axis-1))&1)  


//Servo_board.error set defines
#define LOOP_ERROR_SET            servo_board.error|=(1<<7)
#define SERVO_RESTART_SET         servo_board.error|=(1<<6)
#define AXES_NOT_ZEROED_SET       servo_board.error|=(1<<5)
#define AXIS_ALREADY_MOVING_SET   servo_board.error|=(1<<4)
#define SERVO_NOT_AT_ORIGIN_SET   servo_board.error|=(1<<3)
#define INVALID_MODE_SET          servo_board.error|=(1<<2)
#define MOVE_OUT_OF_BOUNDS_SET    servo_board.error|=(1<<1)
#define ALARM_SET                 servo_board.error|=(1)
//Servo_board.error reset defines
#define LOOP_ERROR_RESET            servo_board.error&=~(1<<7)
#define SERVO_RESTART_RESET         servo_board.error&=~(1<<6)
#define AXES_NOT_ZEROED_RESET       servo_board.error&=~(1<<5)
#define AXIS_ALREADY_MOVING_RESET   servo_board.error&=~(1<<4)
#define SERVO_NOT_AT_ORIGIN_RESET   servo_board.error&=~(1<<3)
#define INVALID_MODE_RESET          servo_board.error&=~(1<<2)
#define MOVE_OUT_OF_BOUNDS_RESET    servo_board.error&=~(1<<1)
#define ALARM_RESET                 servo_board.error&=~(1)
#define RESET_ERROR_REPORT          servo_board.error&=~(0b01011110)
//Servo_board.error check if set defines
#define LOOP_ERROR_CHECK              ((servo_board.error>>7)&1)
#define AXES_NOT_ZEROED_CHECK         ((servo_board.error>>5)&1)
#define ALARM_CHECK                   (servo_board.error & 1)


//servo_board.com_status set defines
#define COM_SLAVE_CONTROL_SET     servo_board.com_status|=(1<<2)
#define COM_MASTER_CONTROL_SET    servo_board.com_status|=(1<<1)
#define COM_SERIAL_BUSY_SET       servo_board.com_status|=(1)
//servo_board.com_status reset defines 
#define COM_SLAVE_CONTROL_RESET     servo_board.com_status&=~(1<<2)
#define COM_MASTER_CONTROL_RESET    servo_board.com_status&=~(1<<1)
#define COM_SERIAL_BUSY_RESET       servo_board.com_status&=~(1)
//servo_board.com_status check if set defines
#define COM_SLAVE_CONTROL_CHECK     ((servo_board.com_status>>2)&1)
#define COM_MASTER_CONTROL_CHECK    ((servo_board.com_status>>1)&1)
#define COM_SERIAL_BUSY_CHECK       (servo_board.com_status & 1)


//servo_board.mode check defines
#define MANUAL_MODE_CHECK     (servo_board.mode==0)
#define AUTO_MODE_CHECK       (servo_board.mode==1)
#define SERVICE_MODE_CHECK    (servo_board.mode==2)


//servo_board.timer_status set defines
#define TIMER0_PRESCALER_SAVE(x)    (servo_board.timer_status|=x<<6)
#define TIMER1_PRESCALER_SAVE(x)    (servo_board.timer_status|=x<<3)
#define TIMER2_PRESCALER_SAVE(x)    (servo_board.timer_status|=x)
#define TIMER0_PRESCALER_RESET      (servo_board.timer_status&=~(0b111<<6))
#define TIMER1_PRESCALER_RESET      (servo_board.timer_status&=~(0b111<<3))
#define TIMER2_PRESCALER_RESET      (servo_board.timer_status&=~0b111)
#define TIMER0_PRESCALER_CHECK      ((servo_board.timer_status>>6)&0b111)
#define TIMER1_PRESCALER_CHECK      ((servo_board.timer_status>>3)&0b111)
#define TIMER2_PRESCALER_CHECK      (servo_board.timer_status&0b111)


//interrupt setup defines
#define ENABLE_INT_MASK         EIMSK|=(1<<1)
#define DISABLE_INT_MASK        EIMSK&=~(1<<1)
#define RESET_INT_FLAG          EIFR|=(1<<1)
#define SET_FALLING_EDGE_TRIG   EICRA=(0b10<<2)
#define SET_RISING_EDGE_TRIG    EICRA=(0b11<<2)


//INT1 defines
#define RESPONSE_LENGTH       ((current_response>>27)&0b11) 
#define RESPONSE_OPERATION    ((current_response>>24)&0b111)
#define RESPONSE_FIRST_BYTE   (current_response>>24)
#define REPORT_PARAMS   (0b100)


//add_com_response defines
#define REPORT_STATUS               (0)
#define REPORT_X                    (0b1)
#define REPORT_Y                    (0b10)
#define REPORT_Z                    (0b11)
#define REPORT_PARAMS               (0b100)
#define REPORT_MODE                 (0b101)
#define REPORT_INDEX                (0b110)
#define REPORT_X_START_AUTO         (0b1000)
#define REPORT_X_END_AUTO           (0b1001)
#define REPORT_Y_START_AUTO         (0b1010)
#define REPORT_Y_END_AUTO           (0b1011)
#define REPORT_Z_START_AUTO         (0b1100)
#define REPORT_Z_END_AUTO           (0b1101)
#define REPORT_STATUS_RESPONSE      ((((uint32_t)((ARDUINO_ID<<5)|(0b11<<3)))<<24)|((uint32_t)(servo_board.error)<<16)|servo_board.servo_status)
#define REPORT_X_RESPONSE           ((((uint32_t)((ARDUINO_ID<<5)|0b10001))<<24)|((servo_position.toggles_x/servo_params.x_toggles_mm_mult)&0xFFFF))
#define REPORT_Y_RESPONSE           ((((uint32_t)((ARDUINO_ID<<5)|0b10010))<<24)|((servo_position.toggles_y/servo_params.y_toggles_mm_mult)&0xFFFF))
#define REPORT_Z_RESPONSE           ((((uint32_t)((ARDUINO_ID<<5)|0b10011))<<24)|((servo_position.toggles_z/servo_params.z_toggles_mm_mult)&0xFFFF))
#define REPORT_PARAMS_RESPONSE      ((((uint32_t)((ARDUINO_ID<<5)|0b11100))<<24)|((uint32_t)param_index<<16)|(param_high_byte<<8)|(param_low_byte))
#define REPORT_MODE_RESPONSE        ((((uint32_t)((ARDUINO_ID<<5)|0b01101))<<24)|servo_board.mode)
#define REPORT_INDEX_RESPONSE       ((((uint32_t)((ARDUINO_ID<<5)|0b01110))<<24)|saved_commands.index)
#define REPORT_X_START_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(1<<8)|saved_commands.x_auto_start_index) 
#define REPORT_X_END_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(1<<10)|(1<<8)|saved_commands.x_auto_start_index) 
#define REPORT_Y_START_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(0b10<<8)|saved_commands.y_auto_start_index) 
#define REPORT_Y_END_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(1<<10)|(0b10<<8)|saved_commands.y_auto_start_index) 
#define REPORT_Z_START_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(0b11<<8)|saved_commands.z_auto_start_index) 
#define REPORT_Z_END_AUTO_RESPONSE  ((((uint32_t)((ARDUINO_ID<<5)|0b10111))<<24)|(1<<10)|(0b11<<8)|saved_commands.z_auto_start_index) 


//check_inductive_sensors  defines
#define Z_RESET_POSITION_FLAG_SET   zeroed_axes |=(1<<5)
#define Y_RESET_POSITION_FLAG_SET   zeroed_axes |=(1<<4)
#define X_RESET_POSITION_FLAG_SET   zeroed_axes |=(1<<3)
#define Z_ZEROED_SET                zeroed_axes |=(1<<2)
#define Y_ZEROED_SET                zeroed_axes |=(1<<1)
#define X_ZEROED_SET                zeroed_axes |=(1)
//check_inductive_sensors reset defines
#define Z_RESET_POSITION_FLAG_RESET   zeroed_axes &=~(1<<5)
#define Y_RESET_POSITION_FLAG_RESET   zeroed_axes &=~(1<<4)
#define X_RESET_POSITION_FLAG_RESET   zeroed_axes &=~(1<<3)
#define Z_ZEROED_RESET                zeroed_axes &=~(1<<2)
#define Y_ZEROED_RESET                zeroed_axes &=~(1<<1)
#define X_ZEROED_RESET                zeroed_axes &=~(1)
//check_inductive_sensors check defines
#define Z_RESET_POSITION_FLAG_CHECK   ((zeroed_axes>>5)&1)
#define Y_RESET_POSITION_FLAG_CHECK   ((zeroed_axes>>4)&1)
#define X_RESET_POSITION_FLAG_CHECK   ((zeroed_axes>>3)&1)
#define Z_ZEROED_CHECK                ((zeroed_axes>>2)&1)
#define Y_ZEROED_CHECK                ((zeroed_axes>>1)&1)
#define X_ZEROED_CHECK                (zeroed_axes&1)



//defines for flags required to inform master that a move was complete in auto mode
#define Z_AT_POS_SENT_SET   (axes_messages_flags|=(1<<2))
#define Y_AT_POS_SENT_SET   (axes_messages_flags|=(1<<1))
#define X_AT_POS_SENT_SET   (axes_messages_flags|=1)
#define Z_AT_POS_SENT_RESET (axes_messages_flags&=~(1<<2))
#define Y_AT_POS_SENT_RESET (axes_messages_flags&=~(1<<1))
#define X_AT_POS_SENT_RESET (axes_messages_flags&=~1)
#define Z_AT_POS_SENT_CHECK ((axes_messages_flags>>2)&1)
#define Y_AT_POS_SENT_CHECK ((axes_messages_flags>>1)&1)
#define X_AT_POS_SENT_CHECK (axes_messages_flags&1)



//handle_program_operation defines
#define PROG_OP_ID              (serial_data>>((8*(message_length-1))+5))&0b111
#define COMMANDS_NUM            (serial_data&0x7F)
#define COMMAND_INDEX           (serial_data&0xFF)
#define MOVE_INFO               (serial_data&0x1FFFFF)
#define DELAY_INFO              (serial_data&0x7FF)
#define PARAMETER_INDEX         ((serial_data>>16)&0b11111)
#define PARAMETER_VALUE_HIGH    ((serial_data>>8)&0xFF)
#define PARAMETER_VALUE_LOW     (serial_data&0xFF)
 


//handle_serial defines
#define ACK_OPERATION            0b111
#define ACK_ID                  (inc_data & 0b111)

#define SERIAL_ID       (inc_data>>5)
#define SERIAL_MESSAGE_LENGHT  ((inc_data>>3)&0b11)
#define SERIAL_OPERATION       (inc_data & 0b111)
#define RESPONSE_TYPE_SERIAL (serial_info.inc_data&0b111)
#define NO_INCR_STOP_SET      index_no_incr|=(1<<1)   //prevents incrementing index after a stop command
#define NO_INCR_ZERO_SET      index_no_incr|=1        //prevents incrementing index when its 0
#define NO_INCR_STOP_RESET    index_no_incr&=~(1<<1)
#define NO_INCR_ZERO_RESET    index_no_incr&=~1
#define NO_INCR_STOP_CHECK    ((index_no_incr>>1)&1)
#define NO_INCR_ZERO_CHECK     (index_no_incr&1)
#define X_IN_CORRECT_POSITION  (servo_position.toggles_x/servo_params.x_toggles_mm_mult==auto_mode_positions.x_position)
#define Y_IN_CORRECT_POSITION  (servo_position.toggles_y/servo_params.y_toggles_mm_mult==auto_mode_positions.y_position)
#define Z_IN_CORRECT_POSITION  (servo_position.toggles_z/servo_params.z_toggles_mm_mult==auto_mode_positions.z_position)



//structs declarations

typedef struct{
  uint8_t  version_int;
  uint8_t  version_fract;
  uint8_t  arduino_id;
  uint8_t  zeroing_speed;
  uint16_t x_mm_len;
  uint16_t y_mm_len;
  uint16_t z_mm_len;
  uint8_t  no_compl_feed;
  uint16_t x_compl_delay_ms;
  uint16_t y_compl_delay_ms;
  uint16_t z_compl_delay_ms;
  uint16_t x_toggles_mm_mult; //multiply mm by this value to get required toggles
                              //divide toggles with this value to get corresponding mm
  uint16_t y_toggles_mm_mult;
  uint16_t z_toggles_mm_mult;
  uint32_t x_freq_const;
  uint32_t y_freq_const;
  uint32_t z_freq_const;       
}Servo_params;

typedef struct{
  volatile int32_t toggles_x;     
  volatile int32_t toggles_end_x;
  volatile int32_t toggles_y;
  volatile int32_t toggles_end_y;
  volatile int32_t toggles_z;
  volatile int32_t toggles_end_z;
}Servo_position;

typedef struct{
  volatile uint16_t servo_status;  
  volatile uint8_t  error;
  volatile uint8_t  com_status;     
  volatile uint32_t com_response[10];
  uint32_t last_response;
  volatile uint8_t  response_index;
  uint8_t           mode;
  volatile uint16_t timer_status;
}Servo_board;

typedef struct {
  uint32_t move_info[60]; //bits according to move axis operation
  
  uint16_t delay_info[60]; //if 1201 , next command executes when master triggers a next move
                           //if not , next move starts after that many mm have completed
                           //in the current move
                           
  uint8_t index;          
                          
  uint8_t num;   
  uint8_t x_auto_start_index;
  uint8_t y_auto_start_index;
  uint8_t z_auto_start_index;              
}Saved_commands;

typedef struct{
  int16_t end_mm;
  uint8_t servo_speed;
  uint8_t axis;
  int16_t next_trigger;
}Abs_move;

typedef struct{
  uint8_t  ignore_bytes;
  uint8_t  message_length;
  uint8_t  index;
  uint8_t  operation;
  uint32_t inc_data;
  uint8_t  ack_received;
}Serial_info;

typedef struct{
  uint8_t prescaler_bin;
  uint16_t prescaler;
}Prescaler_info;

typedef struct{
  uint16_t x_position;
  uint16_t y_position;
  uint16_t z_position;
}Auto_mode_positions;





//function declarations
void init_servo_board(uint32_t baud_rate);
void servo_board_update();
void add_com_response(uint8_t response_type);

void eeprom_write(uint16_t eeprom_addr , uint8_t eeprom_data);
uint8_t eeprom_read(uint16_t eeprom_addr);
void add_com_response(uint8_t response_type);
void remove_com_response();
void get_prescaler_for_axis(float freq , uint8_t axis,Prescaler_info *prescaler_info);
void move_axis_pulses(uint8_t axis, int32_t toggles);
int8_t move_abs_pos(Abs_move * req_move);
void check_alarm();
void check_movement_end();
void stop_motor(uint8_t axis);
void check_inductive_sensors();
void zero_axes(uint8_t selected_axes);
void execute_auto_move(uint8_t evaluate_positions_flag);
void handle_program_operation(uint32_t serial_data,uint8_t message_length);
void handle_move_operation(uint32_t serial_data);
void handle_servo_response();
void handle_serial();
void init_EEPROM();
void calculate_servo_params();
void init_servo_board(uint32_t baud_rate);
void servo_board_update();



//define global variables
Servo_board servo_board;  
Servo_position servo_position;
Saved_commands saved_commands;
Servo_params servo_params;
uint16_t timer2_b_triggers; //timer 2 counts of 1ms
uint16_t timer1_b_triggers; //timer 1 counts of 1ms
uint16_t timer0_b_triggers; //timer 0 counts of 1ms



void transmit_response(uint8_t repeat_flag){

  static uint8_t params_byte_index;
  static uint8_t response_operation;
  uint32_t current_response;
  uint8_t response_bytes[4];
  if(repeat_flag == 0){
    current_response = servo_board.com_response[0]; 
  }else{
    current_response = servo_board.last_response;
  }
  response_bytes[0] = RESPONSE_FIRST_BYTE;
  response_operation = RESPONSE_OPERATION;
  for(int i = 0 ; i < RESPONSE_LENGTH ; i++){
    response_bytes[i+1] = (current_response>>(8*(RESPONSE_LENGTH-(i+1)))) & 0xFF ;
  }
  DEBUG_SERIAL_FLUSH;
  #ifndef DEBUGGING
  Serial.flush();
  #endif

  //disable all timers so that they won't tick while the message is being sent
  TCCR2B&=~(0b111);
  TCCR1B&=~(0b111);
  TCCR0B&=~(0b111);

  //disable interrupts
  uint8_t temp_sreg = SREG;
  cli();
  
  RS485_CONTROL_PIN_HIGH; //set RS485 IC to transmiter mode
  for( int i = 0 ; i< RESPONSE_LENGTH+1 ; i++){
    Serial.write(response_bytes[i]);  
  }
  DEBUG_SERIAL_FLUSH;
  #ifndef DEBUGGING
  Serial.flush();
  #endif
  RS485_CONTROL_PIN_LOW; //set RS485 to receiver mode

  //enable interrupts
  //Restore SREG
  SREG = temp_sreg;

  
  TCCR2B |= TIMER2_PRESCALER_CHECK; 
  TCCR1B |= TIMER1_PRESCALER_CHECK;   
  TCCR0B |= TIMER0_PRESCALER_CHECK;  

  if(repeat_flag == 0){
    //store the response in case the master requests it again
    servo_board.last_response = servo_board.com_response[0];
    
    //remove the response that was sent to the master from the array
    for(int i = 0 ; i < servo_board.response_index - 1; i++){
      servo_board.com_response[i] = servo_board.com_response[i+1];  //replace each response with the next in line
    }
    servo_board.com_response[servo_board.response_index-1] = 0; //delete the command pointed at by the index
    servo_board.response_index--; //decrement the index  
    if( response_operation == REPORT_PARAMS ){
      params_byte_index++;
      if( params_byte_index < PARAM_INDEX_NUM ){
        add_com_response(REPORT_PARAMS);
      }else{
        params_byte_index = 0;
      }
    }

  }
  

  
}



//ISRs that handle pulses to the servo motors
ISR(TIMER2_COMPA_vect){
  //check x axis direction from servo_status (9th bit)
  if(X_AXIS_DIR_CHECK==0){
    servo_position.toggles_x++;
    if(servo_position.toggles_x == servo_position.toggles_end_x){
      TCCR2B &= ~(0b111); //stop TIMER2
      TIMER2_PRESCALER_RESET; //update servo_board.timer_status 
      X_AXIS_MOVE_START_RESET;
      X_AXIS_MOVE_END_RESET;
      if( X_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR2A &= ~(1<<6);  // disconnect OC0A
        OCR2A = 255;  //in CTC mode OCR2A functions as TOP , has to be higher than OCR2B
        OCR2B = 249;
        TIFR2 |= 0b111; //clear all the flags
        TIMSK2 = 0b100;
        TIMER2_PRESCALER_SAVE(0b100); //update servo_board.timer_status 
        TCCR2B |= 0b100;  //start timer with 64 prescaler
      }
    }   
  }else{
    servo_position.toggles_x--;
    if(servo_position.toggles_x == servo_position.toggles_end_x){
      TCCR2B &= ~(0b111); //stop TIMER2
      TIMER2_PRESCALER_RESET; //update servo_board.timer_status 
      X_AXIS_MOVE_START_RESET;
      X_AXIS_MOVE_END_RESET;
      if( X_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR2A &= ~(1<<6);  // disconnect OC0A
        OCR2A = 255;  //in CTC mode OCR2A functions as TOP , has to be higher than OCR2B
        OCR2B = 249;
        TIFR2 |= 0b111; //clear all the flags
        TIMSK2 = 0b100;
        TIMER2_PRESCALER_SAVE(0b100); //update servo_board.timer_status 
        TCCR2B |= 0b100;  //start timer with 64 prescaler
      }
    }       
  } 
}

ISR(TIMER1_COMPA_vect){
  //check y axis direction from servo_status (10th bit)
  if(Y_AXIS_DIR_CHECK==0){
    servo_position.toggles_y++;
    if(servo_position.toggles_y == servo_position.toggles_end_y){
      TCCR1B &= ~(0b111); //stop TIMER1
      TIMER1_PRESCALER_RESET;
      Y_AXIS_MOVE_START_RESET;
      Y_AXIS_MOVE_END_RESET;
      if( Y_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR1A &= ~(1<<6);  // disconnect OC1A
        OCR1A = 255;  //in CTC mode OCR1A functions as TOP , has to be higher than OCR1B
        OCR1B = 249;
        TIFR1 |= 0b111; //clear all the flags
        TIMSK1 = 0b100;
        TIMER1_PRESCALER_SAVE(0b11);
        TCCR1B |= 0b11;  //start timer with 64 prescaler
      }
    }   
  }else{
    servo_position.toggles_y--;
    if(servo_position.toggles_y == servo_position.toggles_end_y){
      TCCR1B &= ~(0b111); //stop TIMER1
      TIMER1_PRESCALER_RESET;
      Y_AXIS_MOVE_START_RESET;
      Y_AXIS_MOVE_END_RESET;
      if( Y_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR1A &= ~(1<<6);  // disconnect OC1A
        OCR1A = 255;  //in CTC mode OCR1A functions as TOP , has to be higher than OCR1B
        OCR1B = 249;
        TIFR1 |= 0b111; //clear all the flags
        TIMSK1 = 0b100;
        TIMER1_PRESCALER_SAVE(0b11);
        TCCR1B |= 0b11;  //start timer with 64 prescaler
      }
    }       
  } 
} 

ISR(TIMER0_COMPA_vect){
  //check z axis direction from servo_status (11th bit)
  if(Z_AXIS_DIR_CHECK==0){
    servo_position.toggles_z++;
    if(servo_position.toggles_z == servo_position.toggles_end_z){
      TCCR0B &= ~(0b111); //stop TIMER0
      TIMER0_PRESCALER_RESET;
      Z_AXIS_MOVE_START_RESET;
      Z_AXIS_MOVE_END_RESET; 
      if( Z_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR0A &= ~(1<<6);  // disconnect OC1A
        OCR0A = 255;  //in CTC mode OCR0A functions as TOP , has to be higher than OCR0B
        OCR0B = 249;
        TIFR0 |= 0b111; //clear all the flags
        TIMSK0 = 0b100;
        TIMER0_PRESCALER_SAVE(0b11);
        
        //add_com_response(REPORT_X);
        TCCR0B |= 0b11;  //start timer with 64 prescaler
      }
    }   
  }else{
    servo_position.toggles_z--;
    if(servo_position.toggles_z == servo_position.toggles_end_z){
      TCCR0B &= ~(0b111); //stop TIMER0
      TIMER0_PRESCALER_RESET;
      Z_AXIS_MOVE_START_RESET;
      Z_AXIS_MOVE_END_RESET; 
      if( Z_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR0A &= ~(1<<6);  // disconnect OC1A
        OCR0A = 255;  //in CTC mode OCR0A functions as TOP , has to be higher than OCR0B
        OCR0B = 249;
        TIFR0 |= 0b111; //clear all the flags
        TIMSK0 = 0b100;
        TIMER0_PRESCALER_SAVE(0b11);
        //add_com_response(REPORT_Y);
        TCCR0B |= 0b11;  //start timer with 64 prescaler
      }
    }       
  } 
} 
//ISRs that handle the movement complete delay if pin is missing
ISR(TIMER2_COMPB_vect){
  timer2_b_triggers++;
  if(timer2_b_triggers >= servo_params.x_compl_delay_ms){
    TCCR2B &= ~(0b111); //stop TIMER2
    TIMER2_PRESCALER_RESET; //update servo_board.timer_status 
    timer2_b_triggers = 0;
    TIFR2 |= 0b111; //clear all the flags
    X_AXIS_MOVE_COMPL_PIN_LOW;  //triggers motion complete
  }
}

ISR(TIMER1_COMPB_vect){
  timer1_b_triggers++;
  if(timer1_b_triggers >= servo_params.y_compl_delay_ms){
    TCCR1B &= ~(0b111); //stop TIMER1
    TIMER1_PRESCALER_RESET;
    timer1_b_triggers = 0;
    TIFR1 |= 0b111; //clear all the flags
    Y_AXIS_MOVE_COMPL_PIN_LOW;  //triggers motion complete
  }
}

ISR(TIMER0_COMPB_vect){
  timer0_b_triggers++;
  if(timer0_b_triggers >= servo_params.z_compl_delay_ms){
    TCCR0B &= ~(0b111); //stop TIMER0
    //add_com_response(REPORT_Z);
    TIMER0_PRESCALER_RESET;
    timer0_b_triggers = 0;
    TIFR0 |= 0b111; //clear all the flags
    Z_AXIS_MOVE_COMPL_PIN_LOW;  //triggers motion complete
  }
}



//EEPROM functions
void eeprom_write(uint16_t eeprom_addr , uint8_t eeprom_data){
  while((EECR>>1)&1){
    //wait for EEPE bit on EECR register to clear --BLOCKING--  
  }
  while(SPMCSR & 1){
    //wait for SELFPRGEN bit on SPMCSR register to clear --BLOCKING--  
  }
  //write address to EEAR register
  EEARL = 0;
  EEARH = 0;
  EEARL |= eeprom_addr & 0xFF; //bottom 8 bits
  EEARH |= (eeprom_addr >> 8)&0b11;  //top 2 bits
  //write data to EEDR register
  EEDR = eeprom_data;
  //disable global interrupts
  uint8_t sreg_temp;
  sreg_temp = SREG;
  cli();
  //reset EEPE bit and set EEMPE bit
  EECR &= ~(1<<1);
  EECR |= 1<<2;
  //set EEPE bit to commit the write to EEPROM
  EECR |= 1<<1;
  //Restore SREG 
  SREG = sreg_temp;
}

  
uint8_t eeprom_read(uint16_t eeprom_addr){
  while((EECR>>1)&1){
    //while EEPE bit is set , do nothing ----BLOCKING----  
  }
  EEARL = 0;
  EEARH = 0;
  EEARL |= eeprom_addr & 0xFF; //bottom 8 bits
  EEARH |= (eeprom_addr >> 8)&0b11;  //top 2 bits
  EECR |= 1;  //set the EERE bit to trigger a read
  return EEDR;
}



//Response array handling functions
void add_com_response(uint8_t response_type){
  if(servo_board.response_index >= 10){
    //com_response[] is full, response will be lost, abort
    DEBUG_SERIAL_LN("servo_board.com_response[] is full, response lost");
    DEBUG_SERIAL_FLUSH;
    Serial.println("servo_board.com_response[] is full, response lost");
    Serial.flush();
    return ;  
  }
  //uint32_t servo_response;
  switch (response_type)
  {
    case REPORT_STATUS:
      servo_board.com_response[servo_board.response_index] = REPORT_STATUS_RESPONSE;
      RESET_ERROR_REPORT; //reset all errors appart from LOOP_ERROR , AXES_NOT_ZEROED and ALARM  
      break;
    case REPORT_X:
      servo_board.com_response[servo_board.response_index] =  REPORT_X_RESPONSE;
      break;
    case REPORT_Y:
      servo_board.com_response[servo_board.response_index] =  REPORT_Y_RESPONSE;
      break;   
    case REPORT_Z:
      servo_board.com_response[servo_board.response_index] =  REPORT_Z_RESPONSE;
      break;
    case REPORT_PARAMS:
      //curly brackets required because of variable declarations inside the case
      {
      static uint8_t param_index;
      uint8_t param_high_byte = 0;
      uint8_t param_low_byte = 0;
      if(param_index < TWO_BYTE_PARAM_START){
        param_low_byte = eeprom_read( SINGLE_BYTE_PARAM_BASE + param_index );
      }else{
        param_high_byte = eeprom_read( TWO_BYTE_PARAM_BASE + ((param_index - TWO_BYTE_PARAM_START)*2) );
        param_low_byte = eeprom_read( TWO_BYTE_PARAM_BASE + ((param_index - TWO_BYTE_PARAM_START)*2) + 1);
      }
      servo_board.com_response[servo_board.response_index] = REPORT_PARAMS_RESPONSE;
      param_index++;
      if(param_index == PARAM_INDEX_NUM){
        param_index = 0;
      }
      break ;
      }
    case REPORT_MODE:
      servo_board.com_response[servo_board.response_index] =  REPORT_MODE_RESPONSE;
      break; 
    case REPORT_INDEX:
      servo_board.com_response[servo_board.response_index] = REPORT_INDEX_RESPONSE;
      break;
    case REPORT_X_START_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_X_START_AUTO_RESPONSE;
      break;
    case REPORT_X_END_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_X_END_AUTO_RESPONSE;
      break;
    case REPORT_Y_START_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_Y_START_AUTO_RESPONSE;
      break;
    case REPORT_Y_END_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_Y_END_AUTO_RESPONSE;
      break;
    case REPORT_Z_START_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_Z_START_AUTO_RESPONSE;
      break;
    case REPORT_Z_END_AUTO:
      servo_board.com_response[servo_board.response_index] = REPORT_Z_END_AUTO_RESPONSE;
      break;
  }
  //increment index
  servo_board.response_index++;
}





//Prescaler calculation function
void get_prescaler_for_axis(float freq , uint8_t axis,Prescaler_info *prescaler_info){
  if( (freq < 31) || (freq > 8000000)){
    //requested rpm not possible ,return 0 to abort move command
    prescaler_info->prescaler_bin = 0;
    prescaler_info->prescaler = 0;
  }
  if(freq > 31250){
    //set prescaler to 1
    prescaler_info->prescaler_bin = 1;
    prescaler_info->prescaler = 1;
  }else if (freq > 3907){
    //set prescaler to 8
    prescaler_info->prescaler_bin = 0b10;
    prescaler_info->prescaler = 8;
  }
  else if (freq > 489){
    //set prescaler to 64
    prescaler_info->prescaler_bin = 0b11;
    prescaler_info->prescaler = 64;
  }
  else if (freq > 123){
    //set prescaler to 256
    prescaler_info->prescaler_bin = 0b100;
    prescaler_info->prescaler = 256;
  }
  else if (freq >= 31){
    //set prescaler to 1024
    prescaler_info->prescaler_bin = 0b101;
    prescaler_info->prescaler = 1024;
  }
  if(axis == 1){
    //TIMER2 (x axis) has special prescalers, so set the prescaler_bin value accordingly
    if(prescaler_info->prescaler_bin == 0b11){
      prescaler_info->prescaler_bin = 0b100;  
    }else if(prescaler_info->prescaler_bin == 0b100){
      prescaler_info->prescaler_bin = 0b110;
    }else if(prescaler_info->prescaler_bin == 0b101){
      prescaler_info->prescaler_bin = 0b111;  
    }
  }
}
//Functions that handle servo movements
void move_axis_pulses(uint8_t axis, int32_t toggles){
  //this function moves the selected axis according to the 
  //requested toggles
  //this function does not check movement boundaries
  uint8_t sreg_temp;
  float freq;
  Prescaler_info prescaler_info;
  switch (axis)
  {
    case 1:
      if(X_AXIS_MOVE_START_CHECK){
        //Serial.println("x axis is already moving");
        //Serial.flush();  
        return ;
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = servo_params.x_freq_const; //freq corresponding to 1% speed  
      get_prescaler_for_axis(freq,axis,&prescaler_info);
      
      //disable interrupts to update TCCR2B and timer_status variable
    
      sreg_temp = SREG;
      cli();
      TCCR2B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER2_PRESCALER_RESET; //update servo_board.timer_status 
      //Restore SREG 
      SREG = sreg_temp;
      TIFR2 |= 0b111;
      
      //update servo_board.servo_status
      X_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      X_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      //set DIR+ pin and update servo_status according to the selected axis
      if( toggles < 0 ){
        //set DIR+ pin HIGH
        X_AXIS_DIR_SET; 
        X_DIR_PIN_HIGH;                                                                                      
      }else{
        //set DIR+ pin LOW
        X_AXIS_DIR_RESET;
        X_DIR_PIN_LOW;
      }
      servo_position.toggles_end_x = servo_position.toggles_x + toggles;
      //start TIMER2
      
      if( X_NO_COMPL_FEED_CHECK ){
        //x axis has no move complete pin, pull the pin high to simulate it
        X_AXIS_MOVE_COMPL_PIN_HIGH;
      }
      TCNT2 = 0;  //reset the counter value
      TCCR2A |= (1<<6); //toggle OC2A on compare match
      TIMSK2 = 0b10;
      OCR2A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      //disable interrupts to update TCCR2B and timer_status variable
      
      sreg_temp = SREG;
      cli();
      TIMER2_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR2B |= prescaler_info.prescaler_bin;
      //Restore SREG
      SREG = sreg_temp;
      break;
    case 2:
      if(Y_AXIS_MOVE_START_CHECK){
        //Serial.println("y axis is already moving");
        //Serial.flush();  
        return ;
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = servo_params.y_freq_const; 
      get_prescaler_for_axis(freq,axis,&prescaler_info);
      //disable interrupts
    
      sreg_temp = SREG;
      cli();
      TCCR1B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER1_PRESCALER_RESET;
      //Restore SREG
      SREG = sreg_temp;
      TIFR1 |= 0b111;
      //update servo_board.servo_status
      Y_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      Y_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      //set DIR+ pin and update servo_status according to the selected axis
      if( toggles < 0 ){
        //set DIR+ pin HIGH
        Y_AXIS_DIR_SET; 
        Y_DIR_PIN_HIGH;                                                                                      
      }else{
        //set DIR+ pin LOW
        Y_AXIS_DIR_RESET;
        Y_DIR_PIN_LOW;
      }
      servo_position.toggles_end_y = servo_position.toggles_y + toggles;
      //start TIMER1
      
      if( Y_NO_COMPL_FEED_CHECK ){
        //y axis has no move complete pin, pull the pin high to simulate it
        Y_AXIS_MOVE_COMPL_PIN_HIGH;
      }
      TCNT1 = 0;  //reset the counter value
      TCCR1A |= (1<<6); //toggle OC1A on compare match
      TIMSK1 = 0b10;
      OCR1A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      sreg_temp = SREG;
      cli();
      TIMER1_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR1B |= prescaler_info.prescaler_bin;
      //Restore SREG 
      SREG = sreg_temp;
      break;
    case 3:
      if(Z_AXIS_MOVE_START_CHECK){
        //Serial.println("z axis is already moving");
        //Serial.flush();  
        return ;
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = servo_params.z_freq_const;  
      get_prescaler_for_axis(freq,axis,&prescaler_info);
      sreg_temp = SREG;
      cli();
      TCCR0B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER0_PRESCALER_RESET;
      //Restore SREG 
      SREG = sreg_temp;
      TIFR0 |= 0b111;
      //update servo_board.servo_status
      Z_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      Z_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      //set DIR+ pin and update servo_status according to the selected axis
      if( toggles < 0 ){
        //set DIR+ pin HIGH
        Z_AXIS_DIR_SET; 
        Z_DIR_PIN_HIGH;                                                                                      
      }else{
        //set DIR+ pin LOW
        Z_AXIS_DIR_RESET;
        Z_DIR_PIN_LOW;
      }
      servo_position.toggles_end_z = servo_position.toggles_z + toggles;
      //start TIMER0
      
      if( Z_NO_COMPL_FEED_CHECK ) {
        //z axis has no move complete pin, pull the pin high to simulate it
        Z_AXIS_MOVE_COMPL_PIN_HIGH;
       
      }
      TCNT0 = 0;  //reset the counter value
      TCCR0A |= (1<<6); //toggle OC1A on compare match
      TIMSK0 = 0b10;
      OCR0A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      sreg_temp = SREG;
      cli();
      TIMER0_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR0B |= prescaler_info.prescaler_bin;
      //Restore SREG 
      SREG = sreg_temp;
      break;
  }
  return 0;  
}

int8_t move_abs_pos(Abs_move * req_move){
  if(ALARM_CHECK){
    //there is an active alarm that has not been canceled , abort move and inform master  
    DEBUG_SERIAL_LN("active alarm error");
    DEBUG_SERIAL_FLUSH;
    add_com_response(REPORT_STATUS);
    return -1;
  }
  if(AXIS_MOVE_START_CHECK){
    //the requested axis is already moving , abort move and inform the master
    DEBUG_SERIAL_LN("axis in move error");
    DEBUG_SERIAL_FLUSH;
    AXIS_ALREADY_MOVING_SET;
    add_com_response(REPORT_STATUS);
    return -1;
  }
  float freq;
  Prescaler_info prescaler_info;
  int32_t required_toggles;
  uint8_t sreg_temp;
  switch (req_move->axis)
  {
    case 1:
      //check if the end position is out of axis bounds
      if( ( (req_move->end_mm < 0) | (req_move->end_mm > servo_params.x_mm_len) ) 
      && (!SERVICE_MODE_CHECK) && (!ZEROING_X_CHECK) ){
        //requested move is out of bounds while servo is not in service mode or zeroing, abort move and inform the master
        MOVE_OUT_OF_BOUNDS_SET;
        add_com_response(REPORT_STATUS);
        return -1;      
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = req_move->servo_speed * servo_params.x_freq_const;  
      get_prescaler_for_axis(freq,req_move->axis,&prescaler_info);
      if( prescaler_info.prescaler_bin == 0){
        //requested speed is out of bounds , abort move
        DEBUG_SERIAL_LN("rpm out of bounds error");
        DEBUG_SERIAL_FLUSH;
        //Serial.println("X rpm out of bounds error");
        //Serial.flush();
        return -1;  
      }
      
      
      //calculate toggles_end_@ based on axis
      required_toggles = ((int32_t)req_move->end_mm*servo_params.x_toggles_mm_mult - servo_position.toggles_x);
      if( required_toggles == 0){
        //servo is already at the selected position, abort move
        return -1;  
      }

      //disable interrupts to update TCCR2B and timer_status variable
      sreg_temp = SREG;
      cli();
      TCCR2B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER2_PRESCALER_RESET; //update servo_board.timer_status 
      //Restore SREG 
      SREG = sreg_temp;
      TIFR2 |= 0b111;
      
      //update servo_board.servo_status
      X_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      X_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      
      //set DIR+ pin and update servo_status according to the selected axis
      if( required_toggles < 0 ){
        //set DIR+ pin HIGH
        X_AXIS_DIR_SET; 
        X_DIR_PIN_HIGH;
      }else{
        //set DIR+ pin LOW
        X_AXIS_DIR_RESET;
        X_DIR_PIN_LOW;
      }
      servo_position.toggles_end_x = servo_position.toggles_x + required_toggles;
      /*
      Serial.print("current x toggles:");
      Serial.print(servo_position.toggles_x);
      Serial.print(",end toggles:");
      Serial.print(servo_position.toggles_end_x);
      Serial.print(",req toggles:");
      Serial.println(required_toggles);
      Serial.flush();
      */
      //start TIMER2
      
      if( X_NO_COMPL_FEED_CHECK ){
        //x axis has no move complete pin, pull the pin high to simulate it
        X_AXIS_MOVE_COMPL_PIN_HIGH;
      }
      TCNT2 = 0;  //reset the counter value
      TCCR2A |= (1<<6); //toggle OC2A on compare match
      TIMSK2 = 0b10;
      OCR2A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      sreg_temp = SREG;
      cli();
      TIMER2_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR2B |= prescaler_info.prescaler_bin;
      //Restore SREG 
      SREG = sreg_temp;
      
      break;
    case 2:
      //check if the end position is out of axis bounds
      if( ( (req_move->end_mm < 0) | (req_move->end_mm > servo_params.y_mm_len) ) 
      && (!SERVICE_MODE_CHECK) && (!ZEROING_Y_CHECK) ){
        //requested move is out of bounds while servo is not in service mode or zeroing, abort move and inform the master
        MOVE_OUT_OF_BOUNDS_SET;
        add_com_response(REPORT_STATUS);
        return -1;      
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = req_move->servo_speed * servo_params.y_freq_const;  
      get_prescaler_for_axis(freq,req_move->axis,&prescaler_info);
      if( prescaler_info.prescaler_bin == 0){
        //requested speed is out of bounds , abort move
        DEBUG_SERIAL_LN("rpm out of bounds error");
        DEBUG_SERIAL_FLUSH;
        //Serial.println("Y rpm out of bounds error");
        //Serial.flush();
        return -1;  
      }
      
      
      //calculate toggles_end_@ based on axis
      
      required_toggles = ((int32_t)req_move->end_mm*servo_params.y_toggles_mm_mult - servo_position.toggles_y);
      if( required_toggles == 0){
        //servo is already at the selected position, abort move
        //Serial.println("Servo already at position");
        //Serial.flush();
        return -1;  
      }

      //disable interrupts to update TCCR1B and timer_status variable
      sreg_temp = SREG;
      cli();
      TCCR1B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER1_PRESCALER_RESET; //update servo_board.timer_status 
      //Restore SREG 
      SREG = sreg_temp; 
      TIFR1 |= 0b111;
      
      //update servo_board.servo_status
      Y_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      Y_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      
      //set DIR+ pin and update servo_status according to the selected axis
      if( required_toggles < 0 ){
        //set DIR+ pin HIGH
        Y_AXIS_DIR_SET; 
        Y_DIR_PIN_HIGH;
      }else{
        //set DIR+ pin LOW
        Y_AXIS_DIR_RESET;
        Y_DIR_PIN_LOW;
      }
      servo_position.toggles_end_y = servo_position.toggles_y + required_toggles;
      /*
      Serial.print("current y toggles:");
      Serial.print(servo_position.toggles_y);
      Serial.print(",end toggles:");
      Serial.print(servo_position.toggles_end_y);
      Serial.print(",req toggles:");
      Serial.println(required_toggles);
      Serial.flush();
      */
      //start TIMER1
      
      if( Y_NO_COMPL_FEED_CHECK ){
        //y axis has no move complete pin, pull the pin high to simulate it
        Y_AXIS_MOVE_COMPL_PIN_HIGH;
      }
      TCNT1 = 0;  //reset the counter value
      TCCR1A |= (1<<6); //toggle OC2A on compare match
      TIMSK1 = 0b10;
      OCR1A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      sreg_temp = SREG;
      cli();
      TIMER1_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR1B |= prescaler_info.prescaler_bin;
      //Restore SREG 
      SREG = sreg_temp;
      
      break;
    case 3:
      //check if the end position is out of axis bounds
      if( ( (req_move->end_mm < 0) | (req_move->end_mm > servo_params.z_mm_len) ) 
      && (!SERVICE_MODE_CHECK) && (!ZEROING_Z_CHECK) ){
        //requested move is out of bounds while servo is not in service mode or zeroing, abort move and inform the master
        MOVE_OUT_OF_BOUNDS_SET;
        add_com_response(REPORT_STATUS);
        return -1;      
      }
      //calculate required frequency and get the corresponding prescaler depending on the axis
      freq = req_move->servo_speed * servo_params.z_freq_const;  
      get_prescaler_for_axis(freq,req_move->axis,&prescaler_info);
      if( prescaler_info.prescaler_bin == 0){
        //requested speed is out of bounds , abort move
        DEBUG_SERIAL_LN("rpm out of bounds error");
        DEBUG_SERIAL_FLUSH;
        //Serial.println("Z rpm out of bounds error");
        //Serial.flush();
        return -1;  
      }
      
      //calculate toggles_end_@ based on axis
      required_toggles = ((int32_t)req_move->end_mm*servo_params.z_toggles_mm_mult - servo_position.toggles_z);
      if( required_toggles == 0){
        //servo is already at the selected position, abort move
        return -1;  
      }
      //disable interrupts to update TCCR0B and timer_status variable
      sreg_temp = SREG;
      cli();
      TCCR0B &= ~0b111; //reset prescaler bits (toggles_end_@ might change before the timer is stopped otherwise)
      TIMER0_PRESCALER_RESET; //update servo_board.timer_status 
      //Restore SREG 
      SREG = sreg_temp;
      TIFR0 |= 0b111;
      
      //update servo_board.servo_status
      Z_AXIS_MOVE_START_SET; //set to prevent more move commands while the pulses are ongoing
      Z_AXIS_MOVE_END_SET;   //set to ingore noise on PED+ pin during the start of the pulses
      
      //set DIR+ pin and update servo_status according to the selected axis
      if( required_toggles < 0 ){
        //set DIR+ pin HIGH
        Z_AXIS_DIR_SET; 
        Z_DIR_PIN_HIGH;
      }else{
        //set DIR+ pin LOW
        Z_AXIS_DIR_RESET;
        Z_DIR_PIN_LOW;
      }
      servo_position.toggles_end_z = servo_position.toggles_z + required_toggles;
      /*
      Serial.print("current z toggles:");
      Serial.print(servo_position.toggles_z);
      Serial.print(",end toggles:");
      Serial.print(servo_position.toggles_end_z);
      Serial.print(",req toggles:");
      Serial.println(required_toggles);
      Serial.flush();
      */
      //start TIMER0
      
      if( Z_NO_COMPL_FEED_CHECK ){
        //z axis has no move complete pin, pull the pin high to simulate it
        Z_AXIS_MOVE_COMPL_PIN_HIGH;
      }
      TCNT0 = 0;  //reset the counter value
      TCCR0A |= (1<<6); //toggle OC2A on compare match
      TIMSK0 = 0b10;
      OCR0A = (ARDUINO_CLOCK_IN_HZ/(2*prescaler_info.prescaler*freq))-1;  //ATmega328P datasheet page 121
      sreg_temp = SREG;
      cli();
      TIMER0_PRESCALER_SAVE(prescaler_info.prescaler_bin);
      TCCR0B |= prescaler_info.prescaler_bin;
      //Restore SREG 
      SREG = sreg_temp;
      
      break;
  }
  return 0;  
}



//Alarm pin monitoring function
void check_alarm(){
  if( (!ALARM_PIN_CHECK) && (!ALARM_CHECK)){
    //alarm triggered at some servo, stop all movement and inform the master
    stop_motor(1);
    stop_motor(2);
    stop_motor(3);
    ALARM_SET;
    DEBUG_SERIAL_LN("alarm triggered");
    DEBUG_SERIAL_FLUSH;
    add_com_response(REPORT_STATUS);
  }  
}
//Movement complete pin monitoring function
void check_movement_end(){
  //x_axis check
  if( 
  ( X_AXIS_MOVE_START_CHECK==0 ) 
  && ( X_AXIS_MOVE_END_CHECK==0 ) 
  && (!X_AXIS_MOVE_COMPL_PIN_CHECK) 
  )
  {
    //x axis movement completed
    X_AXIS_MOVE_END_SET;
    DEBUG_SERIAL_LN("x complete");
    DEBUG_SERIAL_FLUSH;
    if( (!ZEROING_X_CHECK) && (!AUTO_MODE_CHECK) ){
      add_com_response(REPORT_X);
    }
  }
  //y_axis check
  if( 
  ( Y_AXIS_MOVE_START_CHECK==0 ) 
  && ( Y_AXIS_MOVE_END_CHECK==0 ) 
  && (!Y_AXIS_MOVE_COMPL_PIN_CHECK) 
  )
  {
    //y axis movement completed
    Y_AXIS_MOVE_END_SET;
    DEBUG_SERIAL_LN("y complete");
    DEBUG_SERIAL_FLUSH;
    if( (!ZEROING_Y_CHECK) && (!AUTO_MODE_CHECK) ){
      add_com_response(REPORT_Y);
    }
  }
  //z_axis check
  if( 
  ( Z_AXIS_MOVE_START_CHECK==0 ) 
  && ( Z_AXIS_MOVE_END_CHECK==0 ) 
  && (!Z_AXIS_MOVE_COMPL_PIN_CHECK) 
  )
  {
    //z axis movement completed

    //digitalWrite(Z_AXIS_BRAKE_PIN,LOW);  //enable z axis brake
    Z_AXIS_MOVE_END_SET;
    DEBUG_SERIAL_LN("z complete");
    DEBUG_SERIAL_FLUSH;
    if( (!ZEROING_Z_CHECK) && (!AUTO_MODE_CHECK) ){
      add_com_response(REPORT_Z);
    }
  }
}
//Function for stopping motors
void stop_motor(uint8_t axis){
  uint8_t sreg_temp;
  //stop motor resets both MOVE_START and MOVE_END bits, so check_movement_end() will 
  //trigger afterwards , sending a report to the master
  switch (axis)
  {
    case 1:
      //Stopping X axis
      sreg_temp = SREG;
      cli();
      TCCR2B &= ~(0b111); //disable timer2
      TIMER2_PRESCALER_RESET;
      //Restore SREG 
      SREG = sreg_temp;
      if(X_PULSE_PIN_CHECK){ //timer might stop on a pulse high, sort it out
        TCCR2B |= 1<<7; //force an output compare match on channel A to set the output LOW again
        //this will not toggle the ISR, so toggles_x has to change accordingly
        if(!X_AXIS_DIR_CHECK){
          servo_position.toggles_x++;
        }else{
          servo_position.toggles_x--;  
        }
      }
      X_AXIS_MOVE_START_RESET;
      X_AXIS_MOVE_END_RESET;
      if( X_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR2A &= ~(0b11<<6);  //disconnect OC0A
        TIMSK2 = 0b100; //enable output compare match B interrupt,disable interrupts for match A and overflow
        OCR2A = 255;  //OCR0A defines the TOP of CTC mode,has to be higher than OCR0B
        OCR2B = 249;  //64 prescaler -> ticks every 0.006ms ->250 ticks for 1ms ISR
        sreg_temp = SREG;
        cli();
        TIMER2_PRESCALER_SAVE(0b100);
        TCCR2B |= 0b100; //enable timer with 64 prescaler
        //Restore SREG 
        SREG = sreg_temp;
      }
      break;
    case 2:
      //Stopping Y axis
      sreg_temp = SREG;
      cli();
      TCCR1B &= ~(0b111); //disable timer1
      TIMER1_PRESCALER_RESET;
      //Restore SREG 
      SREG = sreg_temp;
      if(Y_PULSE_PIN_CHECK){ //timer might stop on a pulse high, sort it out
        TCCR1C |= 1<<7; //force an output compare match on channel A to set the output LOW again
        if(!Y_AXIS_DIR_CHECK){
          servo_position.toggles_y++;
        }else{
          servo_position.toggles_y--;  
        }
      }
      Y_AXIS_MOVE_START_RESET;
      Y_AXIS_MOVE_END_RESET;
      if( Y_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR1A &= ~(0b11<<6);  //disconnect OC0A
        TIMSK1 = 0b100; //enable output compare match B interrupt,disable interrupts for match A and overflow
        OCR1A = 255;  //OCR0A defines the TOP of CTC mode,has to be higher than OCR0B
        OCR1B = 249;  //64 prescaler -> ticks every 0.006ms ->250 ticks for 1ms ISR
        sreg_temp = SREG;
        cli();
        TIMER1_PRESCALER_SAVE(0b11);
        TCCR1B |= 0b11; //enable timer with 64 prescaler
        //Restore SREG 
        SREG = sreg_temp;
      }
      break;
    case 3:
      //Stopping Z axis
      sreg_temp = SREG;
      cli();
      TCCR0B &= ~(0b111); //disable timer0
      TIMER0_PRESCALER_RESET;
      //Restore SREG 
      SREG = sreg_temp;
      if(Z_PULSE_PIN_CHECK){ //timer might stop on a pulse high, sort it out
        TCCR0B |= 1<<7; //force an output compare match on channel A to set the output LOW again
        if(!Z_AXIS_DIR_CHECK){
          servo_position.toggles_z++;
        }else{
          servo_position.toggles_z--;  
        }
      }
      Z_AXIS_MOVE_START_RESET;
      Z_AXIS_MOVE_END_RESET;
      if( Z_NO_COMPL_FEED_CHECK ) {  
        //set up a timer on compare match B to simulate a movement complete pin going low after some time
        TCCR0A &= ~(0b11<<6);  //disconnect OC0A
        TIMSK0 = 0b100; //enable output compare match B interrupt,disable interrupts for match A and overflow
        OCR0A = 255;  //OCR0A defines the TOP of CTC mode,has to be higher than OCR0B
        OCR0B = 249;  //64 prescaler -> ticks every 0.006ms ->250 ticks for 1ms ISR
        sreg_temp = SREG;
        cli();
        TIMER0_PRESCALER_SAVE(0b11);
        TCCR0B |= 0b11; //enable timer with 64 prescaler
        //Restore SREG 
        SREG = sreg_temp;
      }
      break;
  }
}
//Inductive sensors monitoring function
void check_inductive_sensors(){
  if( AXES_NOT_ZEROED_CHECK ) {
    static uint8_t zeroed_axes; //have to reset it to 0 after zeroing all axes

    //x axis
    if( (!X_AXIS_INDUCTIVE_PIN_CHECK) && (!X_AXIS_INDUCTIVE_CHECK) && (ZEROING_X_CHECK) ){
      //inductive triggered, stop motor
      stop_motor(1);
      X_AXIS_INDUCTIVE_SET;
    }
    if( (ZEROING_X_CHECK) &&
    (!X_AXIS_MOVE_START_CHECK) && (X_AXIS_MOVE_END_CHECK) 
    ){
      //x axis is idling after triggering the inductive sensor
      if(!X_AXIS_INDUCTIVE_PIN_CHECK){
        //x inductive is still triggered, move 1 step away from the axis origin
        //Serial.println("1step->");
        //Serial.flush();
        move_axis_pulses(1,2);
      }else{
        //x inductive is no longer triggered, move 1 mm to the axis origin
        //Serial.println("<-1mm");
        //Serial.flush();
        move_axis_pulses(1,-((uint32_t)servo_params.x_toggles_mm_mult));
        ZEROING_X_RESET;
        X_RESET_POSITION_FLAG_SET;
      }
    }
    if( X_RESET_POSITION_FLAG_CHECK && (!X_AXIS_MOVE_START_CHECK) && (X_AXIS_MOVE_END_CHECK)){
      //x is idling after completing the last zeroing move, mark this position as the x origin
      X_ZEROED_SET;
      X_RESET_POSITION_FLAG_RESET;
      X_AXIS_DIR_RESET;
      X_DIR_PIN_LOW;
      servo_position.toggles_x = 0;
    }
    //y axis
    if( (!Y_AXIS_INDUCTIVE_PIN_CHECK) && (!Y_AXIS_INDUCTIVE_CHECK) && (ZEROING_Y_CHECK) ){
      // yinductive triggered, stop motor
      stop_motor(2);
      Y_AXIS_INDUCTIVE_SET;
    }
    if( (ZEROING_Y_CHECK) &&
    (!Y_AXIS_MOVE_START_CHECK) && (Y_AXIS_MOVE_END_CHECK) 
    ){
      //y axis is idling after triggering the inductive sensor
      if(!Y_AXIS_INDUCTIVE_PIN_CHECK){
        //y inductive is still triggered, move 1mm away from the axis origin
        move_axis_pulses(2,2);
      }else{
        //y inductive is no longer triggered, move 1mm to the axis origin
        move_axis_pulses(2,-((uint32_t)servo_params.y_toggles_mm_mult));
        ZEROING_Y_RESET;
        Y_RESET_POSITION_FLAG_SET;
      }
    }
    if( Y_RESET_POSITION_FLAG_CHECK && (!Y_AXIS_MOVE_START_CHECK) && (Y_AXIS_MOVE_END_CHECK)){
      //y is idling after completing the last zeroing move, mark this position as the z origin
      Y_ZEROED_SET;
      Y_RESET_POSITION_FLAG_RESET;
      Y_AXIS_DIR_RESET;
      Y_DIR_PIN_LOW;
      servo_position.toggles_y = 0;
    }

  //z axis
    if( (!Z_AXIS_INDUCTIVE_PIN_CHECK) && (!Z_AXIS_INDUCTIVE_CHECK) && (ZEROING_Z_CHECK) ){
      //inductive triggered, stop motor
      stop_motor(3);
      Z_AXIS_INDUCTIVE_SET;
    }
    if( (ZEROING_Z_CHECK) &&
    (!Z_AXIS_MOVE_START_CHECK) && (Z_AXIS_MOVE_END_CHECK) 
    ){
      //z axis is idling after triggering the inductive sensor
      if(!Z_AXIS_INDUCTIVE_PIN_CHECK){
        //z inductive is still triggered, move 1mm away from the axis origin
        move_axis_pulses(3,2);
      }else{
        //z inductive is no longer triggered, move 1mm to the axis origin
        move_axis_pulses(3,-((uint32_t)servo_params.z_toggles_mm_mult));
        ZEROING_Z_RESET;
        Z_RESET_POSITION_FLAG_SET;
      }
    }
    if( Z_RESET_POSITION_FLAG_CHECK && (!Z_AXIS_MOVE_START_CHECK) && (Z_AXIS_MOVE_END_CHECK)){
      //z is idling after completing the last zeroing move, mark this position as the z origin
      Z_ZEROED_SET;
      Z_RESET_POSITION_FLAG_RESET;
      Z_AXIS_DIR_RESET;
      Z_DIR_PIN_LOW;
      servo_position.toggles_z = 0;
    }
    if( (X_ZEROED_CHECK) && (Y_ZEROED_CHECK) && (Z_ZEROED_CHECK) ){
      AXES_NOT_ZEROED_RESET;
      add_com_response(REPORT_STATUS);
      zeroed_axes = 0 ; //reset to enable zeroing again if needed
    }
  }else{
    //x axis inductive check
    if( (!X_AXIS_INDUCTIVE_PIN_CHECK) && (!X_AXIS_INDUCTIVE_CHECK) ){
      X_AXIS_INDUCTIVE_SET;
    }
    if( (X_AXIS_INDUCTIVE_PIN_CHECK) && (X_AXIS_INDUCTIVE_CHECK) ){
      X_AXIS_INDUCTIVE_RESET;
    }
    //y axis inductive check
    if( (!Y_AXIS_INDUCTIVE_PIN_CHECK) && (!Y_AXIS_INDUCTIVE_CHECK) ){
      Y_AXIS_INDUCTIVE_SET;
    }
    if( (Y_AXIS_INDUCTIVE_PIN_CHECK) && (Y_AXIS_INDUCTIVE_CHECK) ){
      Y_AXIS_INDUCTIVE_RESET;
    }
    //z axis inductive check
    if( (!Z_AXIS_INDUCTIVE_PIN_CHECK) && (!Z_AXIS_INDUCTIVE_CHECK) ){
      Z_AXIS_INDUCTIVE_SET;
    }
    if( (Z_AXIS_INDUCTIVE_PIN_CHECK) && (Z_AXIS_INDUCTIVE_CHECK) ){
      Z_AXIS_INDUCTIVE_RESET;
    }
  }
}
//Function for zeroing selected axes
void zero_axes(uint8_t selected_axes){
  
  //set the AXES_NOT_ZEROED flag
  AXES_NOT_ZEROED_SET;
  //reset saved_commands.index so that commands can start from the beginning after zeroing
  saved_commands.index = 0;
  Abs_move zero_move;
  zero_move.servo_speed = servo_params.zeroing_speed;
  if(selected_axes & 1){
    stop_motor(1);
    ZEROING_X_SET;
    zero_move.end_mm = -servo_params.x_mm_len;
    zero_move.axis = 1;
    //inductive sensors are active low
    if(X_AXIS_INDUCTIVE_PIN_CHECK){
      X_AXIS_INDUCTIVE_RESET;
      DEBUG_SERIAL_LN("Moving x to the left");
      DEBUG_SERIAL_FLUSH;
      move_abs_pos(&zero_move);
    }else{
      //x axis is on top of the inductive sensor, set the corresponding bit
      X_AXIS_INDUCTIVE_SET;
    } 
  }
  
  if((selected_axes>>1) & 1){
    stop_motor(2);
    ZEROING_Y_SET;
    zero_move.end_mm = -servo_params.y_mm_len;
    zero_move.axis = 2;
    //inductive sensors are active low
    if(Y_AXIS_INDUCTIVE_PIN_CHECK){
      Y_AXIS_INDUCTIVE_RESET;
      DEBUG_SERIAL_LN("Moving y to the left");
      DEBUG_SERIAL_FLUSH;
      move_abs_pos(&zero_move);
    }else{
      //y axis is on top of the inductive sensor, set the corresponding bit
      Y_AXIS_INDUCTIVE_SET;
    } 
  }
  if((selected_axes>>2) & 1){
    stop_motor(3);
    ZEROING_Z_SET;
    zero_move.end_mm = -servo_params.z_mm_len;
    zero_move.axis = 3;
    //inductive sensors are active low
    if(Z_AXIS_INDUCTIVE_PIN_CHECK){
      Z_AXIS_INDUCTIVE_RESET;
      DEBUG_SERIAL_LN("Moving z to the left");
      DEBUG_SERIAL_FLUSH;
      move_abs_pos(&zero_move);
    }else{
      //z axis is on top of the inductive sensor, set the corresponding bit
      Z_AXIS_INDUCTIVE_SET;
    } 
  }
}


//Automatic move handling function
#define X_AT_POS_PENDING_SET (axes_messages_flags|=1<<3)
#define Y_AT_POS_PENDING_SET (axes_messages_flags|=1<<4)
#define Z_AT_POS_PENDING_SET (axes_messages_flags|=1<<5)
#define X_AT_POS_PENDING_RESET (axes_messages_flags&=~(1<<3))
#define Y_AT_POS_PENDING_RESET (axes_messages_flags&=~(1<<4))
#define Z_AT_POS_PENDING_RESET (axes_messages_flags&=~(1<<5))
#define X_AT_POS_PENDING_CHECK ((axes_messages_flags>>3)&1)
#define Y_AT_POS_PENDING_CHECK ((axes_messages_flags>>4)&1)
#define Z_AT_POS_PENDING_CHECK ((axes_messages_flags>>5)&1)


#define X_DIR_CHECK (axes_dir_flags&1)
#define Y_DIR_CHECK ((axes_dir_flags>>1)&1)
#define Z_DIR_CHECK ((axes_dir_flags>>2)&1)


void execute_auto_move(uint8_t evaluate_positions_flag){

  static Abs_move x_move;
  static Abs_move y_move;
  static Abs_move z_move;

  static uint8_t axes_messages_flags= 0b111;  //set so that the master wont be informed about
                                              //axes being in position before any axis moves
  static uint8_t axes_dir_flags = 0;
  
  if(evaluate_positions_flag==1){
    //evaluate where each axis should be for the current index and return
    //Serial.println("Evaluating positions");
    //Serial.flush();
    Auto_mode_positions Auto_mode_positions;
    get_auto_mode_positions( &Auto_mode_positions);
    x_move.end_mm = Auto_mode_positions.x_position;
    y_move.end_mm = Auto_mode_positions.y_position;
    z_move.end_mm = Auto_mode_positions.z_position;
    axes_dir_flags = 0;
    axes_messages_flags= 0b111;
    return;
  }
  
  if(LOOP_ERROR_CHECK || (!AUTO_MODE_CHECK) || (!AUTO_TRIGGER_CHECK) ){
    //loop is not verified or servo not in automatic operation mode
    //or auto triggering is currently disabled ,  abort
    return ;  
  }

  //update Abs_move structs according to the current index
  switch (AXIS_SAVED_COM)
  {
    case 1:
      x_move.end_mm = END_MM_SAVED_COM*SIGN_SAVED_COM;
      x_move.servo_speed = SERVO_SPEED_SAVED_COM;
      x_move.axis =AXIS_SAVED_COM;
      x_move.next_trigger =DELAY_SAVED_COM;
      if(x_move.end_mm >= (servo_position.toggles_x/servo_params.x_toggles_mm_mult)){
        axes_dir_flags&=~1;
      }else{
        axes_dir_flags|=1;    
      }
      break;
    case 2:
      y_move.end_mm = END_MM_SAVED_COM*SIGN_SAVED_COM;
      y_move.servo_speed = SERVO_SPEED_SAVED_COM;
      y_move.axis =AXIS_SAVED_COM;
      y_move.next_trigger =DELAY_SAVED_COM;
      if(y_move.end_mm >= (servo_position.toggles_y/servo_params.y_toggles_mm_mult)){
        axes_dir_flags&=~(1<<1);
      }else{
        axes_dir_flags|=(1<<1);    
      }
      break;
    case 3:
      z_move.end_mm = END_MM_SAVED_COM*SIGN_SAVED_COM;
      z_move.servo_speed = SERVO_SPEED_SAVED_COM;
      z_move.axis =AXIS_SAVED_COM;
      z_move.next_trigger =DELAY_SAVED_COM;
      if(z_move.end_mm >= (servo_position.toggles_z/servo_params.z_toggles_mm_mult)){
        axes_dir_flags&=~(1<<2);
      }else{
        axes_dir_flags|=(1<<2);    
      }
      break;
  }  
  
  //if an axis is not where it should be and it is not getting pulses, start a move towards that position
  if( ( (x_move.end_mm*servo_params.x_toggles_mm_mult) != servo_position.toggles_x ) && ( !X_AXIS_MOVE_START_CHECK ) ){
    //check if axis previously completed a move and it now has to start a new one
    //but it has not reported it to the master yet
    if(X_AT_POS_PENDING_CHECK){
        add_com_response(REPORT_X_END_AUTO);
        X_AT_POS_PENDING_RESET;
    }
    move_abs_pos(&x_move);
    saved_commands.x_auto_start_index = saved_commands.index;
    add_com_response(REPORT_X_START_AUTO);
    X_AT_POS_SENT_RESET;
  }
  if( ((y_move.end_mm*servo_params.y_toggles_mm_mult) != servo_position.toggles_y ) && ( !Y_AXIS_MOVE_START_CHECK ) ){
    //check if axis previously completed a move and it now has to start a new one
    //but it has not reported it to the master yet
    if(Y_AT_POS_PENDING_CHECK){
        add_com_response(REPORT_Y_END_AUTO);
        Y_AT_POS_PENDING_RESET;
    }
    move_abs_pos(&y_move);
    saved_commands.y_auto_start_index = saved_commands.index;
    add_com_response(REPORT_Y_START_AUTO);
    Y_AT_POS_SENT_RESET;
  }
  if( ((z_move.end_mm*servo_params.z_toggles_mm_mult) != servo_position.toggles_z ) && ( !Z_AXIS_MOVE_START_CHECK ) ){
    //check if axis previously completed a move and it now has to start a new one
    //but it has not reported it to the master yet
    if(Z_AT_POS_PENDING_CHECK){
        add_com_response(REPORT_Z_END_AUTO);
        Z_AT_POS_PENDING_RESET;
    }
    move_abs_pos(&z_move);
    saved_commands.z_auto_start_index = saved_commands.index;
    add_com_response(REPORT_Z_START_AUTO);
    Z_AT_POS_SENT_RESET;
    
  }

  //if an axis is at the correct position , idling and the
  //master has not been informed, send him a message
  if( (servo_position.toggles_end_x == servo_position.toggles_x) && (!X_AXIS_MOVE_START_CHECK) 
  && (X_AXIS_MOVE_END_CHECK) && (!X_AT_POS_SENT_CHECK) ){
    add_com_response(REPORT_X_END_AUTO);
    X_AT_POS_SENT_SET;
  }

  if( (servo_position.toggles_end_y == servo_position.toggles_y) && (!Y_AXIS_MOVE_START_CHECK) 
  && (Y_AXIS_MOVE_END_CHECK) && (!Y_AT_POS_SENT_CHECK) ){
    add_com_response(REPORT_Y_END_AUTO);
    Y_AT_POS_SENT_SET;
  }

  if( (servo_position.toggles_end_z == servo_position.toggles_z) && (!Z_AXIS_MOVE_START_CHECK) 
  && (Z_AXIS_MOVE_END_CHECK) && (!Z_AT_POS_SENT_CHECK) ){
    add_com_response(REPORT_Z_END_AUTO);
    Z_AT_POS_SENT_SET;
  }

  if( AUTO_MOVE_CHECK ){
    //check what the index should be according to the axes position
    uint8_t index_incremented_flag = 0;
    switch (AXIS_SAVED_COM)
    {
      case 1:
        //if(X_AXIS_DIR_CHECK == 0){
        if(X_DIR_CHECK==0){
          if( (servo_position.toggles_x/servo_params.x_toggles_mm_mult) >= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            X_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
            
          }
        }else{
          if( (servo_position.toggles_x/servo_params.x_toggles_mm_mult) <= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            X_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
            
          }
        }
        break;
      case 2:
        //if(Y_AXIS_DIR_CHECK == 0){
        if(Y_DIR_CHECK==0){
          if( (servo_position.toggles_y/servo_params.y_toggles_mm_mult) >= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            Y_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
            
          }
        }else{
          if( (servo_position.toggles_y/servo_params.y_toggles_mm_mult) <= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            Y_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
            
          }
        }
        break;
      case 3:
        //if(Z_AXIS_DIR_CHECK == 0){
        if(Z_DIR_CHECK==0){
          if( (servo_position.toggles_z/servo_params.z_toggles_mm_mult) >= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            Z_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
                        
          }
        }else{
          if( (servo_position.toggles_z/servo_params.z_toggles_mm_mult) <= DELAY_SAVED_COM){
            //set flag so that if axis has to move again before move complete is set
            //it can inform the master of completing the previous move
            Z_AT_POS_PENDING_SET;
            saved_commands.index++;
            index_incremented_flag = 1;
            
          }
        }
        break;
    }
    if(saved_commands.index >= saved_commands.num){
      //set index to 0
      saved_commands.index = 0;  
    }
    if(index_incremented_flag == 1){
      //report the saved_commands.index so that the master know what move 
      //will be executed
      add_com_response(REPORT_INDEX); 
    }
  }
  
}


#define X_POSITION_FOUND_SET (axes_position_found|=1)
#define Y_POSITION_FOUND_SET (axes_position_found|=(1<<1))
#define Z_POSITION_FOUND_SET (axes_position_found|=(1<<2))
#define X_POSITION_FOUND_CHECK (axes_position_found&1)
#define Y_POSITION_FOUND_CHECK ((axes_position_found>>1)&1)
#define Z_POSITION_FOUND_CHECK ((axes_position_found>>2)&1)
#define ALL_POSITIONS_FOUND_CHECK (axes_position_found==0b111)

void get_auto_mode_positions(Auto_mode_positions * Auto_mode_positions ){
  //find starting position for each axis
  uint8_t axes_position_found = 0;
  uint8_t temp_index = saved_commands.index;
  Auto_mode_positions->x_position = 0;
  Auto_mode_positions->y_position = 0;
  Auto_mode_positions->z_position = 0;
  for(saved_commands.index = saved_commands.num -1 ; saved_commands.index >= 0 ; saved_commands.index--){
    if(saved_commands.index == 255){
      //search completed , got to break out of the loop because saved_commands.index is unsigned
      break;  
    }
    switch(AXIS_SAVED_COM)
    {
      case 1:
        //
        //if(!(axes_position_found&1)){
        if( !X_POSITION_FOUND_CHECK ){
          //set flag to stop checking x axis
          //axes_position_found |= 1;
          X_POSITION_FOUND_SET;
          Auto_mode_positions->x_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        }
        break;
      case 2:
        //if(!((axes_position_found>>1)&1)){
        if( !Y_POSITION_FOUND_CHECK ){
          //set flag to stop checking y axis
          //axes_position_found |= (1<<1);
          Y_POSITION_FOUND_SET;
          Auto_mode_positions->y_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        }
        break;
      case 3:
        //if(!((axes_position_found>>2)&1)){
        if( !Z_POSITION_FOUND_CHECK ){
          //set flag to stop checking z axis
          //axes_position_found |= (1<<2);
          Z_POSITION_FOUND_SET;
          Auto_mode_positions->z_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        }
        break;  
    }
    if( ALL_POSITIONS_FOUND_CHECK ){
      //found the starting positions of all axes, break out of the loop
      break;  
    }  
  }
  //check where each axis should be according to the current index
  for( saved_commands.index = 0 ; saved_commands.index < temp_index ; saved_commands.index++){
    switch(AXIS_SAVED_COM)
    {
      case 1:
        Auto_mode_positions->x_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        break;
      case 2:
        Auto_mode_positions->y_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        break;
      case 3:
        Auto_mode_positions->z_position = END_MM_SAVED_COM*SIGN_SAVED_COM;
        break;  
    }
  }
  saved_commands.index = temp_index;
}





//Serial communication handling functions
void handle_program_operation(uint32_t serial_data,uint8_t message_length){
  LOOP_ERROR_SET;
  uint8_t prog_op_id = PROG_OP_ID;
  static uint8_t commands_to_receive;
  static uint8_t temp_index;
  switch (prog_op_id)
  {
    case 0b000:
      //incoming data declare the number of commands
      if(COMMANDS_NUM > 60){
    //Servo can only store up to 60 commands, return
        return;  
      }
      saved_commands.num = COMMANDS_NUM ; 
      commands_to_receive = saved_commands.num;
      break;
    case 0b001:
      //incoming data select the programming command index 
      if(COMMAND_INDEX >= saved_commands.num){
      //selected index is greater than the selected number of commands, return
        return;  
      }
      temp_index = COMMAND_INDEX;
      if(commands_to_receive == 0){
        //this is a command to update a single move, set commands_to_receive to 1
        commands_to_receive = 1;  
      }
      break;
    case 0b010:
      //save incoming move info to the move_info array
      if( commands_to_receive == 0 ){
        //either received move_info without setting a saved_commands.num or received
        //a single move_info update without selecting an index first , return
        return;  
      }
      saved_commands.move_info[temp_index] = MOVE_INFO;
      break;
    case 0b011:
      //save incoming delay info to the delay_info array
      if( saved_commands.num == 0 ){
        //either received delay_info without setting a saved_commands.num or received 
        //a single delay_info update without selecting an index first , return
        return;  
      }
      saved_commands.delay_info[temp_index] = DELAY_INFO;
      commands_to_receive--;
      if(commands_to_receive==0){
        LOOP_ERROR_RESET;
        add_com_response(REPORT_STATUS);
        /*
        temp_index = saved_commands.index;
        for(saved_commands.index = 0 ; saved_commands.index < saved_commands.num ; saved_commands.index++){
          Serial.print("Index ");
          Serial.print(saved_commands.index);
          Serial.print(" Move :");
          Serial.print(END_MM_SAVED_COM);
          Serial.print(" , speed :");
          Serial.print(SERVO_SPEED_SAVED_COM);
          Serial.print(" , axis :");
          Serial.print(AXIS_SAVED_COM);
          Serial.print(" , delay:");
          Serial.println(DELAY_SAVED_COM);
          Serial.flush();
        }
        saved_commands.index = temp_index;
        */
      }
      break;
    case 0b100:
      //incoming data set a servo parameter
      if(PARAMETER_INDEX < TWO_BYTE_PARAM_START){
        //parameter is a single byte long, store it in EEPROM
        eeprom_write( SINGLE_BYTE_PARAM_BASE+PARAMETER_INDEX , PARAMETER_VALUE_LOW);
      }else{
        //parameter is two bytes long, store in EEPROM accordingly
        eeprom_write(TWO_BYTE_PARAM_BASE + (PARAMETER_INDEX-TWO_BYTE_PARAM_START)*2,PARAMETER_VALUE_HIGH);
        eeprom_write(TWO_BYTE_PARAM_BASE + (PARAMETER_INDEX-TWO_BYTE_PARAM_START)*2+1,PARAMETER_VALUE_LOW);
      }
      calculate_servo_params();
      LOOP_ERROR_RESET;
      break;
    case 0b101:
      //incoming data select the current command index
      if(COMMAND_INDEX >= saved_commands.num){
      //selected index is greater than the selected number of commands, return
        return;  
      }
      LOOP_ERROR_RESET;
      saved_commands.index = COMMAND_INDEX;
      add_com_response(REPORT_INDEX); 
      break;
  }
}

void handle_move_operation(uint32_t serial_data){
  Abs_move req_move;
  req_move.end_mm = END_MM_SERIAL;
  req_move.servo_speed = SERVO_SPEED_SERIAL;
  req_move.axis = AXIS_SERIAL;
  req_move.end_mm = req_move.end_mm*SIGN_SERIAL;
  move_abs_pos(&req_move);
}


void handle_serial(){
  static Serial_info serial_info; //no need to initialise since its declared static
  static uint8_t response_delay ;
  static uint8_t response_cycles = 75;
  static uint8_t index_no_incr;
  static uint8_t repeat_response_flag;

  if(Serial.available() > 0 ){
    //Serial.println("got message");
    //Serial.flush();
    if(serial_info.ignore_bytes > 0){
      //read the byte and ignore it , decrement the ignore_bytes counter
      uint8_t ignore_data = Serial.read();
      serial_info.ignore_bytes--;
    }else{
      //check incoming message
      uint8_t inc_data = Serial.read();
      if(serial_info.index == 0){
        //this is the first byte of a message, check if it corresponds to this slave
        if( SERIAL_ID == ARDUINO_ID ){
          //message is targeting this slave , get the length and start saving the data
          serial_info.message_length = SERIAL_MESSAGE_LENGHT;
          serial_info.index = serial_info.message_length;
          serial_info.operation = SERIAL_OPERATION;
          serial_info.inc_data = 0;
          if( serial_info.message_length == 0 ){
            //handle commands that have no extra arguments
            switch ( serial_info.operation ) 
            {
              case 0b10:
                //next move operation , trigger the next move if mode is automatic operation
                if( !AUTO_MODE_CHECK ){
                  //command not accepted when not in automatic operation mode
                  INVALID_MODE_SET;
                  add_com_response(REPORT_STATUS);
                  return ;
                }
                if( LOOP_ERROR_CHECK ){
                  //cannot accept a next move operation while the loop is not verified
                  add_com_response(REPORT_STATUS);  
                  return ; 
                }
                
                AUTO_TRIGGER_SET;
                
                if(NO_INCR_STOP_CHECK){
                  //if a stop command was issued while in auto mode , do not increment the command index
                  NO_INCR_STOP_RESET;
                  //report the saved_commands.index so that the master know what move 
                  //will be executed
                  //add_com_response(REPORT_INDEX);
                  return ;  
                }
                /*
                if( (!NO_INCR_ZERO_CHECK) && (saved_commands.index == 0) ){
                  NO_INCR_ZERO_SET;  
                }else{
                  NO_INCR_ZERO_RESET;
                }
                if( NO_INCR_ZERO_CHECK ){
                  //do not increment command index for index zero
                  return;
                }
                */
                if(saved_commands.index == saved_commands.num-1){
                  //reset index to 0
                  saved_commands.index = 0;
                }else{
                  saved_commands.index++;
                }
                //report the saved_commands.index so that the master know what move 
                //will be executed
                add_com_response(REPORT_INDEX);  
                break;
              case 0b111:
                //stop operation
                stop_motor(1);
                stop_motor(2);
                stop_motor(3);
                if( AUTO_MODE_CHECK ){
                  AUTO_TRIGGER_RESET;  //prevent any further commands from running in auto mode
                  if( AUTO_MOVE_CHECK ){
                    //servo stopped during an automatic index increment move
                    //set a flag to prevent the following next operation from incrementing the index 
                    NO_INCR_STOP_SET;  
                  }else{
                    //servo stopped during a move that waits for a next command
                    //check if it has not completed it yet, and if so prevent the following
                    //next operation from incrementing the index
                    switch(AXIS_SAVED_COM)
                    {
                      case 1:
                        if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.x_toggles_mm_mult) != servo_position.toggles_x )){
                          NO_INCR_STOP_SET;  
                        }
                        break;
                      case 2:
                        if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.y_toggles_mm_mult) != servo_position.toggles_y )){
                          NO_INCR_STOP_SET;  
                        }
                        break;
                      case 3:
                        if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.z_toggles_mm_mult) != servo_position.toggles_z )){
                          NO_INCR_STOP_SET;  
                        }
                        break;
                    }   
                  }
                }
                break;
              case 0b101:
                //Repeat last response operation
                repeat_response_flag = 1;
                //raise the hand
                SLAVE_R_HIGH;
                break;    
            }  
          }
        }else if ( SERIAL_ID == ACK_OPERATION){
          //check if master acknowledged this slave
          if (ACK_ID == ARDUINO_ID){
            //if there are any responses available , set ack_recieved to respond
            if (servo_board.response_index > 0) {
              serial_info.ack_received = 1;
              SLAVE_R_LOW;  
            }
          }
        }else{
          //message is targeting another slave , get the length to ingore that amount of incoming bytes
          serial_info.ignore_bytes = SERIAL_MESSAGE_LENGHT;
        }
      }else{
        //more incoming bytes, save them according to the index
        serial_info.index--;
        serial_info.inc_data |= ((uint32_t)inc_data<<(8*serial_info.index));
        if(serial_info.index == 0){
          //full message was received , do stuff with it
          switch (serial_info.operation)
          {
            case 0b0:
              //servo status report operation
              add_com_response(RESPONSE_TYPE_SERIAL);
              break;
            case 0b01:
              //program operation
              if( AUTO_MODE_CHECK ){
                //command not accepted if in automatic mode
                INVALID_MODE_SET;
                add_com_response(REPORT_STATUS);
                return ;
              }
              handle_program_operation(serial_info.inc_data,serial_info.message_length);
              break;
            case 0b11:
              //move axis operation 
              if( AUTO_MODE_CHECK ){
                //command not accepted if in automatic mode
                INVALID_MODE_SET;
                add_com_response(REPORT_STATUS);
                return ;
              }
              if( AXES_NOT_ZEROED_CHECK && (!SERVICE_MODE_CHECK) ){
                //command not accepted if axes are not zeroed and the servo is not in service mode 
                add_com_response(REPORT_STATUS);
                return ;
              }
              handle_move_operation(serial_info.inc_data);
              break;
            case 0b100:
              //set servo mode operation
              static uint8_t previous_index = 255;  //init index to 255 to force a position check the first time the servo
                                                    //goes in automatic mode
              static Auto_mode_positions auto_mode_positions;
              if( (serial_info.inc_data==1) && (!AUTO_MODE_CHECK) ){
                //servo was instructed to set mode to automatic
                if(AXES_NOT_ZEROED_CHECK){
                  //servo cannot enter automatic mode without zeroing axes first
                  add_com_response(REPORT_STATUS);
                  return ; 
                }
                if( LOOP_ERROR_CHECK ){
                  //servo cannot enter automatic mode without setting up the loop first
                  add_com_response(REPORT_STATUS);
                  return;  
                }


                get_auto_mode_positions( &auto_mode_positions);
                //run execute_auto_move() in axis evaluation mode to update where each axis should be
                execute_auto_move(1);
                
                //check if axes are where they should be
                if( (!X_IN_CORRECT_POSITION) || (!Y_IN_CORRECT_POSITION) || (!Z_IN_CORRECT_POSITION) ){
                  //servo is not where is should be, cannot enter automatic mode
                  SERVO_NOT_AT_ORIGIN_SET;
                  add_com_response(REPORT_STATUS);
                  return; 
                }
                if( ( AUTO_MOVE_CHECK ) || (saved_commands.index != previous_index) ){
                  //if servo is setting mode to automatic during a move that automatically triggers
                  //the next , or after an index change , the following next operation should not
                  //increment the current indexs,z 
                  NO_INCR_STOP_SET;  
                }
                
                //set response_cycles to 20 to account for increased time per cycle in auto mode  
                response_cycles = 20;
              
              }
              if( (serial_info.inc_data != 1) && ( AUTO_MODE_CHECK ) ){
                //exiting automatic operation mode stops all axes and
                //resets the auto_trigger flag to prevent moving without
                //a next command when the mode changes back to automatic
                AUTO_TRIGGER_RESET;  
                //stop axes
                stop_motor(1);
                stop_motor(2);
                stop_motor(3);
                if( AUTO_MOVE_CHECK ){
                  //servo stopped during an automatic index increment move
                  //set a flag to prevent the following next operation from incrementing the index 
                  NO_INCR_STOP_SET;  
                }else{
                  //servo stopped during a move that waits for a next command
                  //check if it has not completed it yet, and if so prevent the following
                  //next operation from incrementing the index
                  switch(AXIS_SAVED_COM)
                  {
                    case 1:
                      if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.x_toggles_mm_mult) != servo_position.toggles_x )){
                        NO_INCR_STOP_SET;  
                      }
                      break;
                    case 2:
                      if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.y_toggles_mm_mult) != servo_position.toggles_y )){
                        NO_INCR_STOP_SET;  
                      }
                      break;
                    case 3:
                      if( ( (END_MM_SAVED_COM*SIGN_SAVED_COM*servo_params.z_toggles_mm_mult) != servo_position.toggles_z )){
                        NO_INCR_STOP_SET;  
                      }
                      break;
                  }
                }
                //store the servo position and index to enable re-entrace to automatic mode
                previous_index = saved_commands.index;
                auto_mode_positions.x_position = servo_position.toggles_x/servo_params.x_toggles_mm_mult;
                auto_mode_positions.y_position = servo_position.toggles_y/servo_params.y_toggles_mm_mult;
                auto_mode_positions.z_position = servo_position.toggles_z/servo_params.z_toggles_mm_mult; 
                
                //set response_cycles to 75 to account for reduced time per cycle in auto mode  
                response_cycles = 75;
                
              }
              servo_board.mode = serial_info.inc_data;
              add_com_response(REPORT_MODE);
              break;
            case 0b110:
              //zero all axes operation
              if( AUTO_MODE_CHECK ){
                //command not accepted in automatic operation mode
                INVALID_MODE_SET;
                add_com_response(REPORT_STATUS);
                return ;
              }
              zero_axes(serial_info.inc_data);
              break;
          }
        }
      }
    }
  }

  //if there are messages for the master and the hand is not raised , raise the hand to request an ACK
  if( (servo_board.response_index > 0) && !SLAVE_R_PIN_CHECK && (serial_info.ack_received == 0) ){
    SLAVE_R_HIGH;
  }
  //if an ACK was received, increment for a while and then send response
  if ( (serial_info.ack_received == 1)  ){
    if (response_delay < response_cycles) {
      response_delay ++;
      
    }else{
      serial_info.ack_received = 0;
      if(repeat_response_flag == 1){
        repeat_response_flag = 0;
        transmit_response(1);
      }else{
        transmit_response(0);  
      }
      response_delay = 0;  
    }
      
  }
  
}



//Parameter handling functions
void init_EEPROM(){
  eeprom_write(SINGLE_BYTE_PARAM_BASE+VERSION_INT,VERSION_INT_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+VERSION_FRACT,VERSION_FRACT_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+ARDUINO_ID,ARDUINO_ID_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+ZEROING_SPEED,ZEROING_SPEED_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+X_GEAR_RATIO,X_GEAR_RATIO_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+Y_GEAR_RATIO,Y_GEAR_RATIO_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+Z_GEAR_RATIO,Z_GEAR_RATIO_VAL);
  eeprom_write(SINGLE_BYTE_PARAM_BASE+NO_COMPL_FEED,NO_COMPL_FEED_VAL);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2,(X_PULSES_PER_REV_VAL>>8));
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1,(X_PULSES_PER_REV_VAL&0xFF));
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2,(Y_PULSES_PER_REV_VAL>>8));
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1,(Y_PULSES_PER_REV_VAL&0xFF));
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2,(Z_PULSES_PER_REV_VAL>>8));
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1,(Z_PULSES_PER_REV_VAL&0xFF));
  eeprom_write(TWO_BYTE_PARAM_BASE+(MAX_RPM-TWO_BYTE_PARAM_START)*2,(MAX_RPM_VAL>>8));
  eeprom_write(TWO_BYTE_PARAM_BASE+(MAX_RPM-TWO_BYTE_PARAM_START)*2+1,(MAX_RPM_VAL&0xFF));
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2,X_MM_PER_PULLEY_ROT_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1,X_MM_PER_PULLEY_ROT_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2,Y_MM_PER_PULLEY_ROT_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1,Y_MM_PER_PULLEY_ROT_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2,Z_MM_PER_PULLEY_ROT_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1,Z_MM_PER_PULLEY_ROT_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_MM_LEN-TWO_BYTE_PARAM_START)*2,X_MM_LEN_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_MM_LEN-TWO_BYTE_PARAM_START)*2+1,X_MM_LEN_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_MM_LEN-TWO_BYTE_PARAM_START)*2,Y_MM_LEN_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_MM_LEN-TWO_BYTE_PARAM_START)*2+1,Y_MM_LEN_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_MM_LEN-TWO_BYTE_PARAM_START)*2,Z_MM_LEN_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_MM_LEN-TWO_BYTE_PARAM_START)*2+1,Z_MM_LEN_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2,X_COMPL_DELAY_MS_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(X_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1,X_COMPL_DELAY_MS_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2,Y_COMPL_DELAY_MS_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Y_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1,Y_COMPL_DELAY_MS_VAL&0xFF);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2,Z_COMPL_DELAY_MS_VAL>>8);
  eeprom_write(TWO_BYTE_PARAM_BASE+(Z_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1,Z_COMPL_DELAY_MS_VAL&0xFF);
  DEBUG_SERIAL_LN("EEPROM DATA SET TO INITIALIZED VALUES");
  DEBUG_SERIAL_FLUSH;
}

void calculate_servo_params(){
  uint16_t x_pulses_per_rev;
  uint16_t y_pulses_per_rev;
  uint16_t z_pulses_per_rev;
  uint16_t max_rpm;
  uint8_t  x_gear_ratio;
  uint8_t  y_gear_ratio;
  uint8_t  z_gear_ratio;
  uint16_t x_mm_per_pulley_rot;
  uint16_t y_mm_per_pulley_rot;
  uint16_t z_mm_per_pulley_rot;
  //initialize Servo_params struct
  servo_params.version_int = eeprom_read(SINGLE_BYTE_PARAM_BASE+VERSION_INT);
  servo_params.version_fract = eeprom_read(SINGLE_BYTE_PARAM_BASE+VERSION_FRACT);
  servo_params.arduino_id = eeprom_read(SINGLE_BYTE_PARAM_BASE+ARDUINO_ID);
  servo_params.zeroing_speed = eeprom_read(SINGLE_BYTE_PARAM_BASE+ZEROING_SPEED);
  x_gear_ratio = eeprom_read(SINGLE_BYTE_PARAM_BASE+X_GEAR_RATIO);
  y_gear_ratio = eeprom_read(SINGLE_BYTE_PARAM_BASE+Y_GEAR_RATIO);
  z_gear_ratio = eeprom_read(SINGLE_BYTE_PARAM_BASE+Z_GEAR_RATIO);
  servo_params.no_compl_feed = eeprom_read(SINGLE_BYTE_PARAM_BASE+NO_COMPL_FEED);
  x_pulses_per_rev = eeprom_read(TWO_BYTE_PARAM_BASE+(X_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2)<<8;
  x_pulses_per_rev |= eeprom_read(TWO_BYTE_PARAM_BASE+(X_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1);
  y_pulses_per_rev = eeprom_read(TWO_BYTE_PARAM_BASE+(Y_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2)<<8;
  y_pulses_per_rev |= eeprom_read(TWO_BYTE_PARAM_BASE+(Y_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1);
  z_pulses_per_rev = eeprom_read(TWO_BYTE_PARAM_BASE+(Z_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2)<<8;
  z_pulses_per_rev |= eeprom_read(TWO_BYTE_PARAM_BASE+(Z_PULSES_PER_REV-TWO_BYTE_PARAM_START)*2+1);
  max_rpm = eeprom_read(TWO_BYTE_PARAM_BASE+(MAX_RPM-TWO_BYTE_PARAM_START)*2)<<8;
  max_rpm |= eeprom_read(TWO_BYTE_PARAM_BASE+(MAX_RPM-TWO_BYTE_PARAM_START)*2+1);
  x_mm_per_pulley_rot = eeprom_read(TWO_BYTE_PARAM_BASE+(X_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2)<<8;
  x_mm_per_pulley_rot |= eeprom_read(TWO_BYTE_PARAM_BASE+(X_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1);
  y_mm_per_pulley_rot = eeprom_read(TWO_BYTE_PARAM_BASE+(Y_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2)<<8;
  y_mm_per_pulley_rot |= eeprom_read(TWO_BYTE_PARAM_BASE+(Y_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1);
  z_mm_per_pulley_rot = eeprom_read(TWO_BYTE_PARAM_BASE+(Z_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2)<<8;
  z_mm_per_pulley_rot |= eeprom_read(TWO_BYTE_PARAM_BASE+(Z_MM_PER_PULLEY_ROT-TWO_BYTE_PARAM_START)*2+1);
  servo_params.x_mm_len = eeprom_read(TWO_BYTE_PARAM_BASE+(X_MM_LEN-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.x_mm_len |= eeprom_read(TWO_BYTE_PARAM_BASE+(X_MM_LEN-TWO_BYTE_PARAM_START)*2+1);
  servo_params.y_mm_len = eeprom_read(TWO_BYTE_PARAM_BASE+(Y_MM_LEN-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.y_mm_len |= eeprom_read(TWO_BYTE_PARAM_BASE+(Y_MM_LEN-TWO_BYTE_PARAM_START)*2+1);
  servo_params.z_mm_len = eeprom_read(TWO_BYTE_PARAM_BASE+(Z_MM_LEN-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.z_mm_len |= eeprom_read(TWO_BYTE_PARAM_BASE+(Z_MM_LEN-TWO_BYTE_PARAM_START)*2+1);
  servo_params.x_compl_delay_ms = eeprom_read(TWO_BYTE_PARAM_BASE+(X_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.x_compl_delay_ms |= eeprom_read(TWO_BYTE_PARAM_BASE+(X_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1);
  servo_params.y_compl_delay_ms = eeprom_read(TWO_BYTE_PARAM_BASE+(Y_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.y_compl_delay_ms |= eeprom_read(TWO_BYTE_PARAM_BASE+(Y_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1);
  servo_params.z_compl_delay_ms = eeprom_read(TWO_BYTE_PARAM_BASE+(Z_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2)<<8;
  servo_params.z_compl_delay_ms |= eeprom_read(TWO_BYTE_PARAM_BASE+(Z_COMPL_DELAY_MS-TWO_BYTE_PARAM_START)*2+1);

  
  DEBUG_SERIAL("version :");
  DEBUG_SERIAL(servo_params.version_int);
  DEBUG_SERIAL(".");
  DEBUG_SERIAL_LN(servo_params.version_fract);
  DEBUG_SERIAL("Arduino id:");
  DEBUG_SERIAL_LN(servo_params.arduino_id);
  DEBUG_SERIAL("Pulses per rev x:");
  DEBUG_SERIAL(x_pulses_per_rev);
  DEBUG_SERIAL(" ,y:");
  DEBUG_SERIAL(y_pulses_per_rev);
  DEBUG_SERIAL(" ,z:");
  DEBUG_SERIAL_LN(z_pulses_per_rev);
  DEBUG_SERIAL("max rpm:");
  DEBUG_SERIAL_LN(max_rpm);
  DEBUG_SERIAL("zeroing speed:");
  DEBUG_SERIAL_LN(servo_params.zeroing_speed);
  DEBUG_SERIAL("Gear ratio x:");
  DEBUG_SERIAL(x_gear_ratio);
  DEBUG_SERIAL(" y:");
  DEBUG_SERIAL(y_gear_ratio);
  DEBUG_SERIAL(" z:");
  DEBUG_SERIAL_LN(z_gear_ratio);
  DEBUG_SERIAL("mm per pulley x:");
  DEBUG_SERIAL(x_mm_per_pulley_rot);
  DEBUG_SERIAL(" ,y:");
  DEBUG_SERIAL(y_mm_per_pulley_rot);
  DEBUG_SERIAL(" ,z:");
  DEBUG_SERIAL_LN(z_mm_per_pulley_rot);
  DEBUG_SERIAL("Axis len x:");
  DEBUG_SERIAL(servo_params.x_mm_len);
  DEBUG_SERIAL(" ,y:");
  DEBUG_SERIAL(servo_params.y_mm_len);
  DEBUG_SERIAL(" ,z:");
  DEBUG_SERIAL_LN(servo_params.z_mm_len);
  DEBUG_SERIAL("no complete feedback :");
  DEBUG_SERIAL_LN_BIN(servo_params.no_compl_feed);
  DEBUG_SERIAL("x delay:");
  DEBUG_SERIAL(servo_params.x_compl_delay_ms);
  DEBUG_SERIAL(" , y delay:");
  DEBUG_SERIAL(servo_params.y_compl_delay_ms);
  DEBUG_SERIAL(" , z delay:");
  DEBUG_SERIAL_LN(servo_params.z_compl_delay_ms);
  DEBUG_SERIAL_FLUSH;
  
  
  
  
  //calculate constants for switching from toggles to mm and backwards
  //each step requires 2 toggles of the corresponding pin , one low->high and one high->low 
  servo_params.x_toggles_mm_mult = ((2*x_gear_ratio*x_pulses_per_rev)/x_mm_per_pulley_rot);
  servo_params.y_toggles_mm_mult = ((2*y_gear_ratio*y_pulses_per_rev)/y_mm_per_pulley_rot);
  servo_params.z_toggles_mm_mult = ((2*z_gear_ratio*z_pulses_per_rev)/z_mm_per_pulley_rot);
  //calculate frequency constants for each axis
  servo_params.x_freq_const = ((uint32_t)max_rpm*x_pulses_per_rev)/6000;
  servo_params.y_freq_const = ((uint32_t)max_rpm*y_pulses_per_rev)/6000;
  servo_params.z_freq_const = ((uint32_t)max_rpm*z_pulses_per_rev)/6000;  
  
  //set up movement complete pins 
  if( X_NO_COMPL_FEED_CHECK ){
    DEBUG_SERIAL_LN("x has not feedback pin , set as output");
    DEBUG_SERIAL_FLUSH;
    SET_X_COMPL_OUTPUT;
    X_AXIS_MOVE_COMPL_PIN_HIGH;
  }else{
    SET_X_COMPL_INPUT;
    SET_X_COMPL_PULLUP;
  }
  if( Y_NO_COMPL_FEED_CHECK ){
    DEBUG_SERIAL_LN("y has not feedback pin , set as output");
    DEBUG_SERIAL_FLUSH;
    SET_Y_COMPL_OUTPUT;
    Y_AXIS_MOVE_COMPL_PIN_HIGH;
  }else{
    SET_Y_COMPL_INPUT;
    SET_Y_COMPL_PULLUP;
  }
  if( Z_NO_COMPL_FEED_CHECK ){
    DEBUG_SERIAL_LN("z has not feedback pin , set as output");
    DEBUG_SERIAL_FLUSH;
    SET_Z_COMPL_OUTPUT;
    Z_AXIS_MOVE_COMPL_PIN_HIGH;
  }else{
    SET_Z_COMPL_INPUT;
    SET_Z_COMPL_PULLUP;
  }
}



//Initialization function for the servo board (has to be called in the program)
void init_servo_board(uint32_t baud_rate){
  Serial.begin(baud_rate);
  
  uint8_t sreg_temp;
  
  SET_RS485_CONTR_OUTPUT; //prevent the slave from transmitting
  
  //TIMER0 is already set to run, stop it
  TIMSK0 =0;  //clear interrupt mask
  sreg_temp = SREG;
  cli();
  TCCR0B = 0 ;  //disable timer 0 clock input
  TIMER0_PRESCALER_RESET;
  //Restore SREG 
  SREG = sreg_temp;
  #ifdef INIT_EEPROM
  //initialize EEPROM values to 0
  init_EEPROM();
  #endif
  
  //INIT GLOBAL STRUCTS
  calculate_servo_params();
  //initialize saved_commands struct
  for(int i=0;i<60;i++){
    saved_commands.move_info[i] = 0;
    saved_commands.delay_info[i] = 0;
  } 
  saved_commands.index = 0;
  saved_commands.num = 0;
  saved_commands.x_auto_start_index = 255;
  saved_commands.y_auto_start_index = 255;
  saved_commands.z_auto_start_index = 255;

  //initialize servo_board structure
  servo_board.servo_status = 0;

  //set move end bits so that the status is idle
  ALL_AXES_MOVE_END_SET;
  //set error that the axes have not been zeroed yet
  AXES_NOT_ZEROED_SET;
  //set error that the loop is not verified
  LOOP_ERROR_SET;
  //set error that the module has restarted
  SERVO_RESTART_SET;
  
  servo_board.com_status = 0;
  servo_board.last_response = 0;
  for(int i = 0; i<10 ; i++){
    servo_board.com_response[i] = 0;  
  }
  servo_board.response_index = 0;
  servo_board.mode = 0;
  servo_board.timer_status = 0;
  
  //initialize servo_position struct
  servo_position.toggles_x = 0;
  servo_position.toggles_end_x = 0;
  servo_position.toggles_y = 0;
  servo_position.toggles_end_y = 0;
  servo_position.toggles_z = 0;
  servo_position.toggles_end_z = 0;

  //add a response to inform the master of the restart
  DEBUG_SERIAL_LN("Restart");
  DEBUG_SERIAL_FLUSH;
  add_com_response(REPORT_STATUS);
  /*
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  add_com_response(REPORT_STATUS);
  */
  
  //set up timer0 (z axis)
  TIMSK0 =0;  //clear interrupt mask
  sreg_temp = SREG;
  cli();
  TCCR0B = 0 ;  //disable timer 0 clock input
  TIMER0_PRESCALER_RESET;
  //Restore SREG 
  SREG = sreg_temp;
  TCCR0A = 0 ;  //reset TCCR0A register, disconnect outputs
  TCNT0  = 0 ;  //reset counter value
  TCCR0A |= 1<<6; //set compare output mode to toggle OC0A on compare match
  TCCR0A |= 1<<1; //set CTC mode
  TIFR0 &= ~(0b111); //clear interrupt flag register
  TIMSK0 |= 1<<1; //enable output compare match A interrupt
  SET_Z_PULSE_OUTPUT;

  
  //set up timer1 (y axis)
  TIMSK1 = 0; //clear interrupt mask
  sreg_temp = SREG;
  cli();
  TCCR1B = 0; //disable timer1 clock input
  TIMER1_PRESCALER_RESET;
  //Restore SREG 
  SREG = sreg_temp;
  TCCR1A = 0; //reset TCCR1A register, disconnect outputs
  //TCNT1 is a 16 bit register
  //write the high byte first, then the low byte
  //should be handled by the compiler
  TCNT1 = 0;  //reset counter value
  TCCR1A |= 1<<6; //set compare output mode to toggle 0C1A on compare match
  TCCR1B |= 1<<3; //set CTC mode
  TIFR1 |= (1<<5) | (0b111);  //set bits to clear interrupt flag register
  TIMSK1 |= 1<<1; //enable output compare match A interrupt
  SET_Y_PULSE_OUTPUT;

  //set up timer2 (x axis)
  TIMSK2 = 0; //clear interrupt mask
  sreg_temp = SREG;
  cli();
  TCCR2B = 0; //disable timer2 clock input
  TIMER2_PRESCALER_RESET;
  //Restore SREG 
  SREG = sreg_temp;
  TCCR2A = 0; //reset TCCR2A register, disconnect outputs
  TCNT2 = 0;  //reset counter value
  TCCR2A |= 1<<6; //set compare output mode to toggle OC2A on compare match
  TCCR2A |= 1<<1; //set CTC mode
  TIFR2 |= 0b111; //set bits to clear interrupt flag register
  TIMSK2 |= 1<<1; //enable output compare match A interrupt
  SET_X_PULSE_OUTPUT;
  

  //set up servo pins
  SET_Z_DIR_OUTPUT;
  SET_Y_DIR_OUTPUT;
  SET_X_DIR_OUTPUT;
  
  SET_ALARM_INPUT_PULLUP;
  SET_Z_BRAKE_OUTPUT;
  Z_AXIS_BRAKE_DISABLE;
  
  SLAVE_R_LOW;
  SET_SLAVE_R_OUTPUT;
  
  Serial.println("init completed");
  Serial.flush();
}



//Update function for the servo board (has to be called in the program)
void servo_board_update(){
  check_movement_end();
  check_inductive_sensors();
  execute_auto_move(0);
  check_alarm();
  handle_serial();
}


void setup() {
  
  // put your setup code here, to run once:
  //init_servo_board(9600);
  init_servo_board(57600);
  
}


void loop() {
  servo_board_update();
}
