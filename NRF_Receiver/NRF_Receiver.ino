//#include <Servo.h>
#include <SPI.h>
#include "RF24.h"
//Servo myservo;
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 10//CE -> 8
RF24 radio(8, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int msg[1];
int analogOutPin = 9;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
void loop()
{
  if (radio.available())
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(msg, 1);
      Serial.println(msg[0]);
      // read the analog in value:
      //sensorValue = analogRead(msg[0]);
      // map it to the range of the analog out:
      //outputValue = map(sensorValue, 0, 1023, 0, 255);
      //Serial.println(outputValue);
      // change the analog out value:
      analogWrite(analogOutPin, msg[0]);
      delay(5);
    }
  }
}
