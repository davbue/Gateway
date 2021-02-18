#ifndef _MQTT_SETTINGS_PAGE
#define _MQTT_SETTINGS_PAGE

#include "Arduino.h"
#include "AutoConnect.h"

namespace MQTT_SETTINGS_PAGE
{
    void loadPage(AutoConnect &portal);
    void setHandlers(AutoConnect &portal);
    
    IPAddress getBrokerIP(void);
    uint16_t getBrokerPort(void);
    uint8_t getUsedEEPROMSize(void);
}

#endif