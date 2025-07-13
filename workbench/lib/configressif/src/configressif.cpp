#include "configressif.h"
#include "networkmanager.h"
#include "httpserver.h"

namespace configressif
{

    namespace
    {
        NetworkManager networkManager;
        HttpServer httpServer;
    }

    void Configressif::init()
    {
        networkManager.begin();
        httpServer.begin();
    }

} // namespace configressif
