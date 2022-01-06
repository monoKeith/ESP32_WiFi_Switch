#include "server.h"

namespace server
{

    // WebUI according to current state
    // https://randomnerdtutorials.com/esp32-web-server-arduino-ide/

    const String webUI_ON =
        "<!DOCTYPE html><html>"
        "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
        "<link rel=\"icon\" href=\"data:,\">"
        "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
        ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;"
        "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
        ".button2 {background-color: #555555;}</style></head>"
        "<body><h1>ESP32 WiFi Switch</h1>"
        "<p><a href=\"/switch/off\"><button class=\"button button2\">OFF</button></a></p>"

        "</body></html>";

    const String webUI_OFF =
        "<!DOCTYPE html><html>"
        "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
        "<link rel=\"icon\" href=\"data:,\">"
        "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
        ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;"
        "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
        ".button2 {background-color: #555555;}</style></head>"
        "<body><h1>ESP32 WiFi Switch</h1>"
        "<p><a href=\"/switch/on\"><button class=\"button\">ON</button></a></p>"
        "</body></html>";

    /* Handlers */

    void handleHomeBridge(AsyncWebServerRequest *request)
    {
        String action = request->pathArg(0);

        if (action.equals("on"))
        {
            state::newMessage("Switch ON HomeBridge");
            state::switchOn = true;
            request->send(200, "text/plain", "on");
        }
        else if (action.equals("off"))
        {
            state::newMessage("Switch OFF HomeBridge");
            state::switchOn = false;
            request->send(200, "text/plain", "off");
        }
        else
        {
            state::newMessage("Check stat HomeBridge");
            request->send(200, "text/plain", state::switchOn ? "1" : "0");
        }
    }

    void handleWebUI(AsyncWebServerRequest *request)
    {
        String action = request->pathArg(0);

        if (action.equals("on"))
        {
            state::newMessage("Switch ON WebUI");
            state::switchOn = true;
        }
        else if (action.equals("off"))
        {
            state::newMessage("Switch OFF WebUI");
            state::switchOn = false;
        }

        request->send(200, "text/html", state::switchOn ? webUI_ON : webUI_OFF);
    }

    void notFound(AsyncWebServerRequest *request)
    {
        request->redirect("/switch/status");
    }

    /* Async web server setup */
    
    AsyncWebServer server(80);

    void setup()
    {
        // https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/examples/simple_server/simple_server.ino

        /* HomeBridge */

        server.on("^/homebridge/switch/(on|off|status)$", HTTP_GET, handleHomeBridge);

        /* WebUI */

        server.on("^/switch/(on|off|status)$", HTTP_GET, handleWebUI);

        /* Start */

        server.onNotFound(notFound);
        server.begin();
    }
}
