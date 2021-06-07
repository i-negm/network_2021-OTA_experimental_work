#ifndef __SYSTEM_CFG__
#define __SYSTEM_CFG__

#define SSID_NAME "Test"
#define PSWD "12345678"
#define FOTA_SERVER_IP "fota-server.ddns.net"
#define FOTA_SERVER_PORT 80
#define FOTA_SERVER_BIN "/fetch"

#define SW_MAJOR 1
#define SW_MINOR 1
#define SW_PATCH 0
#define SW_VERSION (String)("v" + String(SW_MAJOR) + "." + String(SW_MINOR) + "." + String(SW_PATCH))

/* Auto generated time and date */
#define DATE_TIME (String)(String(__DATE__) + " " + String(__TIME__))

#endif /*__SYSTEM_CFG__*/