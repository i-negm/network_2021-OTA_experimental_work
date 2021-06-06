#include "Logger.h"
#include "System.h"
#include "OTA.h"

#include <WiFi.h>

static void initWiFi()
{
  // Connect to provided SSID_NAME and PSWD
  WiFi.begin(SSID_NAME, PSWD);
  // Wait for connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    Logger::debug("Trying to connect (every 500ms)...\n"); // Keep the serial monitor lit!
    delay(500);
  }
}

void System::init(void)
{
  Logger::init();
  initWiFi();
  Logger::debug("Successfully connected to ("+ String(SSID_NAME) +").\n");
  OTA::execOTA();
}
