#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
static const char *ssid = "YOUR_SSID";
static const char *password = "YOUR_PASSWD";

// GPIO Pins
#define SDA_PIN 4
#define SCL_PIN 5

#define WHITE_BUTTON_PIN 8
#define GRAY_BUTTON_PIN 7
#define BLACK_BUTTON_PIN 6

#define SWITCH_PIN 33

// Message display time (ms)
// How long should a message (light on / off) stay on display?
#define MSG_DISPLAY_MS 3000

// Time server
static const char *ntpServer = "pool.ntp.org";
// Eastern time
static const long gmtOffset_sec = 3600 * (-5);
static const int daylightOffset_sec = 3600;

#endif