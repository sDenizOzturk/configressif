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
        AsyncWebServer server;
        void handleStaticFiles();
        void handleNetworkGet();
        void handleNetworkPost();
        void handleNtpGet();
        void handleNtpPost();
    };

} // namespace configressif
