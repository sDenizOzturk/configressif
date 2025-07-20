#include "configressif.h"
#include "storagemanager.h"
#include "networkmanager.h"
#include "ntpmanager.h"
#include "httpserver.h"
#include "debugutils.h"

namespace configressif
{

    namespace
    {
        HttpServer httpServer;
    }

    void Configressif::init()
    {

        // For manual testing, uncomment the line below to delay the startup
        // DebugUtils::countdown(10, "[configressif] Manual delay for testing");

        Serial.println("[configressif] Initializing...");
        StorageManager::init(); // SPIFFS + config bootstrap,
        Serial.println("[configressif] Storage initialized.");
        NetworkManager::begin(); // WiFi config, network logic
        Serial.println("[configressif] Network initialized.");
        NtpManager::configure(); // NTP time sync
        Serial.println("[configressif] NTP configured.");
        httpServer.begin(); // HTTP server + UI/API
        Serial.println("[configressif] HTTP server started.");
    }

} // namespace configressif
