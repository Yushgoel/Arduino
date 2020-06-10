int c_fmotor = 4;
int a_fmotor = 5;
int c_bmotor = 6;
int a_bmotor = 7;

float prevError_y = 0;
float prevError_p = 0;

unsigned long motor_current_time, finish_time, zero_timer;
int c_ftime, a_ftime, c_btime, a_btime = 100;
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
byte highByte, lowByte;
int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4;
int counter_channel_1, counter_channel_2, counter_channel_3, counter_channel_4, loop_counter;
unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_timer, esc_loop_timer;
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;
unsigned long loop_timer;
int throttle,roll_receiver,pitch_receiver,yaw_receiver;

void setup() {

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer

  DDRD |= B11110000; //Pins 4, 5, 6 and 7 are set to output DDRD - Data Direction Register The last D stands for port number
     
     //Arduino (Atmega) pins default to inputs, so they don't need to be explicitly declared as inputs
  PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan, 
     //PCICR - Pin Change Interupt Control Register
  PCMSK0 |= (1 << PCINT0);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
     //PCMSK - Pin Change MaSK Regsiter 0
  PCMSK0 |= (1 << PCINT2);  // set PCINT1 (digital input 10)to trigger an interrupt on state change
  PCMSK0 |= (1 << PCINT4);  // set PCINT2 (digital input 12)to trigger an interrupt on state change
  PCMSK0 |= (1 << PCINT5);  // set PCINT3 (digital input 13)to trigger an interrupt on state change

}

void loop() {
   roll_receiver=receiver_input_channel_1;
   pitch_receiver=receiver_input_channel_2;
   throttle=receiver_input_channel_3;
   yaw_receiver=receiver_input_channel_4;

   Serial.print(roll_receiver);
   Serial.print(" ");
   Serial.print(pitch_receiver);
   Serial.print(" ");
   Serial.print(yaw_receiver);
   Serial.print(" ");
   Serial.print(throttle);
   Serial.print("\n");

   pid_to_motor_time();
   move_motors();
}
void move_motors()
{
   motor_current_time = micros();
   PORTD |= B11110000; //Assign all motor ports to high
   unsigned long af = a_ftime + motor_current_time;
   unsigned long cf = c_ftime + motor_current_time;
   unsigned long ab = a_btime + motor_current_time;
   unsigned long cb = c_btime + motor_current_time;
   while(PORTD >= 16)
   {
      motor_current_time = micros();
      if(af > motor_current_time){PORTD &= B11111111;} //whichever motor a_fmotor refers to should be made 0 here
      if(cf > motor_current_time){PORTD &= B11111111;} //whichever motor a_fmotor refers to should be made 0 here
      if(ab > motor_current_time){PORTD &= B11111111;} //whichever motor a_fmotor refers to should be made 0 here
      if(cb > motor_current_time){PORTD &= B11111111;} //whichever motor a_fmotor refers to should be made 0 here
   }
}

ISR(PCINT0_vect){
  current_time = micros();
  //Channel 1=========================================
  if(PINB & B00000001){                                        //Is input 8 high?
    if(last_channel_1 == 0){                                   //Input 8 changed from 0 to 1
      last_channel_1 = 1;                                      //Remember current input state
      timer_1 = current_time;                                  //Set timer_1 to current_time
    }
  }
  else if(last_channel_1 == 1){                                //Input 8 is not high and changed from 1 to 0
    last_channel_1 = 0;                                        //Remember current input state
    receiver_input_channel_1 = current_time - timer_1;         //Channel 1 is current_time - timer_1
  }
  //Channel 2=========================================
  if(PINB & B00000100 ){                                       //Is input 10 high?
    if(last_channel_2 == 0){                                   //Input 10 changed from 0 to 1
      last_channel_2 = 1;                                      //Remember current input state
      timer_2 = current_time;                                  //Set timer_2 to current_time
    }
  }
  else if(last_channel_2 == 1){                                //Input 10 is not high and changed from 1 to 0
    last_channel_2 = 0;                                        //Remember current input state
    receiver_input_channel_2 = current_time - timer_2;         //Channel 2 is current_time - timer_2
  }
  //Channel 3=========================================
  if(PINB & B00010000 ){                                       //Is input 11 high?
    if(last_channel_3 == 0){                                   //Input 11 changed from 0 to 1
      last_channel_3 = 1;                                      //Remember current input state
      timer_3 = current_time;                                  //Set timer_3 to current_time
    }
  }
  else if(last_channel_3 == 1){                                //Input 11 is not high and changed from 1 to 0
    last_channel_3 = 0;                                        //Remember current input state
    receiver_input_channel_3 = current_time - timer_3;         //Channel 3 is current_time - timer_3

  }
  //Channel 4=========================================
  if(PINB & B00100000 ){                                       //Is input 12 high?
    if(last_channel_4 == 0){                                   //Input 12 changed from 0 to 1
      last_channel_4 = 1;                                      //Remember current input state
      timer_4 = current_time;                                  //Set timer_4 to current_time
    }
  }
  else if(last_channel_4 == 1){                                //Input 12 is not high and changed from 1 to 0
    last_channel_4 = 0;                                        //Remember current input state
    receiver_input_channel_4 = current_time - timer_4;         //Channel 4 is current_time - timer_4
  }
}

float yaw_pid(float e)
{
  float kp_y = 1;
  float ki_y = 1;
  float kd_y = 1;
  
  float prop_y = e * kp_y;
  
  float integral_y += (e * ki_y);
  float der_y = (e - prevError_y) * kd_y;
  
  float output = prop_y + integral_y + der_y;
  prevError_y = e;
  return output;
}
void pitch_pid(float e)
{
  float kp_p = 1;
  float ki_p = 1;
  float kd_p = 1;
  
  float prop_p = e * kp_p;
  
  float integral_p += (e * ki_p);
  float der_p = (e - prevError_p) * kd_p;
  
  float output = prop_p + integral_p + der_p;
  prevError_p = e;
  return output;
}
void roll_pid(float e)
{
  float kp_r = 1;
  float ki_r = 1;
  float kd_r = 1;
  
  float prop_r = e * kp_r;
  
  float integral_r += (e * ki_r);
  float der_r = (e - prevError_r) * kd_r;
  
  float output = prop_r + integral_r + der_r;
  prevError_r = e;
  return output;
}

void pid_to_motor_time()
{
  
}
