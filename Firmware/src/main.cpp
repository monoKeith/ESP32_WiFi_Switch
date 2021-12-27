#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "monitor.h" 
#include "config.h"
#include "state.h"


// State of everything
State state;
// OLED display controller
Monitor monitor(&state);


// Arduino Initialize
void setup(){
  // Initialize
  monitor.setup();
  monitor.refresh();
  // Start Wi-Fi
  WiFi.begin(ssid, password);
}


// Sync time from server
void syncTime(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}


// Update time for monitor
void updateLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }
  state.setTime(&timeinfo);
}


// Arduino run loop
void loop() {
  // Check WiFi status
  state.wirelessConnected = (WiFi.status() == WL_CONNECTED);
  // Update time
  if (state.wirelessConnected && !state.timeSynced){
    syncTime();
    state.timeSynced = true;
  }
  updateLocalTime();
  

  // Refresh monitor
  monitor.refresh();
  delay(10);
}
