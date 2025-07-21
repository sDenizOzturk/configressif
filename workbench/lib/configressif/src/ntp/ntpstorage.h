#pragma once

#include "storage/storage.h"
#include <Preferences.h>

namespace configressif
{

  class NtpStorage : public Storage
  {
    Preferences prefs; // Preferences instance for NVS storage

    // Namespace for NTP configuration in NVS
    static constexpr const char *NVS_NAMESPACE = "ntp_config";

  public:
    void load() override;  // Loads config into NtpConfig::instance()
    bool save() override;  // Saves config from NtpConfig::instance()
    void clear() override; // Erases NVS keys for NTP (factory reset)
    void fill() override;  // Fills NVS with defaults if missing (from SPIFFS or hardcoded)
  };

} // namespace configressif
