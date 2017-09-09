
// constants won't change. They're used here to set pin numbers:
const int buttonPin2 = 2;    // lovato
const int buttonPin3 = 3;    // compri
const int buttonPin4 = 4;    // rebecca
const int buttonPin5 = 5;    // omoto

const int successLed = 13;      
const int loadingLed = 12;
const int failLed = 7;

int incomingByte = 0;

void setup() 
{
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);

 
  pinMode(successLed, OUTPUT);
  pinMode(loadingLed, OUTPUT);
  pinMode(failLed, OUTPUT);

  Serial.begin(9600);
  // set initial LED state
  digitalWrite(successLed, LOW);
}

void loop()
{
  // read the state of the switch into a local variable:
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);
  int reading4 = digitalRead(buttonPin4);
  int reading5 = digitalRead(buttonPin5);

  
  // We can create a function here to handle all the possible buttons (aka users)
  // we can also ser some constants for each person
  // send a signal to clock in
  if (reading2 == HIGH) 
  {
    digitalWrite(loadingLed, HIGH);
    Serial.println("lovato");
  }
  else if(reading3 == HIGH)
  {
    digitalWrite(loadingLed, HIGH);
    Serial.println("compri");
  }
  else if(reading4 == HIGH)
  {
    digitalWrite(loadingLed, HIGH);
    Serial.println("rebecca");
  }
  else if(reading5 == HIGH)
  {
    digitalWrite(loadingLed, HIGH);
    Serial.println("omoto");
  }

 
  // get the result from the last request
  // If the clocking in was performed correctly we light up the green led
  
    // Avoid too much serial reading, arduino is realy slow
  delay(500);
  incomingByte = Serial.parseInt();
  if(incomingByte == 1)
  {
    digitalWrite(loadingLed, LOW); 
    digitalWrite(successLed, HIGH);
    delay(2000);
    digitalWrite(successLed, LOW);
  }
  else if(incomingByte == 2)
  {
    digitalWrite(loadingLed, LOW);
    digitalWrite(failLed, HIGH);
    delay(2000);
    digitalWrite(failLed, LOW);  
  }
}


