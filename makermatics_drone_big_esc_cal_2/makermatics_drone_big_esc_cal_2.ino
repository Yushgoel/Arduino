//Declaring global variables
byte last_channel_3;

volatile int  receiver_input_channel_3;
int esc_1;
int counter_channel_3;
int receiver_input[5];
unsigned long  timer_channel_3, esc_timer, esc_loop_timer;
unsigned long timer_channel_1, timer_channel_2, timer_channel_4;
unsigned long zero_timer, timer_3, current_time;
int dist;//actual distance measurements of LiDAR
int strength;//signal strength of LiDAR
int i;
int uart[9];//save data measured by LiDAR
//Setup routine
void setup(){
  Serial.begin(115200);                                                                  //Start the serial port.
  
  //Arduino Uno pins default to inputs, so they don't need to be explicitly declared as inputs.
  DDRD |= B11110000;                                                                    //Configure digital poort 4, 5, 6 and 7 as output.
  
  PCICR |= (1 << PCIE0);                                                                // set PCIE0 to enable PCMSK0 scan.
  PCMSK0 |= (1 << PCINT4);                                                              // set PCINT2 (digital input 10)to trigger an interrupt on state change.
  
  zero_timer = micros();                                                                //Set the zero_timer for the first loop.
}

//Main program loop
void loop(){

  /*
  if (Serial.available()>0)//check if serial port has data input
      { 
       for(i=0;i<9;i++)//save data in array
            {
              uart[i]=Serial.read();
              dist=(uart[2]+(uart[3]*256));
              Serial.print(" ");
             }
        }
     if(dist >=0 && dist <= 500){
     Serial.println(dist);
     }

  */   
    while(zero_timer + 4000 > micros());                                                  //Start the pulse after 4000 micro seconds.
    zero_timer = micros();                                                                //Reset the zero timer.
    
    //Serial.println("Testing motor");
    delay(3);                                                                             //Wait 3000us.
    receiver_input_channel_3 = convert_receiver_channel(3);                               //Convert the actual receiver signals for throttle to the standard 1000 - 2000us.
    esc_1 = receiver_input_channel_3+dist;                                                     //Set the pulse for motor 1 equal to the throttle channel.
    //Serial.println(esc_1);
    esc_pulse_output();                                                                   //Send the ESC control pulses.
    
}
 
ISR(PCINT0_vect){
  current_time = micros();
  //Channel 3=========================================
  if(PINB & B00010000 ){                                       //Is input 10 high?
    if(last_channel_3 == 0){                                   //Input 10 changed from 0 to 1.
      last_channel_3 = 1;                                      //Remember current input state.
      timer_3 = current_time;                                  //Set timer_3 to current_time.
    }
  }
  else if(last_channel_3 == 1){                                //Input 10 is not high and changed from 1 to 0.
    last_channel_3 = 0;                                        //Remember current input state.
    receiver_input[3] = current_time - timer_3;                //Channel 3 is current_time - timer_3.
  }
  
}


int convert_receiver_channel(byte function){
  byte channel, reverse;                                                       //First we declare some local variables
  int low, center, high, actual;
  int difference;

  channel = 3;                                                                 //What channel corresponds with the specific function
 
  actual = receiver_input[channel];                                            //Read the actual receiver value for the corresponding function
  
  low = 1000;  //Store the low value for the specific receiver input channel
  center = 1500 ; //Store the center value for the specific receiver input channel
  high = 2000;   //Store the high value for the specific receiver input channel

  if(actual < center){                                                         //The actual receiver value is lower than the center value
    if(actual < low)actual = low;                                              //Limit the lowest value to the value that was detected during setup
    difference = ((long)(center - actual) * (long)500) / (center - low);       //Calculate and scale the actual value to a 1000 - 2000us value
    return 1500 - difference;                                             //If the channel is not reversed
  }
  else if(actual > center){                                                                        //The actual receiver value is higher than the center value
    if(actual > high)actual = high;                                            //Limit the lowest value to the value that was detected during setup
    difference = ((long)(actual - center) * (long)500) / (high - center);      //Calculate and scale the actual value to a 1000 - 2000us value
    return 1500 + difference;                                             //If the channel is not reversed
  }
  else return 1500;
}

void esc_pulse_output(){
  zero_timer = micros();
  PORTD |= B00010000;                                            //Set port 4 high 
  timer_channel_3 = esc_1 + zero_timer;                          //Calculate the time when digital port 4 is set low.
  timer_channel_1 = esc_1 + zero_timer;                          //Calculate the time when digital port 4 is set low.
  timer_channel_2 = esc_1 + zero_timer;                          //Calculate the time when digital port 4 is set low.
  timer_channel_4 = esc_1 + zero_timer;                          //Calculate the time when digital port 4 is set low.

  while(PORTD >= 16){                                            //Execute the loop until digital port 4 
    esc_loop_timer = micros();                                   //Check the current time.
    if(timer_channel_3 <= esc_loop_timer)PORTD &= B11101111;
    if(timer_channel_1 <= esc_loop_timer)PORTD &= B11011111;
    if(timer_channel_2 <= esc_loop_timer)PORTD &= B10111111;
    if(timer_channel_4 <= esc_loop_timer)PORTD &= B01111111;//When the delay time is expired, digital port 4 is set low.
  }
}
