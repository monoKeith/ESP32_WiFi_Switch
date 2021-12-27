#include "state.h"


void State::setTime(tm *timeinfo){
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
  displayTime = String(buffer);
}