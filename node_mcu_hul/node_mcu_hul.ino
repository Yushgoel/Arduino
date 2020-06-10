#include <TM1637Display.h>
const int CLK = D2; //Set the CLK pin connection to the display
const int DIO = D3; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO); //set up the 4-Digit Display.

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Virus2.0";
const char* password = "helpme1#";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
  display.setBrightness(0xff);
  display.showNumberDec(1234,false,4,0);//Print the response payload

  delay(1000);
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    //Serial.println("Entered loop if condition");
    http.begin("http://hulnodemcu.appspot.com/b1");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);
      //Serial.println("hello");       
      display.showNumberDec(payload.toInt(),false,4,0);//Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(30000);    //Send a request every 30 seconds
 
}
