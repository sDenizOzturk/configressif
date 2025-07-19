#pragma once

namespace configressif
{
  class NtpManager
  {
  public:
    static void configure();
    static unsigned long long getTime();
  };
}
