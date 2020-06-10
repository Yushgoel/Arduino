int redled = 8;
int yellowled = 9;
int greenled = 10;
void setup() {
  // put your setup code here, to run once:
pinMode(redled, OUTPUT);
pinMode(yellowled, OUTPUT);
pinMode(greenled, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(redled, HIGH);
delay(200);
digitalWrite(redled, LOW);
digitalWrite(yellowled, HIGH);
delay(200);
digitalWrite(yellowled, LOW);
digitalWrite(greenled, HIGH);
delay(200);
digitalWrite(redled, LOW);
delay(200);
}
