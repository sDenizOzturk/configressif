#include "networkroutes.h"
#include "networkconfig.h"
#include "networkmanager.h"

#include "system/restartmanager.h"

namespace configressif
{
  NetworkRoutes::NetworkRoutes(AsyncWebServer &server)
      : m_server(server)
  {
  }

  void NetworkRoutes::setup()
  {
    handleGet();
    handlePost();
  }

  void NetworkRoutes::handleGet()
  {
    m_server.on("/api/network", HTTP_GET, [](AsyncWebServerRequest *request)
                {
            JsonDocument doc;
            JsonObject jsonObject = doc.to<JsonObject>();
            NetworkConfig::instance().toJson(jsonObject);
    
            String json;
            serializeJson(doc, json);
            request->send(200, "application/json", json); });
  }

  void NetworkRoutes::handlePost()
  {
    m_server.on("/api/network", HTTP_POST, [](AsyncWebServerRequest *request)
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

                NetworkConfig::instance().setFromJson(doc.as<JsonObject>());
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
}
