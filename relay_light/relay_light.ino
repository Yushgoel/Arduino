int bulb = 11;                 // the pin that the bulb is connected to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  pinMode(bulb, OUTPUT);      // initalize bulb as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);      // initialize serial
}

void loop(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(bulb, 1); 
    Serial.println("Motion detected!");// turn bulb ON
    delay(10000);                // delay 100 milliseconds 
    
  }
  else {
      digitalWrite(bulb, 0); // turn Bulb OFF
      delay(100);             // delay 200 milliseconds 
      Serial.println("Motion stopped!");

  }
}
