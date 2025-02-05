
SoftwareSerial mySerial(10, 11); // RX, TX

class Handy
{
  public:
  void send( String tel, String nachricht )
  {
    String message = String("send|") + tel + "|" + nachricht + "\n";
    Serial.write(message.c_str());
  }
};