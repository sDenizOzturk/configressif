#include "ntpconfig.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "ntpvalidation.h"
#include "ntpstorage.h"

using namespace configressif;

bool configressif::NtpConfig::m_initialized = false;

NtpConfig::NtpConfig() {}

NtpConfig &NtpConfig::instance()
{
  static NtpConfig config;
  if (!config.m_initialized)
  {
    config.m_initialized = true;
    // Load configuration from storage
    NtpStorage storage;
    storage.load();
  }
  return config;
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
    if (!NtpValidation::isServerValid(newServer))
      newServer = NtpValidation::getFirstServer();

    if (newServer != m_server)
    {
      m_server = newServer;
      changed = true;
    }
  }

  if (json["timezoneOffset"].is<int>())
  {
    int newOffset = json["timezoneOffset"].as<int>();
    if (!NtpValidation::isOffsetValid(newOffset))
      newOffset = NtpValidation::getFirstOffset();

    if (newOffset != m_timezoneOffset)
    {
      m_timezoneOffset = newOffset;
      changed = true;
    }
  }

  if (changed)
  {
    NtpStorage storage;
    storage.save();
  }
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

void NtpConfig::setEnabled(bool enabled) { m_enabled = enabled; }
void NtpConfig::setServer(const String &server) { m_server = server; }
void NtpConfig::setTimezoneOffset(int offset) { m_timezoneOffset = offset; }