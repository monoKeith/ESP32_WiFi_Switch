# ESP32_WiFi_Switch

This project include hardware design and firmware implementation for a ESP32 powered network accessable on/off switch.

This switch have an 128*64 OLED I2C display to show information. User can turn on/off the switch from HomeKit, physical button, or web interface.

Powered by a ESP32 S2 Wroom, might have compatibility issue on other ESP32 models, because the use of ESP32-S2 specific hardware timer library.

PCB design located in KiCad in `./breakout_board`


## Firmware

Configuration file in `Firmware/src/config.h`

## Libraries

* [esp8266-oled-ssd1306](https://github.com/ThingPulse/esp8266-oled-ssd1306)

* [ESP32TimerInterrupt](https://github.com/khoih-prog/ESP32TimerInterrupt)

## HomeBridge Plugin

Install this plugin [homebridge-http-switch](https://github.com/Supereg/homebridge-http-switch#readme) in HomeBridge, change settings:

```
{
    "accessory": "HTTP-SWITCH",
    "name": "<name-display-in-Home>",
    "switchType": "stateful",
    "serialNumber": "<fill-in-anything-here>",
    "onUrl": "http://<ip-of-esp32>:80/homebridge/switch/on",
    "offUrl": "http://<ip-of-esp32>:80/homebridge/switch/off",
    "statusUrl": "http://<ip-of-esp32>:80/homebridge/switch/status"
}
```
