#include <SoftwareSerial.h>

SoftwareSerial myPort(2, 3); // RX, TX

void setup()
{
  Serial.begin(115200);
  myPort.begin(9600);
}

  void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
}
