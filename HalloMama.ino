#include "lcd.h"
#include "datenbank.h"
#include "handy.h"
#include "tasten.h"
#include "nfc.h"

void setup() {          
    // Beispiel-Daten in die Datenbank hinzufügen
    db_addKeysCodeMessage("123", "017646677143", "Hallo1");
    db_addKeysCodeMessage("234", "017646677143", "Hallo2");
    db_addKeysCodeMessage("345", "017646677143", "Hallo3");
    db_addRFCodeMessage("191253445", "+4915236338238", "Hallo4");
    db_addRFCodeMessage("1292161812", "017646677143", "Hi was geht?");
    db_addRFCodeMessage("462428234115128", "+4915753078030", "Hi Elena!");

    // Serielle Kommunikation starten
    Serial.begin(9600);
    // Module initialisieren
    nfc_start();
    lcd_start();
    tasten_start();
    delay(1000);
}

void loop() {
    Serial.println("loop");

    String code; // Speichert den eingegebenen Code
    const int MaxTries = 25;  //Anzahl der Leseversuche für Tasten und RFID

    while (true) {
        // Tasteneingabe prüfen (PIN-Code)
        lcd_print(0, 0, "Pin code...");
        code = tasten_read(MaxTries);

        if (code.length() > 0) {
            int dbIndex = db_findKeys(code);
            code = ""; // Code zurücksetzen

            if (dbIndex != -1) {        
                lcd_print(0, 0, "Sende: " + db_message(dbIndex));
                lcd_print(0, 1, db_phone(dbIndex));
                handy_send(db_phone(dbIndex), db_message(dbIndex));
                delay(3000);
                break; 
            } else {
                lcd_print(0, 0, "Pincode Fehler!");
                delay(3000);
                break; 
            }
        }

        // RFID-Eingabe prüfen
        lcd_print(0, 0, "RFID...");
        code = nfc_read(MaxTries);

        if (code.length() > 0) {
            int dbIndex = db_findRf(code);

            if (dbIndex != -1) {
                lcd_print(0, 0, "Sende: " + db_message(dbIndex));
                lcd_print(0, 1, db_phone(dbIndex));
                handy_send(db_phone(dbIndex), db_message(dbIndex));
                delay(3000);
                break;     
            } else {
                lcd_print(0, 0, "Karte Fehler!");
                delay(3000);
                break;
            }
        }
    }
}
