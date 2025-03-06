#include "lcd.h"
#include "datenbank.h"
#include "handy.h"
#include "tasten.h"
#include "nfc.h"


void setup() {          
  db_addKeysCodeMessage("123","017646677143","Hallo1");
  db_addKeysCodeMessage("234","017646677143", "Hallo2");
  db_addKeysCodeMessage("345","017646677143", "Hallo3");
  db_addRFCodeMessage("191253445","+4915236338238", "Hallo4");
  db_addRFCodeMessage("1292161812","017646677143", "Hi was geht?");
  db_addRFCodeMessage("462428234115128","+4915753078030", "Hi Elena!");

  Serial.begin(9600);
  delay(500);  
  nfc_start();
  lcd_start();
  tasten_start();
  Wire.setClock(100000);
  delay(1000);
}

//******* das ist die Haupt-Schleife
void loop() {
  Serial.println("loop");
  int inputMode=1;
  int cnt=0;
  String code;
  for (;;)
  {

    lcd_print(0,0,"Pin code..." );
    
    code = tasten_read(25);
    if (code.length() > 0  )
    {
      int dbIndex = db_findKeys( code );
      code="";
      if ( dbIndex != -1 )
      {        
        lcd_print(0,0,"Sende:" + db_message(dbIndex) );
        lcd_print(0,1, db_phone(dbIndex) );
        handy_send( db_phone(dbIndex), db_message(dbIndex));
        delay(3000);
        break; 
      }
      else
      {
        lcd_print(0,0,"Pincode Fehler!" );
        delay(3000);
        break; 
      }
    }
     

    lcd_print(0,0,"RFID..." );
      
    String code = nfc_read(25);
    if (code.length() > 0  )
    {
      int dbIndex = db_findRf( code );
      if ( dbIndex!=-1 )
      {
        lcd_print(0,0,"Sende:" + db_message(dbIndex) );
        lcd_print(0,1, db_phone(dbIndex) );
        handy_send( db_phone(dbIndex), db_message(dbIndex));
        delay(3000);
        break;     
      }
      else
      {
        lcd_print(0,0,"Karte fehler!" );
        delay(3000);
        break;
      }
    }
  }
}
