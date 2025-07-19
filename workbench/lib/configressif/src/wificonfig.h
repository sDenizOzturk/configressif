#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace configressif
{

  class WifiConfig
  {
  public:
    static WifiConfig &instance();

    void setFromJson(const JsonObject &obj);
    void toJson(JsonObject &obj) const;

    const String &ssid() const;
    const String &password() const;
    const String &ip() const;
    const String &gateway() const;
    const String &subnet() const;
    bool wifiEnabled() const;
    bool dhcpEnabled() const;

  private:
    WifiConfig();
    bool loadFromNVS();
    bool saveToNVS() const;

    bool m_wifiEnabled = false;
    bool m_dhcpEnabled = true;
    String m_ssid;
    String m_password;
    String m_ip;
    String m_gateway;
    String m_subnet;
  };
  static constexpr const char *NVS_NAMESPACE = "wifi_config";

} // namespace configressif
