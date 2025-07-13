

#include "networkmanager.h"
#include "accesspoint.h"
#include <WiFi.h>

namespace configressif
{

    void NetworkManager::begin()
    {
        AccessPoint ap;
        ap.begin("Configressif-Setup", "12345678");
    }

} // namespace configressif
