#pragma once  // Verhindert, dass diese Datei mehrmals geladen wird

#include <LiquidCrystal_I2C.h> // Bibliothek für das LCD-Display

// Erstelle ein LCD-Display-Objekt mit I2C-Adresse 0x27 und 16x2 Zeichen
LiquidCrystal_I2C _lcd(0x27, 16, 2);

/////////////////////////////////////////////
// Funktion: lcd_start
// Initialisiert das LCD-Display, schaltet das 
// Hintergrundlicht ein und zeigt Begrüßungstexte an.
// Nach einigen Sekunden wird das Display gelöscht.
/////////////////////////////////////////////
void lcd_start() {
  _lcd.init();   // Initialisiert das LCD
  _lcd.clear();  // Löscht das Display
  _lcd.backlight(); // Schaltet die Hintergrundbeleuchtung ein
  delay(100); // Kurze Pause, um sicherzustellen, dass das LCD bereit ist

  // Zeigt die erste Nachricht an
  _lcd.setCursor(0, 0);
  _lcd.print("Projekt");  // Erste Zeile: "Projekt"
  _lcd.setCursor(0, 1);
  _lcd.print("Hallo Mama"); // Zweite Zeile: "Hallo Mama"
  delay(2000); // 2 Sekunden warten

  // Löscht das Display und zeigt eine neue Nachricht
  _lcd.clear();
  delay(100);
  _lcd.setCursor(0, 0);
  _lcd.print("Jugend Forscht"); // Erste Zeile: "Jugend Forscht"
  _lcd.setCursor(0, 1);
  _lcd.print("2025"); // Zweite Zeile: "2025"
  delay(3000); // 3 Sekunden warten

  // Löscht das Display abschließend
  _lcd.clear();
}

/////////////////////////////////////////////
// Funktion: lcd_clear
// Löscht den gesamten Inhalt des Displays.
/////////////////////////////////////////////
void lcd_clear()
{
  _lcd.clear();
}

/////////////////////////////////////////////
// Funktion: lcd_setPosition
// Setzt den Cursor auf eine bestimmte Position 
// im Display, damit der nächste Text dort erscheint.
//
// Parameter:
//  - r: Zeile (0 oder 1, weil das Display 2 Zeilen hat)
//  - c: Spalte (0 bis 15, weil das Display 16 Zeichen pro Zeile hat)
/////////////////////////////////////////////
void lcd_setPosition(int r, int c)
{
  _lcd.setCursor(r, c);
}

/////////////////////////////////////////////
// Funktion: lcd_print (String-Version)
// Gibt eine Zeichenkette (Text) auf dem LCD aus.
//
// Parameter:
//  - str: Die Zeichenkette, die auf dem LCD angezeigt wird.
/////////////////////////////////////////////
void lcd_print(String str)
{
  _lcd.print(str.c_str());
}

/////////////////////////////////////////////
// Funktion: lcd_print (Integer-Version)
// Gibt eine Zahl als Text auf dem LCD aus.
//
// Parameter:
//  - v: Die Zahl, die angezeigt werden soll.
/////////////////////////////////////////////
void lcd_print(int v)
{
  _lcd.print(String(v).c_str());
}

/////////////////////////////////////////////
// Funktion: lcd_print (Char-Version)
// Gibt ein einzelnes Zeichen auf dem LCD aus.
//
// Parameter:
//  - v: Das Zeichen, das angezeigt werden soll.
/////////////////////////////////////////////
void lcd_print(char v)
{
  _lcd.print(v);
}

/////////////////////////////////////////////
// Funktion: lcd_print (Positionierte Version)
// Gibt einen Text an einer bestimmten Position aus.
// Falls die Position (0,0) ist, wird das Display vorher gelöscht.
//
// Parameter:
//  - r: Zeile (0 oder 1, weil das Display 2 Zeilen hat)
//  - c: Spalte (0 bis 15, weil das Display 16 Zeichen pro Zeile hat)
//  - str: Der Text, der an dieser Position angezeigt werden soll.
/////////////////////////////////////////////
void lcd_print(int r, int c, String str)
{
  if (r == 0 && c == 0)
    _lcd.clear(); // Wenn der Text ganz links oben beginnt, wird das Display geleert

  _lcd.setCursor(r, c); // Setzt den Cursor an die gewünschte Position
  _lcd.print(str.c_str()); // Gibt den Text aus
}
