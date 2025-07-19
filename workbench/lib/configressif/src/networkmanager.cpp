

#include "networkmanager.h"
#include "accesspoint.h"
#include <WiFi.h>
#include "wifiparameters.h"

namespace configressif
{

    const IPAddress DNS_SERVER(8, 8, 8, 8);

    void NetworkManager::begin()
    {
        if (WifiParameters::wifiEnabled())
        {
            WiFi.mode(WIFI_STA);

            if (!WifiParameters::dhcpEnabled())
            {
                IPAddress localIP, gateway, subnet;
                if (localIP.fromString(WifiParameters::ip()) &&
                    gateway.fromString(WifiParameters::gateway()) &&
                    subnet.fromString(WifiParameters::subnet()))
                {
                    WiFi.config(localIP, gateway, subnet, DNS_SERVER);
                    Serial.println("[WiFi] Static IP configuration applied.");
                }
                else
                {
                    Serial.println("[WiFi] Invalid static IP configuration. Falling back to DHCP.");
                }
            }

            WiFi.begin(WifiParameters::ssid().c_str(), WifiParameters::password().c_str());

            unsigned long startAttemptTime = millis();
            const unsigned long TIMEOUT = 7000;

            while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < TIMEOUT)
            {
                delay(500);
            }

            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.println("[WiFi] Connected successfully");
                Serial.println(WiFi.localIP());
                return;
            }

            Serial.println("[WiFi] Failed to connect. Falling back to AP mode...");
        }

        AccessPoint ap;
        ap.begin("Configressif-Setup", "12345678");
    }

} // namespace configressif
