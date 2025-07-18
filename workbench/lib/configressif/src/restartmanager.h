#pragma once

#include <Arduino.h>

namespace configressif
{
  class RestartManager
  {
  public:
    static void schedule(unsigned long delaySeconds);
  };
}
