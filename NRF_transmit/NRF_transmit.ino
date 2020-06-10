#include <SPI.h>
#include "RF24.h"
int msg[4]; 
RF24 radio(8,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
// this constant won't change:
const int  buttonPin1 = 2;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 3;    // the pin that the pushbutton is attached to
const int  buttonPin3 = 5;
const int  buttonPin4 = 4;
const int  buttonPin5 = 7;
const int  buttonPin6 = 6;

int Count1 = 0,Count2 = 0,Count3= 0;   // counter for the number of button presses
int buttonState1 = 0;  
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;



int lastButtonState1 = 0;// previous state of the button
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;
int lastButtonState5 = 0;
int lastButtonState6 = 0;

int potpin0 = 0;
int potpin1 = 1;
int potpin2 = 2;
int potpin3 = 3;
int val0,val1,val2,val3;

void setup(void)
{

Serial.begin(115200);  
radio.begin();
radio.openWritingPipe(pipe);


// initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  
}

void loop(void)
{
// read the pushbutton input pin:
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
buttonState4 = digitalRead(buttonPin4);
buttonState5 = digitalRead(buttonPin5);
buttonState6 = digitalRead(buttonPin6);

val0 = analogRead(potpin0);
val1 = analogRead(potpin1);
val2 = analogRead(potpin2);
val3 = analogRead(potpin3);

msg[0]= map(val0, 0, 1023, 0, 255);
msg[1]= map(val1, 0, 1023, 0, 255);
msg[2]= map(val2, 0, 1023, 0, 255);
msg[3]= map(val3, 0, 1023, 0, 255);
/*
msg[1]= msg[1]-127+ Count1;
msg[2]= msg[2]-127+ Count2;
msg[3]= msg[3]-127+ Count3;*/


Serial.print(msg[0]);
Serial.print("\t");
Serial.print(msg[1]);
Serial.print("\t");
Serial.print(msg[2]);
Serial.print("\t");
Serial.println(msg[3]);

 
//printing count values 
 //Serial.print("pitch correction= ");
 //Serial.print(Count1);
 //Serial.print("   ");
 //Serial.print("roll correction= ");
 //Serial.print(Count2);
 //Serial.print("   ");
 //Serial.print("yaw correction= ");
 //Serial.println(Count3);
   

  // compare the buttonState to its previous state
  if (buttonState1 != lastButtonState1 || buttonState2 != lastButtonState2 || buttonState3 != lastButtonState3 || buttonState4 != lastButtonState4 || buttonState5 != lastButtonState5 || buttonState6 != lastButtonState6) {
      // if the state has changed, increment the counter
      if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          Count1++;
          //Serial.println("button1 pressed");
          //Serial.println(Count1);
         }
      if (buttonState2 == HIGH) {
        
          Count1--;
          //Serial.println("button2 pressed");
          //Serial.println(Count1);
          
         }
          
    if (buttonState3 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          Count2++;
          //Serial.println("button3 pressed");
          //Serial.println(Count2);
         }
      if (buttonState4 == HIGH) {
        
          Count2--;
          //Serial.println("button4 pressed");
          //Serial.println(Count2);
          
         }
        if (buttonState5 == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          Count3++;
          //Serial.println("button5 pressed");
          //Serial.println(Count3);
         }
      if (buttonState6 == HIGH) {
        
          Count3--;
          //Serial.println("button6 pressed");
          //Serial.println(Count3);
          
         }
            
      } 
      
    
    // Delay a little bit to avoid bouncing
    delay(5);
  
  // save the current state as the last state, for next time through the loop
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
  lastButtonState4 = buttonState4;
  lastButtonState5 = buttonState5;
  lastButtonState6 = buttonState6;


radio.write(&msg, sizeof(msg));
delay(5);
}
