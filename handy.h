#pragma once  // Verhindert, dass diese Datei mehrmals geladen wird

// Funktion: Sendet eine Nachricht an das Handy über die ODG-Schnittstelle
// Das Handy empfängt die Nachricht und sendet sie dann als SMS weiter.
void handy_send(String tel, String nachricht)
{
  // Erstelle die Nachricht im speziellen Format für die App
  // Beispiel: "send|1234567890|Hallo!|\n"
  String message = String("send|") + tel + "|" + nachricht + "|\n";

  // Schickt die Nachricht über die serielle Schnittstelle (z. B. Bluetooth oder USB)
  // Das Handy mit AppInventor liest diese Nachricht aus und sendet sie als SMS.
  Serial.print(message.c_str()); 
}
