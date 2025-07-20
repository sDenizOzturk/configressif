#include "ntpstorage.h"
#include "ntpconfig.h"
#include "ntpvalidation.h"
#include "SPIFFS.h"

using namespace configressif;

void NtpStorage::load()
{
  prefs.begin(NVS_NAMESPACE, true);

  NtpConfig &config = NtpConfig::instance();
  config.setEnabled(prefs.getBool("enabled", false));
  config.setServer(prefs.getString("server", NtpValidation::getFirstServer()));
  config.setTimezoneOffset(prefs.getInt("timezoneOffset", NtpValidation::getFirstOffset()));

  prefs.end();
}

bool NtpStorage::save()
{
  prefs.begin(NVS_NAMESPACE, false);

  const NtpConfig &config = NtpConfig::instance();
  prefs.putBool("enabled", config.enabled());
  prefs.putString("server", config.server());
  prefs.putInt("timezoneOffset", config.timezoneOffset());

  prefs.end();
  return true;
}

void NtpStorage::clear()
{
  prefs.begin(NVS_NAMESPACE, false);
  prefs.clear(); // Removes all keys in this namespace
  prefs.end();
}

void NtpStorage::fill()
{
  // Write missing keys to NVS
  prefs.begin(NVS_NAMESPACE, false);
  if (prefs.isKey("enabled") &&
      prefs.isKey("server") &&
      prefs.isKey("timezoneOffset"))
  {
    prefs.end();
    // All keys already exist, no need to fill
    return;
  }

  // Read all defaults once from JSON
  File file = SPIFFS.open("/default/ntp.json", "r");
  bool defaultEnabled = false;
  String defaultServer = "pool.ntp.org";
  int defaultOffset = 0;

  if (file)
  {
    JsonDocument doc;
    if (deserializeJson(doc, file) == DeserializationError::Ok)
    {
      if (doc["enabled"].is<bool>())
        defaultEnabled = doc["enabled"].as<bool>();
      if (doc["server"].is<String>())
        defaultServer = doc["server"].as<String>();
      if (doc["timezoneOffset"].is<int>())
        defaultOffset = doc["timezoneOffset"].as<int>();
    }
    file.close();
  }

  // Validate server and offset using utils if needed
  if (!NtpValidation::isServerValid(defaultServer))
    defaultServer = NtpValidation::getFirstServer();

  if (!NtpValidation::isOffsetValid(defaultOffset))
    defaultOffset = NtpValidation::getFirstOffset();

  if (!prefs.isKey("enabled"))
  {
    prefs.putBool("enabled", defaultEnabled);
  }
  if (!prefs.isKey("server"))
  {
    prefs.putString("server", defaultServer);
  }
  if (!prefs.isKey("timezoneOffset"))
  {
    prefs.putInt("timezoneOffset", defaultOffset);
  }

  prefs.end();
}
