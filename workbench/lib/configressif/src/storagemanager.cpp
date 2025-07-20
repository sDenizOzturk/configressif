#include "storagemanager.h"
#include "ntpstorage.h"
#include "networkstorage.h"
#include <SPIFFS.h>
#include <Preferences.h>
#include "restartmanager.h"
#include <nvs_flash.h>

namespace configressif
{

  void StorageManager::init()
  {
    // For manual testing, uncomment the line below to clear all storage
    // clearAll();

    if (!SPIFFS.begin(true))
    {
      RestartManager::syncReboot(
          5,
          "[configressif] ERROR: Failed to mount SPIFFS. Please ensure that the 'data' folder is uploaded to SPIFFS. Device will reboot in 5 seconds.");
    }
    fillAll();
  }

  void StorageManager::fillAll()
  {
    NtpStorage().fill();
    NetworkStorage().fill();
  }

  void StorageManager::clearAll()
  {
    NtpStorage().clear();
    NetworkStorage().clear();
  }

} // namespace configressif
