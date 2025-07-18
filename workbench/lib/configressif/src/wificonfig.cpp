#include "wificonfig.h"
#include <ArduinoJson.h>
#include <Preferences.h>

using namespace configressif;

namespace
{
  Preferences prefs;
  bool initialized = false;
}

WifiConfig::WifiConfig()
{
  loadFromNVS();
}

// Static initialization
WifiConfig &WifiConfig::instance()
{
  static WifiConfig config;
  if (!initialized)
  {
    config.loadFromNVS();
    initialized = true;
  }
  return config;
}

// JSON setter
void WifiConfig::setFromJson(const JsonObject &json)
{
  if (json["wifiEnabled"].is<bool>())
    m_wifiEnabled = json["wifiEnabled"].as<bool>();

  if (json["ssid"].is<String>())
    m_ssid = json["ssid"].as<String>();

  if (json["password"].is<String>())
    m_password = json["password"].as<String>();

  if (json["dhcpEnabled"].is<bool>())
    m_dhcpEnabled = json["dhcpEnabled"].as<bool>();

  if (json["ip"].is<String>())
    m_ip = json["ip"].as<String>();

  if (json["gateway"].is<String>())
    m_gateway = json["gateway"].as<String>();

  if (json["subnet"].is<String>())
    m_subnet = json["subnet"].as<String>();

  saveToNVS();
}

// JSON getter
void WifiConfig::toJson(JsonObject &obj) const
{
  obj["wifiEnabled"] = m_wifiEnabled;
  obj["ssid"] = m_ssid;
  obj["password"] = m_password;
  obj["dhcpEnabled"] = m_dhcpEnabled;
  obj["ip"] = m_ip;
  obj["gateway"] = m_gateway;
  obj["subnet"] = m_subnet;
}

// Getters
bool WifiConfig::wifiEnabled() const { return m_wifiEnabled; }
bool WifiConfig::dhcpEnabled() const { return m_dhcpEnabled; }
const String &WifiConfig::ssid() const { return m_ssid; }
const String &WifiConfig::password() const { return m_password; }
const String &WifiConfig::ip() const { return m_ip; }
const String &WifiConfig::gateway() const { return m_gateway; }
const String &WifiConfig::subnet() const { return m_subnet; }

// Private: Save to NVS
bool WifiConfig::saveToNVS() const
{
  prefs.begin("wifi_config", false);
  prefs.putBool("wifiEnabled", m_wifiEnabled);
  prefs.putString("ssid", m_ssid);
  prefs.putString("password", m_password);
  prefs.putBool("dhcpEnabled", m_dhcpEnabled);
  prefs.putString("ip", m_ip);
  prefs.putString("gateway", m_gateway);
  prefs.putString("subnet", m_subnet);
  prefs.end();
  return true;
}

// Private: Load from NVS
bool WifiConfig::loadFromNVS()
{
  prefs.begin("wifi_config", true);
  m_wifiEnabled = prefs.getBool("wifiEnabled", false);
  m_ssid = prefs.getString("ssid", "");
  m_password = prefs.getString("password", "");
  m_dhcpEnabled = prefs.getBool("dhcpEnabled", true);
  m_ip = prefs.getString("ip", "");
  m_gateway = prefs.getString("gateway", "");
  m_subnet = prefs.getString("subnet", "");
  prefs.end();
  return true;
}
