#include "accesspointconfig.h"
#include <FS.h>
#include <SPIFFS.h>

using namespace configressif;

bool AccessPointConfig::m_initialized = false;

AccessPointConfig::AccessPointConfig() {}

AccessPointConfig &AccessPointConfig::instance()
{
  static AccessPointConfig config;
  if (!m_initialized)
  {
    config.initValues();
    m_initialized = true;
  }
  return config;
}

void AccessPointConfig::initValues()
{
  File file = SPIFFS.open("/default/access-point.json", "r");
  if (!file)
    return;

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, file);
  file.close();
  if (err != DeserializationError::Ok)
    return;

  if (doc["apEnabled"].is<bool>())
    m_apEnabled = doc["apEnabled"].as<bool>();
  if (doc["apSsid"].is<const char *>())
    m_ssid = doc["apSsid"].as<const char *>();
  if (doc["apPassword"].is<const char *>())
    m_password = doc["apPassword"].as<const char *>();
  if (doc["apIp"].is<const char *>())
    m_ip = doc["apIp"].as<const char *>();
  if (doc["apGateway"].is<const char *>())
    m_gateway = doc["apGateway"].as<const char *>();
  if (doc["apSubnet"].is<const char *>())
    m_subnet = doc["apSubnet"].as<const char *>();
}

// Getter implementations
const String &AccessPointConfig::ssid() const { return m_ssid; }
const String &AccessPointConfig::password() const { return m_password; }
const String &AccessPointConfig::ip() const { return m_ip; }
const String &AccessPointConfig::gateway() const { return m_gateway; }
const String &AccessPointConfig::subnet() const { return m_subnet; }
bool AccessPointConfig::apEnabled() const { return m_apEnabled; }
