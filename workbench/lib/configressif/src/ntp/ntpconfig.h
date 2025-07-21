#pragma once

#include <ArduinoJson.h>
#include <WString.h>

namespace configressif
{
  class NtpConfig
  {
  public:
    static NtpConfig &instance();

    void setFromJson(const JsonObject &json);
    void toJson(JsonObject &json) const;

    bool enabled() const;
    const String &server() const;
    int timezoneOffset() const;

    void setEnabled(bool enabled);
    void setServer(const String &server);
    void setTimezoneOffset(int offset);

  private:
    NtpConfig();

    static bool m_initialized;
    bool m_enabled;
    String m_server;
    int m_timezoneOffset;
  };
}
