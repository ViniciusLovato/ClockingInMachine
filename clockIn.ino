
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 

char st[20];

int incomingByte = 0;


void setup() 
{
  pinMode(8,OUTPUT); // buzzer pin
  Serial.begin(9600); // Initialize Serial port comm
  SPI.begin();    // Initialize SPI bus
  mfrc522.PCD_Init(); //  MFRC522 (RFID reader)

  // Define number of rows and columns
  lcd.begin(16, 2);  
  lcd.print("Aproxime seu");
  lcd.setCursor(0,1);
  lcd.print("cartao");
}

void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "6A 31 0F BB") // lovato card
  {
    tone(8,300,300); //MI
    delay(500);
    tone(8,300,300); //MI
    Serial.println("lovato");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tentativa para");
    lcd.setCursor(0,1);
    lcd.print("Lovato");
    delay(3000);
    lcd.clear();
  
    incomingByte = Serial.parseInt();
    if(incomingByte == 1)
    {
     
      tone(8,300,300); 
      lcd.print("Ponto registrado");
      
    }
    else if(incomingByte == 2)
    {
      lcd.print("Erro no registro");
    }
    delay(3000);
  }
  else 
  {
    tone(8,262,200); 
    lcd.clear();
    lcd.print("Cartao");
    lcd.setCursor(0,1);
    lcd.print("invalido");
    delay(3000);
    
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aproxime seu");
  lcd.setCursor(0,1);
  lcd.print("cartao");
  delay(500);
} 


