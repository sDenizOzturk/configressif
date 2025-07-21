#pragma once

#include <ArduinoJson.h>

namespace configressif
{
  class NtpStatus
  {
  public:
    // Convenience: returns timestamp in millis if available, 0 otherwise
    static unsigned long long now();

    // Returns whether NTP has been configured (timezone and server applied)
    static bool isRunning();
  };
}
