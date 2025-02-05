#include <Bonezegei_LCD1602_I2C.h>
#include <Adafruit_PN532.h>
#include <SoftwareSerial.h>

#include "datenbank.h"
#include "handy.h"
#include "tasten.h"



// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Or use this line for a breakout or shield with an I2C connection:
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

Bonezegei_LCD1602_I2C lcd(0x27);

Datenbank db;
Handy handy;
Tasten keys;


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

void initNRF() {
  Serial.println("initNRF...");
  nfc.begin();
  Serial.println("  NRF start...");

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1); // halt
  }
  //nfc.setPassiveActivationRetries(0xFF);  
  Serial.println("  NRF init OK");
}


void setup() {
            
  db.addKeysCodeMessage("123","017646677143","Hallo");
  db.addKeysCodeMessage("234","014675969977", "Hallo");
  db.addKeysCodeMessage("345","0162436295759", "Hallo");

  Serial.begin(9600);
  delay(500);
  Serial.println("Start");
  
  keys.start();
  initLCD();

  initNRF(); 
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
      int dbIndex = db.durchsuchenKeys( code );
    }
    //code = lese_RFID();
    if (code.length() > 0  )
    {
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
   /*!*/ Serial.println("Nachricht wird");
   lcd.setPosition(0, 1);
   /*!*/ Serial.println("gesendet...");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
   /*!*/ Serial.println("erfolgreich(-:");
   delay(2000);
   lcd.clear();
   lcd.setPosition(0, 0);
}


String lese_RFID(void) {
  Serial.println(" lese_RFID");
  String result;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
  uint8_t uidLength;				// Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100)) {
    //Serial.println("Found a card!");
    //Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    //Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++)
    {
      result += uid[i];
      //Serial.print(" 0x");Serial.print(uid[i], HEX);
    }
	// Wait 1 second before continuing
	//delay(1000);
  }
  return result;
}
