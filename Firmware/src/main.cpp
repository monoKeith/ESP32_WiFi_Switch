#include <Arduino.h>
#include "monitor.h" 



Monitor monitor;

void setup(){
  monitor = Monitor();
  monitor.setup();
}


void loop() {
  monitor.run();
}
