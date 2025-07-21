#pragma once

namespace configressif
{

  class StorageManager
  {
  public:
    // Initializes SPIFFS and performs config bootstrap if needed
    static void init();

  private:
    // Loads default configs from SPIFFS to NVS if not already present
    static void fillAll();

    // Erases all configs (used by FactoryResetManager)
    static void clearAll();

    // Grant access to clearAll for FactoryResetManager if needed
    friend class FactoryResetManager;
  };

} // namespace configressif
