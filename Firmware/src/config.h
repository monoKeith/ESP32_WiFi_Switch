#ifndef CONFIG_H
#define CONFIG_H


const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWD";

static const char* ntpServer = "pool.ntp.org";
// Eastern time
static const long  gmtOffset_sec = 3600 * (-5);
static const int   daylightOffset_sec = 3600;

#endif