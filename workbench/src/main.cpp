#include <Arduino.h>
#include <configressif.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting Configressif firmware...");
  configressif::Configressif::init();
}

void loop()
{
}
