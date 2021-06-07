#include "Logger.h"
#include "System_Cfg.h"

void Task1(void* pvParameters)
{
  while(1)
  {
    Logger::debug("Current Software Version: " + SW_VERSION + ", Compiled at: " + DATE_TIME + "\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}