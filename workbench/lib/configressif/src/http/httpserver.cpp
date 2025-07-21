#include "http/httpserver.h"
#include <SPIFFS.h>
#include "ntp/ntproutes.h"
#include "network/networkroutes.h"

namespace configressif
{

    HttpServer::HttpServer() : m_server(80) {}

    void HttpServer::begin()
    {
        if (!SPIFFS.begin(true))
        {
            Serial.println("[configressif] SPIFFS mount failed!");
            return;
        }

        handleStaticFiles();

        NetworkRoutes networkRoutes(m_server);
        networkRoutes.setup();

        NtpRoutes ntpRoutes(m_server);
        ntpRoutes.setup();

        m_server.begin();
        Serial.println("[configressif] HTTP server started");
    }

    void HttpServer::handleStaticFiles()
    {
        m_server.serveStatic("/", SPIFFS, "/public").setDefaultFile("index.html");
        m_server.serveStatic("/assets/", SPIFFS, "/assets");
        m_server.serveStatic("/configs/", SPIFFS, "/configs");

        m_server.onNotFound([](AsyncWebServerRequest *request)
                            { request->send(SPIFFS, "/public/index.html", "text/html"); });
    }

} // namespace configressif
