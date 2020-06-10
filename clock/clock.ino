#include "Wire.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
//#include "RTClib.h"


#define CLK 5
#define DIO 4
Adafruit_7segment disp = Adafruit_7segment();

void setup() {
  // put your setup code here, to run once:
  disp.begin(0x70);
}

void loop() {
  // put your main code here, to run repeatedly:
  disp.print(82.123,0);
 
  
  delay(500);
}
