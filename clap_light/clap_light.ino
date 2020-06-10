int sound_sensor = A0;
int count=0;
int time_count = 0;
unsigned long clap_dist = 0;
int led = 13;
bool ledState = LOW;
bool first_time;

void setup() {
  // put your setup code here, to run once:
  first_time = true;
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  count = 0;
  time_count = 0;
  clap_dist = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  int decibels = analogRead(sound_sensor);
  Serial.println(decibels);
  //Serial.println(time_count);
  if(decibels >= 600)
  {
      time_count++;
  }
  if(time_count >= 20 && ((millis() - clap_dist) < 1000 || first_time))
  {
    count++;
    time_count=0;
    clap_dist=millis();
    first_time=false;
    Serial.println("clap");
    delay(150);
  }
  if((millis() - clap_dist) > 1000)
  {
    first_time = true;
    count = 0;
  }
  if(count >= 2)
  {
      count = 0;
      ledState = !ledState;
      digitalWrite(led, ledState);

     delay(100);
     first_time = true;
  }
  
  
  
}
