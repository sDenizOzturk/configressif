#pragma once

#include <WString.h>

namespace configressif
{

  class NtpValidation
  {
  public:
    // Returns the first valid NTP server from config, or the default if not available
    static String getFirstServer();

    // Returns the first valid timezone offset, or zero if not available
    static int getFirstOffset();

    // Checks if the given server value exists in the valid NTP server list
    static bool isServerValid(const String &value);

    // Checks if the given offset value exists in the valid timezone offset list
    static bool isOffsetValid(int value);
  };

} // namespace configressif
