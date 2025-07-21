
#include "network/accesspoint/accesspoint.h"
#include "network/accesspoint/accesspointconfig.h"
#include <WiFi.h>

namespace configressif
{

  void AccessPoint::begin()
  {
    const auto &apConfig = configressif::AccessPointConfig::instance();

    if (!apConfig.apEnabled())
      return;

    WiFi.mode(WIFI_AP);

    IPAddress localIp, gateway, subnet;
    localIp.fromString(apConfig.ip());
    gateway.fromString(apConfig.gateway());
    subnet.fromString(apConfig.subnet());

    WiFi.softAPConfig(localIp, gateway, subnet);
    WiFi.softAP(apConfig.ssid().c_str(), apConfig.password().c_str());

    Serial.print("[configressif] AP IP address: ");
    Serial.println(WiFi.softAPIP());
  }

}
