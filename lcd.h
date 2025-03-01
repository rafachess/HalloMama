#pragma once

#include <Bonezegei_LCD1602_I2C.h>


class LCD
{
  Bonezegei_LCD1602_I2C * lcd=0;
  LCD()
  {
    lcd = new Bonezegei_LCD1602_I2C(0x27);
  }

public:

  static LCD & inst()
  {
    static LCD _lcd;
    return _lcd;
  }

  void start() {
    lcd->begin();
    lcd->clear();
    delay(100);
    lcd->setPosition(0, 0);
    lcd->print("Projekt");
    lcd->setPosition(0, 1);
    lcd->print("Hallo Mama");
    delay(2000);
    lcd->clear();
    delay(100);
    lcd->setPosition(0, 0);
    lcd->print("Jugend Forscht");
    lcd->setPosition(0, 1);
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
    lcd->setPosition( r,c );
  }

  void print( String str )
  {
    lcd->print( str.c_str() );
  }

  void print( int r, int c, String str )
  {
    if (r == 0 && c == 0)
      lcd->clear();

    lcd->setPosition( r,c );
    lcd->print( str.c_str() );
  }

};




