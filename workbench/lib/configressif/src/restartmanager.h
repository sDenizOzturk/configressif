#pragma once

#include <Arduino.h>

namespace configressif
{
  class RestartManager
  {
  public:
    static void schedule(unsigned long delaySeconds);
    static void syncReboot(unsigned int delaySeconds = 5, const char *message = nullptr);
  };
}
