#include "ntpmanager.h"
#include "ntpconfig.h"
#include <esp_sntp.h>
#include <WiFi.h>

namespace configressif
{
  namespace
  {
    bool configured = false;
  }

  void NtpManager::configure()
  {
    const auto &config = NtpConfig::instance();
    if (!config.enabled() || WiFi.status() != WL_CONNECTED)
    {
      configured = false;
      return;
    }

    configTime(0, 0, config.server().c_str());

    configured = true;
  }

  unsigned long long NtpManager::getTime()
  {
    const auto &config = NtpConfig::instance();
    if (!config.enabled())
      return 0;

    if (!configured)
      configure();

    for (int i = 0; i < 15; ++i)
    {
      if (sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED)
        break;
      delay(200);
    }

    struct tm tm;
    if (getLocalTime(&tm, 100))
    {
      unsigned long long currentTime = static_cast<unsigned long long>(mktime(&tm));
      return currentTime + config.timezoneOffset() * 3600;
    }

    configured = false;
    return 0;
  }

}
