#ifndef CONFIG_H
#define CONFIG_H

/* WiFi credentials */
static const char *ssid = "YOUR_SSID";
static const char *password = "YOUR_PASSWD";

/* GPIO Pins */

#define SDA_PIN 43
#define SCL_PIN 44

#define WHITE_BUTTON_PIN 37
#define GRAY_BUTTON_PIN 36
#define BLACK_BUTTON_PIN 35

#define SWITCH_PIN 33

/* Display */

// Shift UI in regular screen, positive = down, negative = up
#define SCREEN_Y_OFFSET 7

// How long should a message (light on / off) stay on display?
#define MSG_DISPLAY_MS 3000

/* Time server */

#define NTP_SERVER "pool.ntp.org"

// Eastern time (-5 * 3600)
#define GMT_OFFSET_S -18000
#define DAYLIGHT_OFFSET_S 3600

// Update time periodically (30 mins)
#define TIME_SYNC_INTERVAL_MINUTES 30
// 2 mins for test
// #define TIME_SYNC_INTERVAL_MINUTES 2


/* HTTP server */

#define HTTP_TIMEOUT_MS 1000

/* WiFi Hostname */

#define HOSTNAME "Keith's ESP32-S2 Switch"

#endif