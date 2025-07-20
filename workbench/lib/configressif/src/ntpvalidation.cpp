#include "ntpvalidation.h"

#include <SPIFFS.h>
#include <ArduinoJson.h>

using namespace configressif;

String NtpValidation::getFirstServer()
{
  File file = SPIFFS.open("/configs/ntp-servers.json", "r");
  if (!file)
    return "pool.ntp.org";

  JsonDocument doc;
  if (deserializeJson(doc, file) != DeserializationError::Ok)
  {
    file.close();
    return "pool.ntp.org";
  }
  file.close();

  if (!doc.is<JsonArray>() || doc.size() == 0)
    return "pool.ntp.org";

  return doc[0]["value"] | "pool.ntp.org";
}

int NtpValidation::getFirstOffset()
{
  File file = SPIFFS.open("/configs/timezone-offsets.json", "r");
  if (!file)
    return 0;

  JsonDocument doc;
  if (deserializeJson(doc, file) != DeserializationError::Ok)
  {
    file.close();
    return 0;
  }
  file.close();

  if (!doc.is<JsonArray>() || doc.size() == 0)
    return 0;

  return doc[0]["value"] | 0;
}

bool NtpValidation::isServerValid(const String &value)
{
  File file = SPIFFS.open("/configs/ntp-servers.json", "r");
  if (!file)
    return false;

  JsonDocument doc;
  if (deserializeJson(doc, file) != DeserializationError::Ok)
  {
    file.close();
    return false;
  }
  file.close();

  for (JsonObject obj : doc.as<JsonArray>())
  {
    if (obj["value"].as<String>() == value)
      return true;
  }

  return false;
}

bool NtpValidation::isOffsetValid(int value)
{
  File file = SPIFFS.open("/configs/timezone-offsets.json", "r");
  if (!file)
    return false;

  JsonDocument doc;
  if (deserializeJson(doc, file) != DeserializationError::Ok)
  {
    file.close();
    return false;
  }
  file.close();

  for (JsonObject obj : doc.as<JsonArray>())
  {
    if (obj["value"].as<int>() == value)
      return true;
  }

  return false;
}