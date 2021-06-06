#ifndef __OTA_H__
#define __OTA_H__
#include <WiFi.h>

class OTA
{
public:
  static void execOTA();
private:
  static WiFiClient client;
  static long contentLength;
  static bool isValidContentType;
  // Utility to extract header value from headers
  static String getHeaderValue(String header, String headerName);
};

#endif /*__OTA_H__*/