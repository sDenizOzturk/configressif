
#include "accesspoint.h"

#include <WiFi.h>

namespace configressif
{

  void AccessPoint::begin(const char *ssid, const char *password)
  {
    WiFi.mode(WIFI_AP);
    IPAddress local_ip(192, 168, 168, 168);
    IPAddress gateway(192, 168, 168, 168);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password);

    Serial.print("[configressif] AP IP address: ");
    Serial.println(WiFi.softAPIP());
  }

}
