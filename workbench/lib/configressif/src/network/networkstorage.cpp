#include "network/networkstorage.h"
#include "network/networkconfig.h"
#include "SPIFFS.h"

using namespace configressif;

void NetworkStorage::load()
{
  prefs.begin(NVS_NAMESPACE, true);

  NetworkConfig &config = NetworkConfig::instance();
  config.setWifiEnabled(prefs.getBool("wifiEnabled", false));
  config.setSsid(prefs.getString("ssid", ""));
  config.setPassword(prefs.getString("password", ""));
  config.setDhcpEnabled(prefs.getBool("dhcpEnabled", true));
  config.setIp(prefs.getString("ip", ""));
  config.setGateway(prefs.getString("gateway", ""));
  config.setSubnet(prefs.getString("subnet", ""));

  prefs.end();
}

bool NetworkStorage::save()
{
  prefs.begin(NVS_NAMESPACE, false);

  const NetworkConfig &config = NetworkConfig::instance();
  prefs.putBool("wifiEnabled", config.wifiEnabled());
  prefs.putString("ssid", config.ssid());
  prefs.putString("password", config.password());
  prefs.putBool("dhcpEnabled", config.dhcpEnabled());
  prefs.putString("ip", config.ip());
  prefs.putString("gateway", config.gateway());
  prefs.putString("subnet", config.subnet());

  prefs.end();
  return true;
}

void NetworkStorage::clear()
{
  prefs.begin(NVS_NAMESPACE, false);
  prefs.clear();
  prefs.end();
}

void NetworkStorage::fill()
{
  prefs.begin(NVS_NAMESPACE, false);

  if (prefs.isKey("wifiEnabled") &&
      prefs.isKey("ssid") &&
      prefs.isKey("password") &&
      prefs.isKey("dhcpEnabled") &&
      prefs.isKey("ip") &&
      prefs.isKey("gateway") &&
      prefs.isKey("subnet"))
  {
    prefs.end();
    return;
  }

  // Read all defaults once from JSON
  File file = SPIFFS.open("/default/network.json", "r");
  bool wifiEnabled = false;
  String ssid = "";
  String password = "";
  bool dhcpEnabled = true;
  String ip = "";
  String gateway = "";
  String subnet = "";

  if (file)
  {
    JsonDocument doc;
    if (deserializeJson(doc, file) == DeserializationError::Ok)
    {
      if (doc["wifiEnabled"].is<bool>())
        wifiEnabled = doc["wifiEnabled"].as<bool>();
      if (doc["ssid"].is<String>())
        ssid = doc["ssid"].as<String>();
      if (doc["password"].is<String>())
        password = doc["password"].as<String>();
      if (doc["dhcpEnabled"].is<bool>())
        dhcpEnabled = doc["dhcpEnabled"].as<bool>();
      if (doc["ip"].is<String>())
        ip = doc["ip"].as<String>();
      if (doc["gateway"].is<String>())
        gateway = doc["gateway"].as<String>();
      if (doc["subnet"].is<String>())
        subnet = doc["subnet"].as<String>();
    }
    file.close();
  }

  if (!prefs.isKey("wifiEnabled"))
    prefs.putBool("wifiEnabled", wifiEnabled);
  if (!prefs.isKey("ssid"))
    prefs.putString("ssid", ssid);
  if (!prefs.isKey("password"))
    prefs.putString("password", password);
  if (!prefs.isKey("dhcpEnabled"))
    prefs.putBool("dhcpEnabled", dhcpEnabled);
  if (!prefs.isKey("ip"))
    prefs.putString("ip", ip);
  if (!prefs.isKey("gateway"))
    prefs.putString("gateway", gateway);
  if (!prefs.isKey("subnet"))
    prefs.putString("subnet", subnet);

  prefs.end();
}
