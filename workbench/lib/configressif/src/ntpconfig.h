#pragma once

#include <ArduinoJson.h>
#include <WString.h>

namespace configressif
{
  class NtpConfig
  {
  public:
    static NtpConfig &instance();

    void loadFromNVS();
    bool saveToNVS() const;

    void setFromJson(const JsonObject &json);
    void toJson(JsonObject &json) const;

    bool enabled() const;
    const String &server() const;
    int timezoneOffset() const;

  private:
    NtpConfig();

    bool m_enabled = false;
    String m_server;
    int m_timezoneOffset = 0;

    static constexpr const char *NVS_NAMESPACE = "ntp_config";
  };
}
