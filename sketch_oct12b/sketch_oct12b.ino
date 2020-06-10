#include <Arduino.h>
#include <TM1637Display.h>
#include <Wire.h>
#include "RTClib.h"

#define CLK 5
#define DIO 4
#define buzzerPin 3
#define buttonPin 2 
#define motorpin 12


RTC_DS1307 RTC;

bool alarm_rang = false;
bool ring = false;
int buttonState = 0;
int current_time;

TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); //This needs to be done only once to set the rtc module

  pinMode(buzzerPin, OUTPUT); //Set buzzerPin as output  
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = RTC.now();
  current_time = now.hour() * 100 + now.minute();
  
  if (current_time == 1721 && alarm_rang == false)
  {
      ring = true;
      

    
  }
  buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {
      // turn LED on:
        ring = false;
        digitalWrite(12, LOW);
        alarm_rang = true;
    }
  if(ring)
  {
    beep(75);
    digitalWrite(12, HIGH);
  }
  
  display.setBrightness(0x0f);
  display.showNumberDecEx(current_time, 0b11100000, true, 4, 0);
}

void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 255); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
}
