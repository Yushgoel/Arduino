int pinEcho = 13;
int pinTrig = 12;
long duration = 0;
long distance = 0;

void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);

//pinMode(pinTrig, OUTPUT);
//pinMode(pinEcho, INPUT);
}

void loop() {
Serial.print("Distance = ");
  // put your main code here, to run repeatedly:
  //digitalWrite(pinTrig, LOW);
  //delayMicroseconds(500);
  
  //digitalWrite(pinTrig, HIGH);
  //delayMicroseconds(10);
  //duration = pulseIn(pinEcho, HIGH);
  //distance = duration/58.0;
  //Serial.print("Distance = ");
  //Serial.print(distance);
  //Serial.print("\n");
  //delayMicroseconds(100);
}
