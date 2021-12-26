#include <Arduino.h>
// #include <WiFiNINA.h>
#include <WiFi.h>
#include "time.h"
#include "monitor.h" 
#include "config.h"

// OLED display controller
Monitor monitor;


// Arduino Initialize
void setup(){

  monitor = Monitor();
  monitor.setup();
  monitor.refresh();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}


void updateLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }
  monitor.setTime(&timeinfo);
}


// Arduino run loop
void loop() {
  updateLocalTime();
  monitor.refresh();
  
  delay(10);
}
