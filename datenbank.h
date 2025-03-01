#pragma once

const int MaxElements = 10;

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
  
  DBElement dataBase[MaxElements];
  int lastFreeElement=0;
public:
  void addKeysCodeMessage(String code, String phone, String message);
  void addRFCodeMessage(String code, String phone, String message);
  void addFingerCodeMessage(String code, String phone, String message);
  DBElement element(int index);
  int findKeys(String code);
  int findRf(String code);
  int findFinger(String code);
};


void Datenbank::addKeysCodeMessage(String code, String phone, String message)
{
  if ( lastFreeElement >= MaxElements )
    return;
    
  dataBase[lastFreeElement] = {code,"","",phone, message};
  lastFreeElement++;
}

void Datenbank::addRFCodeMessage(String code, String phone, String message)
{
  if ( lastFreeElement >= MaxElements )
    return;

  dataBase[lastFreeElement] = {"",code,"",phone, message};
  lastFreeElement++;
}

void Datenbank::addFingerCodeMessage(String code, String phone, String message)
{
  if ( lastFreeElement >= MaxElements )
    return;

  dataBase[lastFreeElement] = {"","",code,phone, message};
  lastFreeElement++;
}

DBElement Datenbank::element(int index)
{
  if ( index >= MaxElements || index < 0 )
    return {};

  return dataBase[index];
}

int Datenbank::findKeys(String code)
{
  for(int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];
    if( el.codeKeys == code)
    {
      return i;
    }
  } 
  return -1;
}

int Datenbank::findRf(String code)
{
  for(int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];
    if( el.codeRF == code)
    {
      return i;
    }
  } 
  return -1;
}

int Datenbank::findFinger(String code)
{
  for(int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];
    if( el.codeFinger == code)
    {
      return i;
    }
  } 
  return -1;
}
