
int sentence = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sentence = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  Serial.println(value);
  if(value < 100)
  {
    speak(sentence);
    sentence++;
  }
  //delay(15000);
}
void speak(int num)
{
  if(num == 0)
  {
    Serial.println("Hello, how are you?");  
  }
  
  else if(num == 1)
  {
    Serial.println("Okay setting the reminder.");  
  }
  
  else if(num == 2)
  {
    Serial.println("You have one reminder to do homework at 7:30 pm");  
  }
  
  else if(num == 3)
  {
    Serial.println("Goodbye");
  }
}
