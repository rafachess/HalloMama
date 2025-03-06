#pragma once
#include <Adafruit_PN532.h>



class NFC
{
  Adafruit_PN532 *pn532 = 0;
  int _sda;
  int _scl;
  
  public:
  NFC( int sda, int scl ):_sda(sda),_scl(scl)
  {
    
  }

  void start() {
    Serial.println("Start NFC...");
    delete pn532;
    pn532 = new Adafruit_PN532 (_sda, _scl);
    pn532->begin();

    uint32_t versiondata = pn532->getFirmwareVersion();
    if (! versiondata) {
      Serial.println("ERROR: Didn't find PN53x board");
      delete pn532;
      pn532 = nullptr;
      //while (1); // halt
    }
    Serial.println("  NRF init OK");
  }

  void stop() {
    Serial.println("Sop NFC...");

    //if (pn532) pn532->stop();
    delete pn532;
    pn532 = 0;
   
    Serial.println("  NRF off");
  }

  String read(void) {
    //Serial.println(" lese_RFID");+49
    String result;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
    uint8_t uidLength;				// Length of the UID (4 or 7 bytes depending on ISO14443A card type)

    if ( pn532 )
    {
      if (pn532->readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100)) {
        for (uint8_t i=0; i < uidLength; i++)
        {
          result += uid[i];
        }
      }
    }
    return result;
  }

};
