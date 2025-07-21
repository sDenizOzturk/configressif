#pragma once

#include <ArduinoJson.h>

namespace configressif
{

  class Storage
  {
  public:
    // Load config from backend (NVS/EEPROM) into singleton instance
    virtual void load() = 0;

    // Save singleton instance config to backend
    virtual bool save() = 0;

    // Erase or reset all storage (factory reset for this config)
    virtual void clear() = 0;

    // Fill storage from defaults (SPIFFS JSON etc.) if not present in backend
    virtual void fill() = 0;
  };
} // namespace configressif
