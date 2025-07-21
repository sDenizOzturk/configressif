#pragma once
#include <ESPAsyncWebServer.h>

namespace configressif
{
  class NtpRoutes
  {
  public:
    explicit NtpRoutes(AsyncWebServer &server);
    void setup();

  private:
    AsyncWebServer &m_server;

    void handleGet();
    void handlePost();
  };
}
