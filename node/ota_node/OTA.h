#ifndef __OTA_H__
#define __OTA_H__
#include <WiFi.h>

class OTA
{
public:
  static void execOTA(void* params);
  static void thread(void* params);
private:
  static WiFiClient client;
  static long contentLength;
  static bool isValidContentType;
  // Utility to extract header value from headers
  static String getHeaderValue(String header, String headerName);
};

#endif /*__OTA_H__*/