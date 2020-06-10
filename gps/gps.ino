#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial ss(D4, D3);

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Virus2.0";
const char* password = "helpme1#";


void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
  ss.begin(9600);
}

void loop(){
  while (ss.available() > 0){
    // get the byte data from the GPS
    //Serial.println("HELlo World");
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
  Serial.println(ss.available());
}
