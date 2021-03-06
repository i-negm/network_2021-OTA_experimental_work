#ifndef __SYSTEM_CFG__
#define __SYSTEM_CFG__

#define SSID_NAME "Test"
#define PSWD "12345678"
#define FOTA_SERVER_IP "fota-server.ddns.net"
#define FOTA_SERVER_PORT 80
#define FOTA_SERVER_TIMEOUT_MS 5000
#define FOTA_SERVER_BIN "/fetch"
#define FOTA_SERVER_BIN_VERSION "/version"
#define FOTA_SERVER_PERIODIC_CHECK_MS 5000

#define LED_BUILTIN 2
#define LED_FREQUENCY_MS 100

#define SW_MAJOR 1
#define SW_MINOR 3
#define SW_PATCH 0
#define SW_VERSION (String)("v" + String(SW_MAJOR) + "." + String(SW_MINOR) + "." + String(SW_PATCH))

/* Auto generated time and date */
#define DATE_TIME (String)(String(__DATE__) + " " + String(__TIME__))

#endif /*__SYSTEM_CFG__*/