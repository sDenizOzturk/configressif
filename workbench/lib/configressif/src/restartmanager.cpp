#include "restartmanager.h"
#include "esp_timer.h"

namespace configressif
{
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
