float val;
int tempPin = 0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(tempPin);
  float mv = ( val*500/1023);
  
  Serial.print("VAL = ");
  Serial.print(val);
  Serial.print("temp = ");
  Serial.println(mv);
  delay(1000);

}
