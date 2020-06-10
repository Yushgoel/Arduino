int smoke = A2;

void setup() {
  // put your setup code here, to run once:
   pinMode(smoke, INPUT); 
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   int analogSensor = analogRead(smoke);
   Serial.print("Smoke value - ");
   Serial.println(analogSensor);
   delay(1000);
}
