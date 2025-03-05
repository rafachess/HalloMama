#include "lcd.h"
#include "datenbank.h"
#include "handy.h"
#include "tasten.h"
#include "nfc.h"

Datenbank db;
Handy handy;
Tasten keys;
NFC nfc(2,3);

const int PIN_IRQ_KEYS = 2;
const int PIN_IRQ_NFC = 3;




void setup() {
            
  db.addKeysCodeMessage("123","017646677143","Hallo1");
  db.addKeysCodeMessage("234","017646677143", "Hallo2");
  db.addKeysCodeMessage("345","017646677143", "Hallo3");
  db.addRFCodeMessage("191253445","+4915236338238", "Hallo4");
  db.addRFCodeMessage("1292161812","017646677143", "Hi was geht?");
  db.addRFCodeMessage("462428234115128","+4915753078030", "Hi Elena!");

  Serial.begin(9600);
  delay(500);  
  nfc.start();
  handy.start();
  LCD::inst().start();
  keys.start();
  delay(1000);
  pinMode( PIN_IRQ_KEYS, INPUT_PULLUP );
  pinMode( PIN_IRQ_NFC, INPUT_PULLUP );
}

//******* das ist die Haupt-Schleife
void loop() {
  Serial.println("loop");
  for (;;)
  {
    Serial.print( digitalRead( PIN_IRQ_KEYS ) );
    Serial.print( " " );
    Serial.println( digitalRead( PIN_IRQ_NFC ) );
    
    keys.start();
    String code = keys.read();
    if (code.length() > 0  )
    {
      int dbIndex = db.findKeys( code );
      code="";
      if ( dbIndex != -1 )
      {        
        auto el = db.element(dbIndex);
        LCD::inst().print(0,0,"Sende:" + el.message );
        LCD::inst().print(0,1, el.tel1 );
        handy.send(el.tel1, el.message);
        delay(3000);
        continue; 
      }
      else
      {
        LCD::inst().print(0,0,"Pincode Fehler!" );
        delay(3000);
      }
    }

    code = nfc.read();
    if (code.length() > 0  )
    {
      int dbIndex = db.findRf( code );
      if ( dbIndex!=-1 )
      {
        auto el = db.element(dbIndex);
        LCD::inst().print(0,0,"Sende:" + el.message );
        LCD::inst().print(0,1, el.tel1 );
        handy.send(el.tel1, el.message);
        delay(3000);
        continue;     
      }
      else
      {
        LCD::inst().print(0,0,"Karte fehler!" );
        delay(3000);
      }
    }
  }
}

/*
void nachricht_senden( String tel, String nachricht )
{
   handy.send(tel, nachricht);
   lcd.clear(); 
   lcd.setPosition(0, 0);
   //Serial.println("Nachricht wird");
   lcd.setPosition(0, 1);
   //Serial.println("gesendet...");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
   //Serial.println("erfolgreich(-:");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
}
*/
