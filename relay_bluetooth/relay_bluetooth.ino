#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  BT.begin(9600);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  if(BT.available())
  {
    char a = BT.read();
    Serial.println(a);
    if(a == '1')
    {
      digitalWrite(2, HIGH);
    }
    else if(a == '0')
    {
      digitalWrite(2, LOW);
    }
    
  }
}
