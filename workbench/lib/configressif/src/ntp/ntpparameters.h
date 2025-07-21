#pragma once

#include "ntpconfig.h"

namespace configressif
{

  class NtpParameters
  {
  public:
    static bool enabled()
    {
      return NtpConfig::instance().enabled();
    }

    static const String &server()
    {
      return NtpConfig::instance().server();
    }

    static int timezoneOffset()
    {
      return NtpConfig::instance().timezoneOffset();
    }
  };

} // namespace configressif
