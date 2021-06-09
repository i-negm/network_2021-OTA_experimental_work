#include "Logger.h"
#include "System_Cfg.h"

void TaskMain(void* pvParameters)
{
  pinMode(LED_BUILTIN, OUTPUT);
  bool toggle = false;
  while(1)
  {
    Logger::debug("Current Software Version: " + SW_VERSION + ", Compiled at: " + DATE_TIME + "\n");
    toggle ^= 1;
    digitalWrite(LED_BUILTIN, toggle);
    vTaskDelay(LED_FREQUENCY_MS/portTICK_PERIOD_MS);
  }
}