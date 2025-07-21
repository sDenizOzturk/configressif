#include "ntproutes.h"
#include "ntpconfig.h"
#include "ntpstatus.h"
#include "ntpmanager.h"

namespace configressif
{
  NtpRoutes::NtpRoutes(AsyncWebServer &server)
      : m_server(server)
  {
  }

  void NtpRoutes::setup()
  {
    handleGet();
    handlePost();
  }

  void NtpRoutes::handleGet()
  {
    m_server.on("/api/ntp", HTTP_GET, [](AsyncWebServerRequest *request)
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

  void NtpRoutes::handlePost()
  {
    m_server.on("/api/ntp", HTTP_POST, [](AsyncWebServerRequest *request)
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
}
