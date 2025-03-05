#pragma once

#include <LiquidCrystal_I2C.h>


class LCD
{
  LiquidCrystal_I2C * lcd=0;
  LCD()
  {
    lcd = new LiquidCrystal_I2C(0x27,16,2);
  }

public:

  static LCD & inst()
  {
    static LCD _lcd;
    return _lcd;
  }

  void start() {
    lcd->init();
    lcd->clear();
    lcd->backlight();
    delay(100);
    lcd->setCursor(0, 0);
    lcd->print("Projekt");
    lcd->setCursor(0, 1);
    lcd->print("Hallo Mama");
    delay(2000);
    lcd->clear();
    delay(100);
    lcd->setCursor(0, 0);
    lcd->print("Jugend Forscht");
    lcd->setCursor(0, 1);
    lcd->print("2025");
    delay(3000);
    lcd->clear();
  }

  void clear()
  {
    lcd->clear();
  }

  void setPosition( int r, int c)
  {
    lcd->setCursor( r,c );
  }

  void print( String str )
  {
    lcd->print( str.c_str() );
  }

  void print( int v )
  {
    lcd->print( String(v).c_str() );
  }
  
  void print( char v )
  {
    lcd->print( v );
  }

  void print( int r, int c, String str )
  {
    if (r == 0 && c == 0)
      lcd->clear();

    lcd->setCursor( r,c );
    lcd->print( str.c_str() );
  }

};
