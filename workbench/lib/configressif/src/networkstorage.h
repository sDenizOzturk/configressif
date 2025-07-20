#pragma once

#include "storage.h"
#include <Preferences.h>

namespace configressif
{

  class NetworkStorage : public Storage
  {
    Preferences prefs;
    static constexpr const char *NVS_NAMESPACE = "network_config";

  public:
    void load() override;
    bool save() override;
    void clear() override;
    void fill() override;
  };

} // namespace configressif
