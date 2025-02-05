
struct DBElement
{
  String codeKeys;
  String codeRF;
  String codeFinger;
  String tel1;
  String message;
};


class Datenbank
{
private:
  DBElement dataBase[10];
  int lastFreeElement=0;
public:
  void addKeysCodeMessage(String code, String phone, String message)
  {
    dataBase[lastFreeElement] = {code,"","",phone, message};
    lastFreeElement++;
  }

  void addRFCodeMessage(String code, String phone, String message)
  {
    dataBase[lastFreeElement] = {"",code,"",phone, message};
    lastFreeElement++;
  }

  void addFingerCodeMessage(String code, String phone, String message)
  {
    dataBase[lastFreeElement] = {"","",code,phone, message};
    lastFreeElement++;
  }
  
  int durchsuchenKeys(String code)
  {
    for(int i = 0; i < 10; i++)
    {
      DBElement el = dataBase[i];
      if( el.codeKeys == code)
      {
        return i;
      }
    } 
    return -1;
  }

  int durchsuchenRf(String code)
  {
    for(int i = 0; i < 10; i++)
    {
      DBElement el = dataBase[i];
      if( el.codeRF == code)
      {
        return i;
      }
    } 
    return -1;
  }

  int durchsuchenFinger(String code)
  {
    for(int i = 0; i < 10; i++)
    {
      DBElement el = dataBase[i];
      if( el.codeFinger == code)
      {
        return i;
      }
    } 
    return -1;
  }
};