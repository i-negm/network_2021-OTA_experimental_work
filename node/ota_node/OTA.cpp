#include "OTA.h"
#include "System_Cfg.h"
#include "Logger.h"
#include <Update.h>

WiFiClient OTA::client;

long OTA::contentLength = 0;
bool OTA::isValidContentType = false;

String OTA::getHeaderValue(String header, String headerName) {
  return header.substring(strlen(headerName.c_str()));
}

void OTA::execOTA()
{
  Logger::debug("Connecting to: " + String(FOTA_SERVER_IP) + "\n");
  // Connect to S3
  if (OTA::client.connect(String(FOTA_SERVER_IP).c_str(), FOTA_SERVER_PORT))
  {
    // Connection Succeed.
    // Fecthing the FOTA_SERVER_BIN
    Logger::debug("Fetching Bin: " + String(FOTA_SERVER_BIN) + "\n");

    // Get the contents of the FOTA_SERVER_BIN file
    OTA::client.print(String("GET ") + FOTA_SERVER_BIN + " HTTP/1.1\r\n" +
                 "Host: " + FOTA_SERVER_IP + "\r\n" +
                 "Cache-Control: no-cache\r\n" +
                 "Connection: close\r\n\r\n");

    // Check what is being sent
    //    Serial.print(String("GET ") + FOTA_SERVER_BIN + " HTTP/1.1\r\n" +
    //                 "FOTA_SERVER_IP: " + FOTA_SERVER_IP + "\r\n" +
    //                 "Cache-Control: no-cache\r\n" +
    //                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (OTA::client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
        Logger::error("OTA::client Timeout !");
        OTA::client.stop();
        return;
      }
    }
    // Once the response is available,
    // check stuff

    /*
       Response Structure
        HTTP/1.1 200 OK
        x-amz-id-2: NVKxnU1aIQMmpGKhSwpCBh8y2JPbak18QLIfE+OiUDOos+7UftZKjtCFqrwsGOZRN5Zee0jpTd0=
        x-amz-request-id: 2D56B47560B764EC
        Date: Wed, 14 Jun 2017 03:33:59 GMT
        Last-Modified: Fri, 02 Jun 2017 14:50:11 GMT
        ETag: "d2afebbaaebc38cd669ce36727152af9"
        Accept-Ranges: bytes
        Content-Type: application/octet-stream
        Content-Length: 357280
        Server: AmazonS3
                                   
        {{BIN FILE CONTENTS}} 

    */
    while (OTA::client.available())
    {
      // read line till /n
      String line = OTA::client.readStringUntil('\n');
      // remove space, to check if the line is end of headers
      line.trim();

      // if the the line is empty,
      // this is end of headers
      // break the while and feed the
      // remaining `OTA::client` to the
      // Update.writeStream();
      if (!line.length())
      {
        //headers ended
        break; // and get the OTA started
      }

      // Check if the HTTP Response is 200
      // else break and Exit Update
      if (line.startsWith("HTTP/1.1"))
      {
        if (line.indexOf("200") < 0)
        {
          Logger::debug("Got a non 200 status code from server. Exiting OTA Update.\n");
          break;
        }
      }

      // extract headers here
      // Start with content length
      if (line.startsWith("Content-Length: "))
      {
        OTA::contentLength = atol((OTA::getHeaderValue(line, "Content-Length: ")).c_str());
        Logger::debug("Got " + String(OTA::contentLength) + " bytes from server\n");
      }

      // Next, the content type
      if (line.startsWith("Content-Type: "))
      {
        String contentType = OTA::getHeaderValue(line, "Content-Type: ");
        Logger::debug("Got " + contentType + " payload.\n");
        if (contentType == "application/octet-stream")
        {
          OTA::isValidContentType = true;
        }
      }
    }
  }
  else
  {
    // Connect to S3 failed
    // May be try?
    // Probably a choppy network?
    Logger::error("Connection to " + String(FOTA_SERVER_IP) + " failed. Please check your setup" + "\n");
    // retry??
    // execOTA();
  }

  // Check what is the contentLength and if content type is `application/octet-stream`
  Logger::debug("contentLength : " + String(OTA::contentLength) + ", isValidContentType : " + String(OTA::isValidContentType) + "\n");

  // check contentLength and content type
  if (OTA::contentLength && OTA::isValidContentType)
  {
    // Check if there is enough to OTA Update
    bool canBegin = Update.begin(contentLength);

    // If yes, begin
    if (canBegin)
    {
      Logger::debug("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!\n");
      // No activity would appear on the Serial monitor
      // So be patient. This may take 2 - 5mins to complete
      size_t written = Update.writeStream(OTA::client);

      if (written == OTA::contentLength)
      {
        Logger::debug("Written : " + String(written) + " successfully\n");
      }
      else
      {
        Logger::error("Written only : " + String(written) + "/" + String(OTA::contentLength) + ". Retry?\n");
        // retry??
        // execOTA();
      }

      if (Update.end())
      {
        Logger::debug("OTA done!\n");
        if (Update.isFinished())
        {
          Logger::debug("Update successfully completed. Rebooting.\n");
          ESP.restart();
        }
        else
        {
          Logger::error("Update not finished? Something went wrong!\n");
        }
      }
      else
      {
        Logger::error("Error Occurred. Error #: " + String(Update.getError()) + "\n");
      }
    }
    else
    {
      // not enough space to begin OTA
      // Understand the partitions and
      // space availability
      Logger::error("Not enough space to begin OTA\n");
      OTA::client.flush();
    }
  }
  else
  {
    Logger::error("There was no content in the response\n");
    OTA::client.flush();
  }
}