#ifndef _WLAN_H_
#define _WLAN_H_

#include "Arduino.h"
#include "SPIFFS.h"
#include "WiFi.h"
#include "WebServer.h"
#include "HTTPClient.h"
#include "HTTPUpdate.h"
#include "AutoConnect.h"
#include "AutoConnectCredential.h"
#include "DNSServer.h"
#include "WiFiClient.h"
#include "Esp.h"
#include "Ticker.h"

namespace Wlan
{
    void connect(bool newConnection);
    WiFiClient* getWifiClient(void);
    wl_status_t getStatus(void);

    void loop(void);
}

#endif