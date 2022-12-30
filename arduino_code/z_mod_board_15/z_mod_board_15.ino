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

#define ARDUINO_ID 3
#define DISABLE_INTERRUPTS SREG&=~(1<<7);
#define ENABLE_INTERRUPTS  SREG|=(1<<7);


//defines for pin setup
#define SET_RS485_CONTR_OUTPUT  DDRD|=(1<<2)
#define SET_SLAVE_R_INPUT       DDRD&=~(1<<3)
#define SET_SLAVE_R_OUTPUT      DDRD|=(1<<3)
#define SET_OUT3_OUTPUT         DDRB|=(1<<1)
#define SET_OUT2_OUTPUT         DDRB|=1
#define SET_OUT1_OUTPUT         DDRD|=(1<<7)
#define SET_IN3_INPUT           DDRD&=~(1<<4)
#define SET_IN2_INPUT           DDRD&=~(1<<5)
#define SET_IN1_INPUT           DDRD&=~(1<<6)

//defines for setting pullups
#define SET_IN3_PULLUP          PORTD|=(1<<4)
#define SET_IN2_PULLUP          PORTD|=(1<<5)
#define SET_IN1_PULLUP          PORTD|=(1<<6)


//defines for pin outputs (set pin HIGH)
#define RS485_CONTROL_PIN_HIGH  PORTD|=(1<<2)
#define SLAVE_R_HIGH            PORTD|=(1<<3)
#define SET_OUT3_HIGH           PORTB|=(1<<1)
#define SET_OUT2_HIGH           PORTB|=1
#define SET_OUT1_HIGH           PORTD|=(1<<7)


//defines for pin outputs (set pin LOW)
#define RS485_CONTROL_PIN_LOW   PORTD&=~(1<<2)
#define SLAVE_R_LOW             PORTD&=~(1<<3)
#define SET_OUT3_LOW            PORTB&=~(1<<1)
#define SET_OUT2_LOW            PORTB&=~1
#define SET_OUT1_LOW            PORTD&=~(1<<7)



//defines for reading pin inputs (returns 0 for LOW and 1 for HIGH)
#define SLAVE_R_PIN_CHECK       ((PIND>>3)&1)
#define IN3_CHECK               ((PIND>>4)&1)
#define IN2_CHECK               ((PIND>>5)&1)
#define IN1_CHECK               ((PIND>>6)&1)



//z_board.z_status set defines
#define SAMPLE_TIMEOUT_SET  z_board.z_status|=(1<<7)  //used with a timer to prevent flicker from inputs
#define IN3_STATUS_SET      z_board.z_status|=(1<<6)
#define IN2_STATUS_SET      z_board.z_status|=(1<<5)
#define IN1_STATUS_SET      z_board.z_status|=(1<<4)
#define OUT3_STATUS_SET     z_board.z_status|=(1<<3)
#define OUT2_STATUS_SET     z_board.z_status|=(1<<2)
#define OUT1_STATUS_SET     z_board.z_status|=(1<<1)
#define Z_MOD_RESTART_SET   z_board.z_status|=1
//z_board.z_status reset defines
#define SAMPLE_TIMEOUT_RESET  z_board.z_status&=~(1<<7)
#define IN3_STATUS_RESET      z_board.z_status&=~(1<<6)
#define IN2_STATUS_RESET      z_board.z_status&=~(1<<5)
#define IN1_STATUS_RESET      z_board.z_status&=~(1<<4)
#define OUT3_STATUS_RESET     z_board.z_status&=~(1<<3)
#define OUT2_STATUS_RESET     z_board.z_status&=~(1<<2)
#define OUT1_STATUS_RESET     z_board.z_status&=~(1<<1)
#define Z_MOD_RESTART_RESET   z_board.z_status&=~1
#define OUTPUTS_RESET         z_board.z_status&=~(0b111<<1)
//z_board.z_status check defines
#define SAMPLE_TIMEOUT_CHECK  ((z_board.z_status>>7)&1)
#define IN3_STATUS_CHECK      ((z_board.z_status>>6)&1)
#define IN2_STATUS_CHECK      ((z_board.z_status>>5)&1)
#define IN1_STATUS_CHECK      ((z_board.z_status>>4)&1)
#define OUT3_STATUS_CHECK     ((z_board.z_status>>3)&1)
#define OUT2_STATUS_CHECK     ((z_board.z_status>>2)&1)
#define OUT1_STATUS_CHECK     ((z_board.z_status>>1)&1)
//z_board.com_status set defines
#define COM_SLAVE_CONTROL_SET     z_board.com_status|=(1<<2)
#define COM_MASTER_CONTROL_SET    z_board.com_status|=(1<<1)
#define COM_SERIAL_BUSY_SET       z_board.com_status|=(1)
//servo_board.com_status reset defines 
#define COM_SLAVE_CONTROL_RESET     z_board.com_status&=~(1<<2)
#define COM_MASTER_CONTROL_RESET    z_board.com_status&=~(1<<1)
#define COM_SERIAL_BUSY_RESET       z_board.com_status&=~(1)
//servo_board.com_status check if set defines
#define COM_SLAVE_CONTROL_CHECK     ((z_board.com_status>>2)&1)
#define COM_MASTER_CONTROL_CHECK    ((z_board.com_status>>1)&1)
#define COM_SERIAL_BUSY_CHECK       (z_board.com_status & 1)

typedef struct{
  volatile uint8_t z_status;  
  volatile uint8_t  com_status;     
  volatile uint32_t com_response[10];
  uint32_t last_response;
  volatile uint8_t  response_index;
}Z_board;

Z_board z_board;  //declare z_board as a global




typedef struct{
  uint8_t  ignore_bytes;
  uint8_t  message_length;
  uint8_t  index;
  uint8_t  operation;
  uint32_t inc_data;
  uint8_t  ack_received;
}Serial_info;




ISR(TIMER0_COMPA_vect){
  static uint8_t isr_counter;
  isr_counter++;
  if(isr_counter>15){
    //about 15ms elapsed
    TCCR0B =0 ; //stop timer from running
    SAMPLE_TIMEOUT_RESET;
    isr_counter = 0;
  }
  
}

//interrupt setup defines
#define ENABLE_INT_MASK         EIMSK|=(1<<1)
#define DISABLE_INT_MASK        EIMSK&=~(1<<1)
#define RESET_INT_FLAG          EIFR|=(1<<1)
#define SET_FALLING_EDGE_TRIG   EICRA=(0b10<<2)
#define SET_RISING_EDGE_TRIG    EICRA=(0b11<<2)

//transmit_response defines
#define RESPONSE_LENGTH       ((current_response>>27)&0b11) 
#define RESPONSE_OPERATION    ((current_response>>24)&0b111)
#define RESPONSE_FIRST_BYTE   (current_response>>24)
void transmit_response(uint8_t repeat_flag){
  static uint8_t params_byte_index;
  uint8_t response_bytes[4];
  uint32_t current_response;
  if(repeat_flag == 0){
    current_response = z_board.com_response[0]; 
  }else{
    current_response = z_board.last_response;
  }
  response_bytes[0] = RESPONSE_FIRST_BYTE;
  for(int i = 0 ; i < RESPONSE_LENGTH ; i++){
    response_bytes[i+1] = (current_response>>(8*(RESPONSE_LENGTH-(i+1)))) & 0xFF ;
  }
  DEBUG_SERIAL_FLUSH;
  #ifndef DEBUGGING
  Serial.flush();
  #endif

  
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

  if(repeat_flag == 0){
    //store the response in case the master requests it again
    z_board.last_response = z_board.com_response[0];

    //remove the response that was sent to the master from the array
    for(int i = 0 ; i < z_board.response_index - 1; i++){
      z_board.com_response[i] = z_board.com_response[i+1];  //replace each response with the next in line
    }
    z_board.com_response[z_board.response_index-1] = 0; //delete the command pointed at by the index
    z_board.response_index--; //decrement the index 

  }
  
  
  
} 

  


//add_com_response defines
#define REPORT_STATUS               (0)
#define REPORT_STATUS_RESPONSE      ((((uint32_t)((ARDUINO_ID<<5)|(0b1<<3)))<<24)|z_board.z_status)
void add_com_response(uint8_t response_type){
  if(z_board.response_index >= 10){
    //com_response[] is full, response will be lost, abort
    DEBUG_SERIAL_LN("z_board.com_response[] is full, response lost");
    DEBUG_SERIAL_FLUSH;
    return ;  
  }
  //uint32_t servo_response;
  switch (response_type)
  {
    case REPORT_STATUS:
      z_board.com_response[z_board.response_index] = REPORT_STATUS_RESPONSE; 
      Z_MOD_RESTART_RESET;
      break;
  }
  //increment index
  z_board.response_index++;
}



void check_inputs(){
  if(!SAMPLE_TIMEOUT_CHECK){
    if( (IN1_CHECK ) != (IN1_STATUS_CHECK) ){
      if(IN1_CHECK){
        IN1_STATUS_SET;  
      }else{
        IN1_STATUS_RESET;  
      }
      SAMPLE_TIMEOUT_SET; 
    }
    if( (IN2_CHECK ) != (IN2_STATUS_CHECK) ){
      if(IN2_CHECK){
        IN2_STATUS_SET;  
      }else{
        IN2_STATUS_RESET;  
      }
      SAMPLE_TIMEOUT_SET; 
    }
    if( (IN3_CHECK ) != (IN3_STATUS_CHECK) ){
      if(IN3_CHECK){
        IN3_STATUS_SET;  
      }else{
        IN3_STATUS_RESET;  
      }
      SAMPLE_TIMEOUT_SET; 
    }
    if(SAMPLE_TIMEOUT_CHECK){
      //at least 1 input was updated , add a response and start the timeout timer
      add_com_response(REPORT_STATUS);
      TCCR0B |= 0b101; 
    }
  }
}



void handle_servo_response(){
  
}

//handle_serial defines
#define ACK_OPERATION            0b111
#define ACK_ID                  (inc_data & 0b111)

#define SERIAL_ID               (inc_data>>5)
#define SERIAL_MESSAGE_LENGHT   ((inc_data>>3)&0b11)
#define SERIAL_OPERATION        (inc_data & 0b111)
#define SET_Z_STATUS_SERIAL z_board.z_status|=(serial_info.inc_data&0b111)<<1
void handle_Serial(){
  
  static Serial_info serial_info; //no need to initialise since its declared static
  static uint16_t response_delay;
  static uint16_t response_cycles;
  static uint8_t repeat_response_flag;

  if(Serial.available() > 0 ){
    if(serial_info.ignore_bytes > 0){
      //read the byte and ignore it , decrement the ignore_bytes counter
      uint8_t ignore_data = Serial.read();
      //Serial.print("ignoring ");
      //Serial.println(ignore_data,BIN);
      //Serial.flush();
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
              case 0b0:
                //Serial.println("REPORT");
                //Serial.flush();
                //Report inputs operation
                add_com_response(REPORT_STATUS);
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
            if (z_board.response_index > 0) {
              //Serial.println("ACK");
              //Serial.flush();
              serial_info.ack_received = 1;
              if(!SAMPLE_TIMEOUT_CHECK){
                response_cycles = 75;
              }else{
                //set response_cycles to 300 to account for reduced time per cycle while sampling has timed out
                response_cycles = 300;
              }
              SLAVE_R_LOW;  
            }
          }
        }else{
          //message is targeting another slave , get the length to ingore that amount of incoming bytes
          DEBUG_SERIAL("message for another slave ");
          DEBUG_SERIAL_LN_BIN(inc_data);
          DEBUG_SERIAL_FLUSH;
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
            case 0b1:
              //Set outputs operation
              //Serial.println("SET");
              //Serial.flush();
              OUTPUTS_RESET;
              SET_Z_STATUS_SERIAL;
              if(OUT3_STATUS_CHECK){
                SET_OUT3_HIGH;
              }else{
                SET_OUT3_LOW;
              }
              if(OUT2_STATUS_CHECK){
                SET_OUT2_HIGH;
              }else{
                SET_OUT2_LOW;
              }
              if(OUT1_STATUS_CHECK){
                SET_OUT1_HIGH;
              }else{
                SET_OUT1_LOW;
              }
              add_com_response(REPORT_STATUS);
              break;
          }
        }
      }
    }
  }
  
  //if there are messages for the master and the hand is not raised , raise the hand to request an ACK
  if( (z_board.response_index > 0) && !SLAVE_R_PIN_CHECK && (serial_info.ack_received == 0) ){
    SLAVE_R_HIGH;
  }
  //if an ACK was received , increment for a while and then send response
  if ( (serial_info.ack_received == 1) ){
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




void init_z_mod_board(uint32_t baud_rate){
  Serial.begin(baud_rate);
  SET_RS485_CONTR_OUTPUT; //prevent the slave from transmitting
  
  //set up timer0 to sample vaccum input
  TCCR0B = 0 ;  //disable timer 0 clock input
  TIMSK0 =0;  //clear interrupt mask
  TCCR0A = 0 ;  //reset TCCR0A register, disconnect outputs
  TCNT0  = 0 ;  //reset counter value
  TCCR0A |= 1<<1; //set CTC mode
  OCR0A = 15; //set compare match at 15 -> interrupt triggers every 0.96ms
  //OCR0A = 10;
  TIFR0 &= ~(B111); //clear interrupt flag register
  TIMSK0 |= 1<<1; //enable output compare match A interrupt

  //initialize z_board structure
  z_board.z_status = 0;
  z_board.com_status = 0;
  z_board.last_response = 0;
  for(int i = 0; i<10 ; i++){
    z_board.com_response[i] = 0;  
  }
  z_board.response_index = 0;

  Z_MOD_RESTART_SET;

  //set up z_mod pins
  SET_OUT3_OUTPUT;
  SET_OUT2_OUTPUT;
  SET_OUT1_OUTPUT;
  SET_IN3_INPUT;
  SET_IN2_INPUT;
  SET_IN1_INPUT;
  SET_IN3_PULLUP;
  SET_IN2_PULLUP;
  SET_IN1_PULLUP;
  
  SLAVE_R_LOW;
  SET_SLAVE_R_OUTPUT;
  

  //set OUT1 HIGH to open the gripper
  SET_OUT1_HIGH;
  OUT1_STATUS_SET;
  
  
  //opening the gripper will cause input1 to go high shortly after
  //and this will trigger a response to the master, also indicating 
  //that z_mod has restarted
  Serial.println("init completed");
  Serial.flush();
}


void setup() {
  // put your setup code here, to run once:
  //init_z_mod_board(9600);  
  init_z_mod_board(57600);  
  
}

void loop() {
  check_inputs();
  handle_Serial();
}
