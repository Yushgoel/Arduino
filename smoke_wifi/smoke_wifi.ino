#include <SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial esp8266(RX,TX);
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
char O_K[] = {'O', 'K'}; 

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,O_K);
  sendCommand("AT",5,O_K);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  
  esp8266.println(command);//at+cipsend
      //Serial.println(esp8266);
  delay(2000);
  
  char data = esp8266.read();
  Serial.print(data);
           
  if (esp8266.available()) {
    Serial.write(esp8266.read());
  }

/*
  
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    //Serial.println(esp8266);

    if (esp8266.available()) {
      Serial.write(esp8266.read());
    }

  }*/
}

/*
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }*/
