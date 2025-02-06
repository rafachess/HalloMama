#include <Adafruit_PN532.h>

Adafruit_PN532 *pn532 = 0;

class NFC
{
  
  public:
  NFC( int sda, int scl )
  {
    delete pn532;
    pn532 = new Adafruit_PN532 (sda, scl);
  }

  void start() {
    Serial.println("Start NFC...");
    pn532->begin();

    uint32_t versiondata = pn532->getFirmwareVersion();
    if (! versiondata) {
      Serial.println("Didn't find PN53x board. Full stop.");
      while (1); // halt
    }
    Serial.println("  NRF init OK");
  }

  String read(void) {
    //Serial.println(" lese_RFID");
    String result;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
    uint8_t uidLength;				// Length of the UID (4 or 7 bytes depending on ISO14443A card type)

    if (pn532->readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100)) {
      for (uint8_t i=0; i < uidLength; i++)
      {
        result += uid[i];
      }
    }
    return result;
  }

};