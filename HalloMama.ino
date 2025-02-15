#include <Bonezegei_LCD1602_I2C.h>
#include "datenbank.h"
#include "handy.h"
#include "tasten.h"
#include "nfc.h"



Bonezegei_LCD1602_I2C lcd(0x27);

Datenbank db;
Handy handy;
Tasten keys;
NFC nfc(2,3);


void initLCD() {
  lcd.begin();
  lcd.print("Hallo");
  delay(200);
  lcd.clear(); 
  lcd.setPosition(0, 0);      //param1 = X   param2 = Y
  lcd.print("Schoen dass Sie");
  lcd.setPosition(0, 1);      //param1 = X   param2 = Y 
  lcd.print(" da sind");
  delay(200);
  lcd.clear(); 
  lcd.setPosition(0, 0);
  lcd.print("Projekt:");
  lcd.setPosition(0, 1);
  lcd.print("Hallo Mama");
  delay(1000);
  lcd.clear();
  delay(1000);
}




void setup() {
            
  db.addKeysCodeMessage("123","017646677143","Hallo");
  db.addKeysCodeMessage("234","014675969977", "Hallo");
  db.addKeysCodeMessage("345","0162436295759", "Hallo");

  Serial.begin(9600);
  delay(500);
  Serial.println("Start");
  
  keys.start();
  nfc.start();
  initLCD();
  delay(1000);
  
}

//******* das ist die haupt Schleife
void loop() {
  Serial.println("loop");
  for (;;)
  {
   
    String code = keys.read();
    if (code.length() > 0  )
    {
      Serial.print("Keys: ");
      Serial.println(code.c_str());
      int dbIndex = db.durchsuchenKeys( code );
    }
    code="";
    //code = nfc.read();
    if (code.length() > 0  )
    {
      Serial.print("NFC: ");
      Serial.println(code.c_str());
      int dbIndex = db.durchsuchenRf( code );
    }
    //  nachricht_senden(el.tel1, el.message);
  }
}


void nachricht_senden( String tel, String nachricht )
{
   handy.send(tel, nachricht);
   lcd.clear(); 
   lcd.setPosition(0, 0);
   Serial.println("Nachricht wird");
   lcd.setPosition(0, 1);
   Serial.println("gesendet...");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
   Serial.println("erfolgreich(-:");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
}


