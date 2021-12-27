# ESP32_WiFi_Switch

Powered by a ESP32 S2 Wroom

PCB design located in KiCad in `./breakout_board`


## Config

Configuration file in `Firmware/src/config.h`


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
