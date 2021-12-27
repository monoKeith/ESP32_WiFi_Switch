#include "server.h"

namespace server
{

    void setup()
    {
        // Start Wi-Fi
        WiFi.begin(ssid, password);
    }

    void update()
    {
        // Update WiFi status
        state::wirelessConnected = (WiFi.status() == WL_CONNECTED);
    }

}