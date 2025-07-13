#include "httpserver.h"
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

namespace configressif
{

    HttpServer::HttpServer() : server(80) {}

    void HttpServer::begin()
    {
        if (!SPIFFS.begin(true))
        {
            Serial.println("[configressif] SPIFFS mount failed!");
            return;
        }

        server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

        server.begin();
        Serial.println("[configressif] HTTP server started");
    }

} // namespace configressif
