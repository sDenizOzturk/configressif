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
    };

} // namespace configressif
