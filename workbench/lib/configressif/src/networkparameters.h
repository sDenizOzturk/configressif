#pragma once

#include "networkconfig.h"

namespace configressif
{

  class NetworkParameters
  {
  public:
    static bool wifiEnabled()
    {
      return NetworkConfig::instance().wifiEnabled();
    }

    static const String &ssid()
    {
      return NetworkConfig::instance().ssid();
    }

    static const String &password()
    {
      return NetworkConfig::instance().password();
    }

    static bool dhcpEnabled()
    {
      return NetworkConfig::instance().dhcpEnabled();
    }

    static const String &ip()
    {
      return NetworkConfig::instance().ip();
    }

    static const String &gateway()
    {
      return NetworkConfig::instance().gateway();
    }

    static const String &subnet()
    {
      return NetworkConfig::instance().subnet();
    }
  };

} // namespace configressif
