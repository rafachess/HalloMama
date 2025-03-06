#pragma once  // Verhindert, dass diese Datei mehrmals geladen wird

const int MaxElements = 10; // Maximale Anzahl an gespeicherten Einträgen

// Struktur für einen Datenbank-Eintrag
struct DBElement
{
  String codeKeys;    // Speichert einen Tasten-Code (z. B. eine PIN)
  String codeRF;      // Speichert einen RF-Karten-Code (z. B. eine Chipkarte)
  String codeFinger;  // Speichert einen Fingerabdruck-Code
  String tel1;        // Telefonnummer, die mit dem Code verknüpft ist
  String message;     // Nachricht, die bei erfolgreicher Authentifizierung gesendet wird
};

DBElement dataBase[MaxElements]; // Datenbank als Liste mit maximal 10 Einträgen
int lastFreeElement = 0;         // Anzahl gespeicherter Einträge, zeigt auf den nächsten freien Platz


/////////////////////////////
// Funktion: Fügt eine Nachricht und eine Telefonnummer für einen Tasten-Code hinzu
////////////////////////////
void db_addKeysCodeMessage(String code, String phone, String message)
{
  // Prüft, ob die Datenbank bereits voll ist
  if (lastFreeElement >= MaxElements)
    return;
    
  // Speichert den neuen Eintrag in der Datenbank
  // Setzt den Tasten-Code, aber lässt RF und Finger leer
  dataBase[lastFreeElement] = {code, "", "", phone, message};

  // Erhöht den Zähler für den nächsten freien Eintrag
  lastFreeElement++;
}


//////////////////////////////
// Funktion: Fügt eine Nachricht und eine Telefonnummer für einen RF-Karten-Code hinzu
/////////////////////////////
void db_addRFCodeMessage(String code, String phone, String message)
{
  // Prüft, ob die Datenbank bereits voll ist
  if (lastFreeElement >= MaxElements)
    return;

  // Speichert den neuen Eintrag in der Datenbank
  // Setzt den RF-Code, aber lässt Tasten-Code und Finger leer
  dataBase[lastFreeElement] = {"", code, "", phone, message};

  // Erhöht den Zähler für den nächsten freien Eintrag
  lastFreeElement++;
}


///////////////////////////////
// Funktion: Fügt eine Nachricht und eine Telefonnummer für einen Fingerabdruck-Code hinzu
///////////////////////////////
void db_addFingerCodeMessage(String code, String phone, String message)
{
  // Prüft, ob die Datenbank bereits voll ist
  if (lastFreeElement >= MaxElements)
    return;

  // Speichert den neuen Eintrag in der Datenbank
  // Setzt den Fingerabdruck-Code, aber lässt Tasten-Code und RF leer
  dataBase[lastFreeElement] = {"", "", code, phone, message};

  // Erhöht den Zähler für den nächsten freien Eintrag
  lastFreeElement++;
}

///////////////////////////
// Funktion: Gibt die Telefonnummer für einen gespeicherten Eintrag zurück
///////////////////////////
String db_phone(int index)
{
  // Prüft, ob der Index innerhalb des gültigen Bereichs liegt
  if (index >= MaxElements || index < 0)
  {
    return ""; // Falls der Index ungültig ist, gib einen leeren String zurück
  }
  
  return dataBase[index].tel1; // Gibt die gespeicherte Telefonnummer zurück
}


///////////////////////// 
//Funktion: Gibt die gespeicherte Nachricht für einen bestimmten Eintrag zurück
/////////////////////////
String db_message(int index)
{
  // Prüft, ob der Index innerhalb des gültigen Bereichs liegt
  if (index >= MaxElements || index < 0) 
  {
    return ""; // Falls der Index ungültig ist, gib einen leeren String zurück
  }
  
  return dataBase[index].message; // Gibt die gespeicherte Nachricht zurück
}


///////////////////////// 
//Funktion: Sucht nach einem Tasten-Code in der Datenbank und gibt ein Index zurück
////////////////////////
int db_findKeys(String code)
{
  // Geht alle Einträge in der Datenbank durch
  for (int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];

    // Falls der gespeicherte Tasten-Code mit dem gesuchten übereinstimmt, gib die Position des DB-Elements zurück
    if (el.codeKeys == code)
    {
      return i;
    }
  } 

  return -1; // Falls kein passender Code gefunden wurde, gib -1 zurück
}


////////////////////// 
//Funktion: Sucht nach einem RF-Karten-Code in der Datenbank und gibt ein Index zurück
//////////////////////
int db_findRf(String code)
{
  // Geht alle Einträge in der Datenbank durch
  for (int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];

    // Falls der gespeicherte RF-Code mit dem gesuchten übereinstimmt, gib die Position des DB-Elements zurück
    if (el.codeRF == code)
    {
      return i;
    }
  } 

  return -1; // Falls kein passender Code gefunden wurde, gib -1 zurück
}


///////////////////////
//Funktion: Sucht nach einem Fingerabdruck-Code in der Datenbank und gibt ein Index zurück
////////////////////////
int db_findFinger(String code)
{
  // Geht alle Einträge in der Datenbank durch
  for (int i = 0; i < MaxElements; i++)
  {
    DBElement el = dataBase[i];

    // Falls der gespeicherte Fingerabdruck-Code mit dem gesuchten übereinstimmt, gib die Position des DB-Elements zurück
    if (el.codeFinger == code)
    {
      return i;
    }
  } 

  return -1; // Falls kein passender Code gefunden wurde, gib -1 zurück
}
