#include "networkconfig.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#include "networkstorage.h"

using namespace configressif;

bool configressif::NetworkConfig::m_initialized = false;

NetworkConfig::NetworkConfig() {}

// Static initialization
NetworkConfig &NetworkConfig::instance()
{
  static NetworkConfig config;
  if (!config.m_initialized)
  {
    config.m_initialized = true;
    // Load configuration from storage
    NetworkStorage storage;
    storage.load();
  }
  return config;
}

// JSON setter
void NetworkConfig::setFromJson(const JsonObject &json)
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

  NetworkStorage storage;
  storage.save();
}

// JSON getter
void NetworkConfig::toJson(JsonObject &obj) const
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
bool NetworkConfig::wifiEnabled() const { return m_wifiEnabled; }
bool NetworkConfig::dhcpEnabled() const { return m_dhcpEnabled; }
const String &NetworkConfig::ssid() const { return m_ssid; }
const String &NetworkConfig::password() const { return m_password; }
const String &NetworkConfig::ip() const { return m_ip; }
const String &NetworkConfig::gateway() const { return m_gateway; }
const String &NetworkConfig::subnet() const { return m_subnet; }

// Setters
void NetworkConfig::setWifiEnabled(bool enabled) { m_wifiEnabled = enabled; }
void NetworkConfig::setSsid(const String &ssid) { m_ssid = ssid; }
void NetworkConfig::setPassword(const String &pwd) { m_password = pwd; }
void NetworkConfig::setDhcpEnabled(bool enabled) { m_dhcpEnabled = enabled; }
void NetworkConfig::setIp(const String &ip) { m_ip = ip; }
void NetworkConfig::setGateway(const String &gw) { m_gateway = gw; }
void NetworkConfig::setSubnet(const String &s) { m_subnet = s; }
