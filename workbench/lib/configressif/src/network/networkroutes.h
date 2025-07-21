#pragma once
#include <ESPAsyncWebServer.h>

namespace configressif
{
  class NetworkRoutes
  {
  public:
    explicit NetworkRoutes(AsyncWebServer &server);
    void setup();

  private:
    AsyncWebServer &m_server;

    void handleGet();
    void handlePost();
  };
}
