#include <SoftwareSerial.h>

SoftwareSerial myPort(2, 3); // RX, TX

void setup()
{
  Serial.begin(9600);
  myPort.begin(9600);
}

  void loop()
{
  if (myPort.available())
    Serial.write(myPort.read());
}
