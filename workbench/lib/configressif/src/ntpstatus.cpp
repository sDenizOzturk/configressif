#include "ntpstatus.h"
#include "ntpmanager.h"
#include <time.h>

namespace configressif
{

  unsigned long long NtpStatus::now()
  {
    return NtpManager::getTime();
  }

  bool NtpStatus::isRunning()
  {
    return now() > 0;
  };

}
