#include "debugutils.h"
#include <Arduino.h>

void configressif::DebugUtils::countdown(unsigned int delaySeconds, const char *message)
{
  for (unsigned int i = 0; i < delaySeconds; ++i)
  {
    Serial.print(message);
    Serial.print(" (");
    Serial.print(delaySeconds - i);
    Serial.println(")");
    delay(1000);
  }
}
