#pragma once
#include <Adafruit_PN532.h>

Adafruit_PN532 _pn532(2, 3 );


void nfc_start() {
  Serial.println("Start NFC...");
  _pn532.begin();

  uint32_t versiondata = _pn532.getFirmwareVersion();
  if (! versiondata) {
    Serial.println("ERROR: Didn't find PN53x board");
  }
  Serial.println("  NRF init OK");
}


String nfc_read(int nTries ) {
  for (int i=0; i< nTries;i++)
  {
    String result;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
    uint8_t uidLength;				// Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
    if (_pn532.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100)) 
    {
      for (uint8_t i=0; i < uidLength; i++)
      {
        result += uid[i];
      }
    }

    if ( result.length() > 0 )
    {
      return result;
    }    
  }
  return "";
}
