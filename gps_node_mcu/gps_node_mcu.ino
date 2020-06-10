#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(D4, D3); // The serial connection to the GPS device

const char* ssid = "vajmin0";
const char* password = "AJAYHARSHVARIKATMINUPAULOSE2011";

float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  // Print the IP address

}

void loop()
{

  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      //if (gps.location.isValid())
      //{
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      //}
      Serial.println("lat   " + lat_str);
      Serial.println("lng   " + lng_str);
    }

    
}
