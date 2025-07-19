#include "configressif.h"
#include "networkmanager.h"
#include "ntpmanager.h"
#include "httpserver.h"

namespace configressif
{

    namespace
    {
        HttpServer httpServer;
    }

    void Configressif::init()
    {
        NetworkManager::begin();
        NtpManager::configure();
        httpServer.begin();
    }

} // namespace configressif
