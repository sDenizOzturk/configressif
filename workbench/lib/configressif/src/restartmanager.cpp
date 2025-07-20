#include "restartmanager.h"
#include <esp_timer.h>

namespace configressif
{

  void RestartManager::syncReboot(unsigned int delaySeconds, const char *message)
  {
    if (message && strlen(message) > 0)
      Serial.println(message);

    for (int i = delaySeconds; i > 0; --i)
    {
      Serial.printf("[configressif] Restarting device in %d seconds...\n", i);
      delay(1000);
    }
    Serial.println("[configressif] Restarting now...");
    ESP.restart();
  }

  void restartCallback(void * /*arg*/)
  {
    Serial.println("[configressif] Restarting now...");
    ESP.restart();
  }

  void RestartManager::schedule(unsigned long delaySeconds)
  {
    esp_timer_handle_t restartTimer;
    esp_timer_create_args_t timerArgs = {
        .callback = &restartCallback,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "restart_timer"};

    esp_err_t result = esp_timer_create(&timerArgs, &restartTimer);
    if (result != ESP_OK)
    {
      Serial.println("[configressif] Failed to create restart timer.");
      return;
    }

    esp_timer_start_once(restartTimer, delaySeconds * 1000000); // microseconds
    Serial.printf("[configressif] Scheduled restart in %lu seconds...\n", delaySeconds);
  }

}
