int ledPin = 13;
int ledPinYellow = 12;
int ledPinGreen = 11;
void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  
}  

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(ledPin, HIGH);
   delay(10000);
   digitalWrite(ledPin, LOW);
   digitalWrite(ledPinGreen, HIGH);
   delay(8000);
   digitalWrite(ledPinGreen, LOW);
   digitalWrite(ledPinYellow, HIGH);
   delay(2000);// turn the LED on (HIGH is the voltage level)
   digitalWrite(ledPinYellow, LOW);
   digitalWrite(ledPin, HIGH);
   delay(10000);
   digitalWrite(ledPin, LOW);
   delay(1000);
  
}
