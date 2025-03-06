#pragma once  // Verhindert, dass diese Datei mehrmals geladen wird

#include "Adafruit_MPR121.h"
#include "lcd.h"

//Makro zum Auswerten einzelner Bits. Die Tasten in Tastaturmorul sind alle als einzelne Bits kodiert.
//So dass man mehrere Tasten auf einmal drücken kann.
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif


// Erstellt ein Objekt für den kapazitiven Tasten-Sensor
Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;   // Speichert die vorherige Berührung
uint16_t currtouched = 0;   // Speichert die aktuelle Berührung
String tastencode = "";     // Speichert den eingegebenen Tasten-Code


/////////////////////////////////////////////
// Funktion: tasten_decodeKey
// Konvertiert die gedrückte Taste in das entsprechende Zeichen.
//
// Parameter:
//  - k: Nummer der gedrückten Taste (0-11)
//
// Rückgabe:
//  - char: Das Zeichen, das der Taste entspricht.
/////////////////////////////////////////////
char tasten_decodeKey(uint8_t k) {
    switch (k) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '#';
        case 5: return '4';
        case 6: return '5';
        case 7: return '6';
        case 8: return '*';
        case 9: return '7';
        case 10: return '8';
        case 11: return '9';
        default: return ' '; // Falls keine gültige Taste erkannt wurde
    }
}


/////////////////////////////////////////////
// Funktion: tasten_start
// Initialisiert den kapazitiven Tasten-Sensor MPR121.
// Falls der Sensor nicht gefunden wird, bleibt das Programm hängen.
/////////////////////////////////////////////
void tasten_start() {
    if (!cap.begin(0x5A)) {
        Serial.println("MPR121 nicht gefunden, Programm gestoppt!");
        while (1); // Endlosschleife, falls kein Sensor gefunden wird
    }
}

/////////////////////////////////////////////
// Funktion: tasten_read
// Liest Tasteneingaben vom kapazitiven Sensor aus und gibt 
// den eingegebenen Code als Zeichenkette zurück.
//
// Rückgabe:
//  - String: Enthält den gedrückten Tastencode.
/////////////////////////////////////////////
String tasten_read(int nTries ) {
  tasten_start();
  
  for (int i=0; i< nTries;i++)
  {
    tastencode = ""; // Löscht den gespeicherten Code
    lcd_print(0, 1, "               "); // Löscht die untere Zeile des Displays
    lcd_setPosition(0, 1);

    unsigned long letzte_taste_zeit = 0;  // Speichert die Zeit der letzten Tasteneingabe
    const unsigned long zeit_pro_taste = 2000; // Timeout für Eingabe (2 Sekunden)
    int cnt = 0; // Zähler für die Wartezeit

    while (true) {
        currtouched = cap.touched(); // Liest den aktuellen Berührungsstatus
        Serial.print(currtouched);
        Serial.println(" currtouched");

        for (uint8_t i = 0; i < 12; i++) {
            // Falls Taste gedrückt wurde und vorher nicht gedrückt war
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
                Serial.print(i);
                Serial.println(" touched");
            }
            // Falls Taste losgelassen wurde
            if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
                char k = tasten_decodeKey(i); // Konvertiert den Tastencode in eine Ziffer oder ein Zeichen
                tastencode += k; // Hängt die Taste an den Code an

                Serial.print(i);
                Serial.println(" released");
                lcd_print(String(k)); // Zeigt die gedrückte Taste auf dem Display an
                letzte_taste_zeit = millis(); // Speichert die Zeit des letzten Tastendrucks
                break;
            }
        }

        // Aktualisiert den Status für die nächste Schleife
        lasttouched = currtouched;

        // Falls bereits eine Eingabe gemacht wurde, aber zu lange keine weitere kam -> zurückgeben
        if (tastencode.length() > 0) {
            if (millis() - letzte_taste_zeit > zeit_pro_taste) {
                return tastencode; 
            }
        } else {
            // Falls keine Taste gedrückt wurde und mehrmals gewartet wurde -> Abbruch
            if (cnt++ > 5) {
                break;
            }
        }
        delay(10); // Kleine Verzögerung zur Stabilisierung
    }

    delay(100);
  }
  return "";
}
