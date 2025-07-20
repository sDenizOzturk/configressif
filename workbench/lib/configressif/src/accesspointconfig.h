#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace configressif
{

  class AccessPointConfig
  {
  public:
    static AccessPointConfig &instance();

    void initValues(); // Loads config from SPIFFS (default/access-point.json)

    const String &ssid() const;
    const String &password() const;
    const String &ip() const;
    const String &gateway() const;
    const String &subnet() const;
    bool apEnabled() const;

  private:
    AccessPointConfig();

    static bool m_initialized;
    bool m_apEnabled;
    String m_ssid;
    String m_password;
    String m_ip;
    String m_gateway;
    String m_subnet;
  };

} // namespace configressif
