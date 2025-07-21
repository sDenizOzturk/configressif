#pragma once

#include <ESPAsyncWebServer.h>

namespace configressif
{

    class HttpServer
    {
    public:
        HttpServer();
        void begin();

    private:
        AsyncWebServer m_server;
        void handleStaticFiles();
        void handleNetworkGet();
        void handleNetworkPost();
    };

} // namespace configressif
