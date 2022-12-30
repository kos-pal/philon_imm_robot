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

#define ARDUINO_ID 1
#define DISABLE_INTERRUPTS SREG&=~(1<<7);
#define ENABLE_INTERRUPTS  SREG|=(1<<7);


//defines for pin setup
#define SET_RS485_CONTR_OUTPUT  DDRD|=(1<<2)
#define SET_SLAVE_R_INPUT       DDRD&=~(1<<3)
#define SET_SLAVE_R_OUTPUT      DDRD|=(1<<3)
#define SET_RELAY8_OUTPUT       DDRB|=(1<<3)
#define SET_RELAY7_OUTPUT       DDRB|=(1<<2)
#define SET_RELAY6_OUTPUT       DDRB|=(1<<1)
#define SET_RELAY5_OUTPUT       DDRB|=1
#define SET_RELAY4_OUTPUT       DDRD|=(1<<7)
#define SET_RELAY3_OUTPUT       DDRD|=(1<<6)
#define SET_RELAY2_OUTPUT       DDRD|=(1<<5)
#define SET_RELAY1_OUTPUT       DDRD|=(1<<4)
#define SET_S7_INPUT            DDRC&=~(1<<5)
#define SET_S6_INPUT            DDRC&=~(1<<4)
#define SET_S5_INPUT            DDRC&=~(1<<3)
#define SET_S4_INPUT            DDRC&=~(1<<2)
#define SET_S3_INPUT            DDRC&=~(1<<1)
#define SET_S2_INPUT            DDRC&=~1
#define SET_S1_INPUT            DDRB&=~(1<<4)

//defines for setting pullups
#define SET_S7_PULLUP          PORTC|=(1<<5)
#define SET_S6_PULLUP          PORTC|=(1<<4)
#define SET_S5_PULLUP          PORTC|=(1<<3)
#define SET_S4_PULLUP          PORTC|=(1<<2)
#define SET_S3_PULLUP          PORTC|=(1<<1)
#define SET_S2_PULLUP          PORTC|=1
#define SET_S1_PULLUP          PORTB|=(1<<4)


//defines for pin outputs (set pin HIGH)
#define RS485_CONTROL_PIN_HIGH    PORTD|=(1<<2)
#define SLAVE_R_HIGH              PORTD|=(1<<3)
#define SET_RELAY8_HIGH           PORTB|=(1<<3)
#define SET_RELAY7_HIGH           PORTB|=(1<<2)
#define SET_RELAY6_HIGH           PORTB|=(1<<1)
#define SET_RELAY5_HIGH           PORTB|=1
#define SET_RELAY4_HIGH           PORTD|=(1<<7)
#define SET_RELAY3_HIGH           PORTD|=(1<<6)
#define SET_RELAY2_HIGH           PORTD|=(1<<5)
#define SET_RELAY1_HIGH           PORTD|=(1<<4)


//defines for pin outputs (set pin LOW)
#define RS485_CONTROL_PIN_LOW    PORTD&=~(1<<2)
#define SLAVE_R_LOW              PORTD&=~(1<<3)
#define SET_RELAY8_LOW           PORTB&=~(1<<3)
#define SET_RELAY7_LOW           PORTB&=~(1<<2)
#define SET_RELAY6_LOW           PORTB&=~(1<<1)
#define SET_RELAY5_LOW           PORTB&=~1
#define SET_RELAY4_LOW           PORTD&=~(1<<7)
#define SET_RELAY3_LOW           PORTD&=~(1<<6)
#define SET_RELAY2_LOW           PORTD&=~(1<<5)
#define SET_RELAY1_LOW           PORTD&=~(1<<4)


//defines for reading pin inputs (returns 0 for LOW and 1 for HIGH)
#define SLAVE_R_PIN_CHECK       ((PIND>>3)&1)
#define IN3_CHECK               ((PIND>>4)&1)
#define IN2_CHECK               ((PIND>>5)&1)
#define IN1_CHECK               ((PIND>>6)&1)
#define S7_CHECK          ((PINC>>1)&5)
#define S6_CHECK          ((PINC>>1)&4)
#define S5_CHECK          ((PINC>>1)&3)
#define S4_CHECK          ((PINC>>1)&2)
#define S3_CHECK          ((PINC>>1)&1)
#define S2_CHECK          (PINC&1)
#define S1_CHECK          ((PINB>>4)&1)
#define S2_S7_CHECK       (PINC&0b111111)

//imm_board.imm_status set defines
#define RELAY8_STATUS_SET   imm_board.imm_status|=(1<<15)
#define RELAY7_STATUS_SET   imm_board.imm_status|=(1<<14)
#define RELAY6_STATUS_SET   imm_board.imm_status|=(1<<13)
#define RELAY5_STATUS_SET   imm_board.imm_status|=(1<<12)
#define RELAY4_STATUS_SET   imm_board.imm_status|=(1<<11)
#define RELAY3_STATUS_SET   imm_board.imm_status|=(1<<10)
#define RELAY2_STATUS_SET   imm_board.imm_status|=(1<<9)
#define RELAY1_STATUS_SET   imm_board.imm_status|=(1<<8)
#define S7_STATUS_SET       imm_board.imm_status|=(1<<7)
#define S6_STATUS_SET       imm_board.imm_status|=(1<<6)
#define S5_STATUS_SET       imm_board.imm_status|=(1<<5)
#define S4_STATUS_SET       imm_board.imm_status|=(1<<4)
#define S3_STATUS_SET       imm_board.imm_status|=(1<<3)
#define S2_STATUS_SET       imm_board.imm_status|=(1<<2)
#define S1_STATUS_SET       imm_board.imm_status|=(1<<1)
#define IMM_RESTART_SET     imm_board.imm_status|=1
//imm_board.imm_status reset defines
#define RELAY8_STATUS_RESET   imm_board.imm_status&=~(1<<15)
#define RELAY7_STATUS_RESET   imm_board.imm_status&=~(1<<14)
#define RELAY6_STATUS_RESET   imm_board.imm_status&=~(1<<13)
#define RELAY5_STATUS_RESET   imm_board.imm_status&=~(1<<12)
#define RELAY4_STATUS_RESET   imm_board.imm_status&=~(1<<11)
#define RELAY3_STATUS_RESET   imm_board.imm_status&=~(1<<10)
#define RELAY2_STATUS_RESET   imm_board.imm_status&=~(1<<9)
#define RELAY1_STATUS_RESET   imm_board.imm_status&=~(1<<8)
#define S7_STATUS_RESET       imm_board.imm_status&=~(1<<7)
#define S6_STATUS_RESET       imm_board.imm_status&=~(1<<6)
#define S5_STATUS_RESET       imm_board.imm_status&=~(1<<5)
#define S4_STATUS_RESET       imm_board.imm_status&=~(1<<4)
#define S3_STATUS_RESET       imm_board.imm_status&=~(1<<3)
#define S2_STATUS_RESET       imm_board.imm_status&=~(1<<2)
#define S1_STATUS_RESET       imm_board.imm_status&=~(1<<1)
#define IMM_RESTART_RESET     imm_board.imm_status&=~1
#define INPUTS_STATUS_RESET   imm_board.imm_status&=~(0b1111111<<1)
#define RELAYS_STATUS_RESET   imm_board.imm_status&=~(0xFF<<8)
//imm_board.imm_status check defines
#define RELAY8_STATUS_CHECK ((imm_board.imm_status>>15)&1)
#define RELAY7_STATUS_CHECK ((imm_board.imm_status>>14)&1)
#define RELAY6_STATUS_CHECK ((imm_board.imm_status>>13)&1)
#define RELAY5_STATUS_CHECK ((imm_board.imm_status>>12)&1)
#define RELAY4_STATUS_CHECK ((imm_board.imm_status>>11)&1)
#define RELAY3_STATUS_CHECK ((imm_board.imm_status>>10)&1)
#define RELAY2_STATUS_CHECK ((imm_board.imm_status>>9)&1)
#define RELAY1_STATUS_CHECK ((imm_board.imm_status>>8)&1)
#define S7_STATUS_CHECK     ((imm_board.imm_status>>7)&1)
#define S6_STATUS_CHECK     ((imm_board.imm_status>>6)&1)
#define S5_STATUS_CHECK     ((imm_board.imm_status>>5)&1)
#define S4_STATUS_CHECK     ((imm_board.imm_status>>4)&1)
#define S3_STATUS_CHECK     ((imm_board.imm_status>>3)&1)
#define S2_STATUS_CHECK     ((imm_board.imm_status>>2)&1)
#define S1_STATUS_CHECK     ((imm_board.imm_status>>1)&1)
//imm_board.com_status set defines
#define COM_SLAVE_CONTROL_SET     imm_board.com_status|=(1<<2)
#define COM_MASTER_CONTROL_SET    imm_board.com_status|=(1<<1)
#define COM_SERIAL_BUSY_SET       imm_board.com_status|=(1)
//servo_board.com_status reset defines 
#define COM_SLAVE_CONTROL_RESET     imm_board.com_status&=~(1<<2)
#define COM_MASTER_CONTROL_RESET    imm_board.com_status&=~(1<<1)
#define COM_SERIAL_BUSY_RESET       imm_board.com_status&=~(1)
//servo_board.com_status check if set defines
#define COM_SLAVE_CONTROL_CHECK     ((imm_board.com_status>>2)&1)
#define COM_MASTER_CONTROL_CHECK    ((imm_board.com_status>>1)&1)
#define COM_SERIAL_BUSY_CHECK       (imm_board.com_status & 1)

typedef struct{
  volatile uint16_t imm_status;  
  volatile uint8_t  com_status;     
  volatile uint32_t com_response[10];
  uint32_t last_response;
  volatile uint8_t  response_index;
}Imm_board;

Imm_board imm_board;  //declare imm_board as a global




typedef struct{
  uint8_t  ignore_bytes;
  uint8_t  message_length;
  uint8_t  index;
  uint8_t  operation;
  uint32_t inc_data;
  uint8_t  ack_received;
}Serial_info;






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
void transmit_response(uint8_t repeat_flag){
  static uint8_t params_byte_index;
  uint8_t response_bytes[4];
  uint32_t current_response;
  if(repeat_flag == 0){
    current_response = imm_board.com_response[0]; 
  }else{
    current_response = imm_board.last_response;
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
    imm_board.last_response = imm_board.com_response[0];
    
    //remove the response that was sent to the master from the array
    for(int i = 0 ; i < imm_board.response_index - 1; i++){
      imm_board.com_response[i] = imm_board.com_response[i+1];  //replace each response with the next in line
    }
    imm_board.com_response[imm_board.response_index-1] = 0; //delete the command pointed at by the index
    imm_board.response_index--; //decrement the index 
  }
  
  
} 





//add_com_response defines
#define REPORT_STATUS               (0)
#define REPORT_STATUS_RESPONSE      ((((uint32_t)((ARDUINO_ID<<5)|(0b10<<3)))<<24)|imm_board.imm_status)
void add_com_response(uint8_t response_type){
  if(imm_board.response_index >= 10){
    //com_response[] is full, response will be lost, abort
    DEBUG_SERIAL_LN("imm_board.com_response[] is full, response lost");
    DEBUG_SERIAL_FLUSH;
    return ;  
  }
  
  switch (response_type)
  {
    case REPORT_STATUS:
      imm_board.com_response[imm_board.response_index] = REPORT_STATUS_RESPONSE; 
      IMM_RESTART_RESET;
      break;
  }
  //increment index
  imm_board.response_index++;
}



ISR(TIMER0_COMPA_vect){
  static uint8_t isr_counter;
  isr_counter++;
  if(isr_counter>15){
    //about 15ms elapsed
    TCCR0B =0 ; //stop timer from running
    //sample the inputs pins
    //imm_status bits 7-1
    // PINC5-0 and PINB4
    if( (S1_CHECK!=S1_STATUS_CHECK) || ( S2_S7_CHECK!=((imm_board.imm_status>>2)&0b111111) )){
      //a input has changed status, update imm_status bits
      INPUTS_STATUS_RESET;
      imm_board.imm_status|=(S2_S7_CHECK<<2)|(S1_CHECK<<1); 
      add_com_response(REPORT_STATUS);
    }
    isr_counter = 0;
    //Restart the sampling timer
    TCCR0B |= 0b101;
  }
}







//handle_serial defines
#define ACK_OPERATION            0b111
#define ACK_ID                  (inc_data & 0b111)

#define SERIAL_ID               (inc_data>>5)
#define SERIAL_MESSAGE_LENGHT   ((inc_data>>3)&0b11)
#define SERIAL_OPERATION        (inc_data & 0b111)
#define SET_IMM_STATUS_SERIAL   imm_board.imm_status|=(serial_info.inc_data&0xFF)<<8
void handle_Serial(){
  
  static Serial_info serial_info; //no need to initialise since its declared static
  static uint8_t response_delay ;
  static uint8_t repeat_response_flag;
  
  if(Serial.available() > 0 ){
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
              case 0b0:
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
            if (imm_board.response_index > 0) {
              serial_info.ack_received = 1;  
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
              //Set relays operation
              RELAYS_STATUS_RESET;
              SET_IMM_STATUS_SERIAL;
              if(RELAY8_STATUS_CHECK){
                SET_RELAY8_HIGH;
              }else{
                SET_RELAY8_LOW;
              }
              if(RELAY7_STATUS_CHECK){
                SET_RELAY7_HIGH;
              }else{
                SET_RELAY7_LOW;
              }
              if(RELAY6_STATUS_CHECK){
                SET_RELAY6_HIGH;
              }else{
                SET_RELAY6_LOW;
              }
              if(RELAY5_STATUS_CHECK){
                SET_RELAY5_HIGH;
              }else{
                SET_RELAY5_LOW;
              }
              if(RELAY4_STATUS_CHECK){
                SET_RELAY4_HIGH;
              }else{
                SET_RELAY4_LOW;
              }
              if(RELAY3_STATUS_CHECK){
                SET_RELAY3_HIGH;
              }else{
                SET_RELAY3_LOW;
              }
              if(RELAY2_STATUS_CHECK){
                SET_RELAY2_HIGH;
              }else{
                SET_RELAY2_LOW;
              }
              if(RELAY1_STATUS_CHECK){
                SET_RELAY1_HIGH;
              }else{
                SET_RELAY1_LOW;
              }
              add_com_response(REPORT_STATUS);
              break;
          }
        }
      }
    }
  }

  
  //if there are messages for the master , the hand is not raised and no
  //ack has been received yet , raise the hand to request an ACK
  if( (imm_board.response_index > 0) && !SLAVE_R_PIN_CHECK && (serial_info.ack_received == 0) ){
    SLAVE_R_HIGH;
  }
  //if han ACK was received, increment for a while and then send response
  if ( (serial_info.ack_received == 1) ){
    if (response_delay < 225) {
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




void init_imm_board(uint32_t baud_rate){
  Serial.begin(baud_rate);
  SET_RS485_CONTR_OUTPUT; //prevent the slave from transmitting

  //set up timer0 to sample imm inputs every 5ms
  TCCR0B = 0 ;  //disable timer 0 clock input
  TIMSK0 =0;  //clear interrupt mask
  TCCR0A = 0 ;  //reset TCCR0A register, disconnect outputs
  TCNT0  = 0 ;  //reset counter value
  TCCR0A |= 1<<1; //set CTC mode
  OCR0A = 15; //set compare match at 15 -> interrupt triggers every 0.96ms
  //OCR0A = 10;
  TIFR0 &= ~(B111); //clear interrupt flag register
  TIMSK0 |= 1<<1; //enable output compare match A interrupt
  
  //initialize imm_board structure
  imm_board.imm_status = 0;
  imm_board.com_status = 0;
  imm_board.last_response = 0;
  for(int i = 0; i<10 ; i++){
    imm_board.com_response[i] = 0;  
  }
  imm_board.response_index = 0;

  IMM_RESTART_SET;
  
  
  //set up imm_board pins
  SET_RELAY8_OUTPUT;       
  SET_RELAY7_OUTPUT;     
  SET_RELAY6_OUTPUT;       
  SET_RELAY5_OUTPUT;       
  SET_RELAY4_OUTPUT;       
  SET_RELAY3_OUTPUT;       
  SET_RELAY2_OUTPUT;       
  SET_RELAY1_OUTPUT;     
  SET_S7_INPUT;            
  SET_S6_INPUT;           
  SET_S5_INPUT;           
  SET_S4_INPUT;           
  SET_S3_INPUT;            
  SET_S2_INPUT;          
  SET_S1_INPUT;           
  SET_S7_PULLUP;        
  SET_S6_PULLUP;          
  SET_S5_PULLUP;          
  SET_S4_PULLUP;          
  SET_S3_PULLUP;          
  SET_S2_PULLUP;          
  SET_S1_PULLUP;          
  
  //preset relays
  SET_RELAY4_HIGH;
  SET_RELAY3_HIGH;
  RELAY3_STATUS_SET;
  RELAY4_STATUS_SET;

  
  SLAVE_R_LOW;
  SET_SLAVE_R_OUTPUT;

  //get a first reading of the input pins and update imm_status
  imm_board.imm_status|=(S2_S7_CHECK<<2)|(S1_CHECK<<1); 
  add_com_response(REPORT_STATUS);
  
  Serial.println("init completed");
  Serial.flush();
  //start the sampling timer
  TCCR0B |= 0b101;
}



void setup() {
  //init_imm_board(9600);
  init_imm_board(57600);
}

void loop() {
  
  handle_Serial();
  
}
