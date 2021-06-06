#include <Arduino.h>
#include "Logger.h"

void Logger::init(void)
{
  Serial.begin(115200);
  delay(10); // Delay for stabilization
}

void Logger::debug(String fmt)
{
  Serial.print("[DEBUG]: ");
  Serial.print(fmt);
}

void Logger::error(String fmt)
{
  Serial.print("[ERROR]: ");
  Serial.print(fmt);
}

void Logger::warn(String fmt)
{
  Serial.print("[ERROR]: ");
  Serial.print(fmt);
}
