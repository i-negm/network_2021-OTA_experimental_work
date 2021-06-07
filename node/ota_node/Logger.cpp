#include <Arduino.h>
#include "Logger.h"

static inline String getCurrentTaskName()
{
  return (String)pcTaskGetTaskName(NULL);
}

void Logger::init(void)
{
  Serial.begin(115200);
  delay(10); // Delay for stabilization
}

void Logger::debug(String fmt)
{
  Serial.print("[DEBUG] [" + getCurrentTaskName() + "]: ");
  Serial.print(fmt);
}

void Logger::error(String fmt)
{
  Serial.print("[ERROR] [" + getCurrentTaskName() + "]: ");
  Serial.print(fmt);
}

void Logger::warn(String fmt)
{
  Serial.print("[WARN] [" + getCurrentTaskName() + "]: ");
  Serial.print(fmt);
}
