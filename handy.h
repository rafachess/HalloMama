//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(2, 3); // RX, TX
#pragma once

class Handy
{
  public:
  void start()
  {
    //mySerial.begin(9600);
  }

  void send( String tel, String nachricht )
  {
    //Serial.print ("Handy::send ");
    //Serial.print (tel.c_str());
    //Serial.print (" ");
    //Serial.println (nachricht.c_str());
    String message = String("send|") + tel + "|" + nachricht + "|\n";
    Serial.print(message.c_str());
    //mySerial.write(message.c_str());
    //Serial.println ("Ende");
    
  }
};