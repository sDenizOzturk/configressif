#pragma once

#include "wificonfig.h"

namespace configressif
{

  class WifiParameters
  {
  public:
    static bool wifiEnabled()
    {
      return WifiConfig::instance().wifiEnabled();
    }

    static const String &ssid()
    {
      return WifiConfig::instance().ssid();
    }

    static const String &password()
    {
      return WifiConfig::instance().password();
    }

    static bool dhcpEnabled()
    {
      return WifiConfig::instance().dhcpEnabled();
    }

    static const String &ip()
    {
      return WifiConfig::instance().ip();
    }

    static const String &gateway()
    {
      return WifiConfig::instance().gateway();
    }

    static const String &subnet()
    {
      return WifiConfig::instance().subnet();
    }
  };

} // namespace configressif
