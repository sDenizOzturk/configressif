#include "httpserver.h"
#include "wificonfig.h"
#include "ntpconfig.h"
#include "ntpmanager.h"
#include "ntpstatus.h"

#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "restartmanager.h"

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

        handleStaticFiles();
        handleNetworkGet();
        handleNetworkPost();
        handleNtpGet();
        handleNtpPost();

        server.begin();
        Serial.println("[configressif] HTTP server started");
    }

    void HttpServer::handleStaticFiles()
    {
        server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

        server.onNotFound([](AsyncWebServerRequest *request)
                          { request->send(SPIFFS, "/index.html", "text/html"); });
    }

    void HttpServer::handleNetworkGet()
    {
        server.on("/api/network", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
            JsonDocument doc;
            JsonObject jsonObject = doc.to<JsonObject>();
            WifiConfig::instance().toJson(jsonObject);
    
            String json;
            serializeJson(doc, json);
            request->send(200, "application/json", json); });
    }

    void HttpServer::handleNetworkPost()
    {
        server.on("/api/network", HTTP_POST, [](AsyncWebServerRequest *request)
                  {
                      // Required to prevent premature connection closure
                  },
                  nullptr, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t, size_t)
                  {
                JsonDocument doc;
                DeserializationError error = deserializeJson(doc, data, len);

                if (error)
                {
                    Serial.println("[configressif] Failed to parse incoming JSON.");
                    request->send(400, "application/json", R"({"error":"Invalid JSON"})");
                    return;
                }

                WifiConfig::instance().setFromJson(doc.as<JsonObject>());
                Serial.println("[configressif] New network settings saved.");

                // Construct the response dynamically
                JsonDocument responseDoc;
                responseDoc["status"] = "ok";
                JsonObject rebootObj = responseDoc["reboot"].to<JsonObject>();
                rebootObj["countdown"] = 3;
                rebootObj["redirectAfter"] = 20;

                String responseJson;
                serializeJson(responseDoc, responseJson);

                request->send(200, "application/json", responseJson);

                RestartManager::schedule(3); });
    }

    void HttpServer::handleNtpGet()
    {
        server.on("/api/ntp", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
        JsonDocument doc;
        JsonObject root = doc.to<JsonObject>();

        NtpConfig::instance().toJson(root);

        unsigned long long now = NtpStatus::now();
        if (now > 0)
            root["currentTime"] = now;

        String json;
        serializeJson(doc, json);
        request->send(200, "application/json", json); });
    }

    void HttpServer::handleNtpPost()
    {
        server.on("/api/ntp", HTTP_POST, [](AsyncWebServerRequest *request)
                  {
                      // required placeholder
                  },
                  nullptr, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t, size_t)
                  {
                      JsonDocument doc;
                      DeserializationError error = deserializeJson(doc, data, len);

                      if (error)
                      {
                          Serial.println("[configressif] Failed to parse NTP JSON.");
                          request->send(400, "application/json", R"({"error":"Invalid JSON"})");
                          return;
                      }

                      NtpConfig::instance().setFromJson(doc.as<JsonObject>());
                      NtpManager::configure();

                      Serial.println("[configressif] NTP config updated.");

                      JsonDocument responseDoc;
                      JsonObject responseObj = responseDoc.to<JsonObject>();
                      NtpConfig::instance().toJson(responseObj);
                     
                      unsigned long long now = NtpStatus::now();
                      if (now > 0)
                          responseDoc["currentTime"] = now;


                      String response;
                      serializeJson(responseDoc, response);
                      request->send(200, "application/json", response); });
    }

} // namespace configressif
