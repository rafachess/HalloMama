#pragma once
#include "Adafruit_MPR121.h"
#include "lcd.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
String tastencode = "";


class Tasten
{
  public:
  void start()
  {
    //Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
    if (!cap.begin(0x5A)) {
      Serial.println("MPR121 not found, full stop!");
      while (1);
    }
  }

  String read()
  {  
    //delay(50);
    tastencode="";   
    LCD::inst().print( 0,1,"               " );
    LCD::inst().setPosition( 0,1 );
    unsigned long letzte_taste_zeit = 0; // Zeit des letzten Tastendrucks
    const unsigned long zeit_pro_taste = 2000; // Timeout in Millisekunden
    int cnt=0;

    while (true)
    {
      currtouched = cap.touched();
      Serial.print(currtouched); Serial.println(" curtouched");
      for (uint8_t i=0; i<12; i++) {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
          Serial.print(i); Serial.println(" touched");
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
          auto k = decodeKey(i);
          tastencode += k;
          Serial.print(i); Serial.println(" released");
          LCD::inst().print( String(k) );
          letzte_taste_zeit = millis();
          break;
        }
      }

      // reset our state
      lasttouched = currtouched;
      if ( tastencode.length() > 0 )
      {
        if ( millis() - letzte_taste_zeit  > zeit_pro_taste ) 
        {
          return tastencode;
        }
      }
      else
      {
        if (cnt++ > 5)
          break;
      }
      delay(10);   
    }
    delay(100);
    return tastencode;
  }

  char decodeKey( uint8_t k )
  {
    switch (k){
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
      default: return ' ';
    }
  }

};
