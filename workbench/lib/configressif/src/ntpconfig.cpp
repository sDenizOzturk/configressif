#include "ntpconfig.h"
#include <Preferences.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

using namespace configressif;

namespace
{
  Preferences prefs;
  bool initialized = false;

  String getFirstServer()
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

  int getFirstOffset()
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

  bool isServerValid(const String &value)
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

  bool isOffsetValid(int value)
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
}

NtpConfig::NtpConfig()
{
  loadFromNVS();
}

NtpConfig &NtpConfig::instance()
{
  static NtpConfig config;
  if (!initialized)
  {
    config.loadFromNVS();
    initialized = true;
  }
  return config;
}

void NtpConfig::loadFromNVS()
{
  prefs.begin(NVS_NAMESPACE, true);
  m_enabled = prefs.getBool("enabled", false);
  m_server = prefs.getString("server", getFirstServer());
  m_timezoneOffset = prefs.getInt("timezoneOffset", getFirstOffset());
  prefs.end();
}

bool NtpConfig::saveToNVS() const
{
  prefs.begin(NVS_NAMESPACE, false);
  prefs.putBool("enabled", m_enabled);
  prefs.putString("server", m_server);
  prefs.putInt("timezoneOffset", m_timezoneOffset);
  prefs.end();
  return true;
}

void NtpConfig::setFromJson(const JsonObject &json)
{
  bool changed = false;

  if (json["enabled"].is<bool>())
  {
    bool newEnabled = json["enabled"].as<bool>();
    if (newEnabled != m_enabled)
    {
      m_enabled = newEnabled;
      changed = true;
    }
  }

  if (json["server"].is<String>())
  {
    String newServer = json["server"].as<String>();
    if (!isServerValid(newServer))
      newServer = getFirstServer();

    if (newServer != m_server)
    {
      m_server = newServer;
      changed = true;
    }
  }

  if (json["timezoneOffset"].is<int>())
  {
    int newOffset = json["timezoneOffset"].as<int>();
    if (!isOffsetValid(newOffset))
      newOffset = getFirstOffset();

    if (newOffset != m_timezoneOffset)
    {
      m_timezoneOffset = newOffset;
      changed = true;
    }
  }

  if (changed)
    saveToNVS();
}

void NtpConfig::toJson(JsonObject &obj) const
{
  obj["enabled"] = m_enabled;
  obj["server"] = m_server;
  obj["timezoneOffset"] = m_timezoneOffset;
}

bool NtpConfig::enabled() const { return m_enabled; }
const String &NtpConfig::server() const { return m_server; }
int NtpConfig::timezoneOffset() const { return m_timezoneOffset; }
