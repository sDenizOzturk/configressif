#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace configressif
{

  class NetworkConfig
  {
  public:
    static NetworkConfig &instance();

    void setFromJson(const JsonObject &obj);
    void toJson(JsonObject &obj) const;

    const String &ssid() const;
    const String &password() const;
    const String &ip() const;
    const String &gateway() const;
    const String &subnet() const;
    bool wifiEnabled() const;
    bool dhcpEnabled() const;

    void setWifiEnabled(bool enabled);
    void setSsid(const String &ssid);
    void setPassword(const String &password);
    void setDhcpEnabled(bool enabled);
    void setIp(const String &ip);
    void setGateway(const String &gateway);
    void setSubnet(const String &subnet);

  private:
    NetworkConfig();

    static bool m_initialized;
    bool m_wifiEnabled;
    bool m_dhcpEnabled;
    String m_ssid;
    String m_password;
    String m_ip;
    String m_gateway;
    String m_subnet;
  };
  static constexpr const char *NVS_NAMESPACE = "wifi_config";

} // namespace configressif
