#include "MQTT_SettingsPage.hpp"
#include "EEPROM.h"

const char AUX_MQTT_SETTINGS[] PROGMEM = 
R"(
    [
        {
            "title": "MQTT Settings",
            "uri": "/mqtt_settings",
            "menu": true,
            "element": [
                {
                    "name": "ipLabel",
                    "type": "ACText",
                    "value": "Broker IP"
                },
                {
                    "name": "ip",
                    "type": "ACInput",
                    "global": true
                },
                {
                    "name": "portLabel",
                    "type": "ACText",
                    "value": "Broker Port"
                },
                {
                    "name": "port",
                    "type": "ACInput",
                    "global": true
                },
                {
                    "name": "save",
                    "type": "ACSubmit",
                    "value": "Save",
                    "uri": "/mqtt_save"
                }
            ]
        },
        {
            "title": "MQTT Settings",
            "uri": "/mqtt_save",
            "menu": false,
            "element": [
                {
                    "name": "ipLabel",
                    "type": "ACText",
                    "value": "Broker IP"
                },
                {
                    "name": "ip",
                    "type": "ACInput",
                    "format": "ip: %s",
                    "posterior": "br",
                    "global": true
                },
                {
                    "name": "portLabel",
                    "type": "ACText",
                    "value": "Broker Port"
                },
                {
                    "name": "port",
                    "type": "ACInput",
                    "format": "port: %s",
                    "posterior": "br",
                    "global": true
                },
                {
                    "name": "save",
                    "type": "ACSubmit",
                    "value": "Save",
                    "uri": "/mqtt_save"
                }
            ]
        }
    ]
)";

namespace MQTT_SETTINGS_PAGE
{
    namespace 
    {
        #define EEPROM_SIZE 6

        String loadBrokerIp(AutoConnectAux& page, PageArgument& args)
        {
            String ip = "";
            String port = "";

            EEPROM.begin(EEPROM_SIZE);
            
            ip = String(EEPROM.read(0)) + "." + String(EEPROM.read(1)) + "." + String(EEPROM.read(2)) + "." + String(EEPROM.read(3));

            port = String(EEPROM.readUShort(4));

            EEPROM.end();

            page["ip"].value    = ip;
            page["port"].value  = port;

            return String();
        }

        String saveBrokerIp(AutoConnectAux& page, PageArgument& args)
        {
            String ip = "";
            String port = "";

            IPAddress addr;

            ip = page["ip"].value;
            port = page["port"].value;

            addr.fromString(ip);

            EEPROM.begin(EEPROM_SIZE);

            EEPROM.write(0, addr[0]);
            EEPROM.write(1, addr[1]);
            EEPROM.write(2, addr[2]);
            EEPROM.write(3, addr[3]);

            EEPROM.writeUShort(4, (uint16_t)port.toInt());
            
            EEPROM.commit();

            EEPROM.end();

            Serial.println(ip);
            Serial.println(port);

            return String();
        }
    }
    

    void loadPage(AutoConnect &portal)
    {
        portal.load(AUX_MQTT_SETTINGS);
    }

    void setHandlers(AutoConnect &portal)
    {
        portal.on("/mqtt_settings", loadBrokerIp);
        portal.on("/mqtt_save", saveBrokerIp);
    }
    
    IPAddress getBrokerIP(void)
    {
        EEPROM.begin(EEPROM_SIZE);

        String ip = String(EEPROM.read(0)) + "." + String(EEPROM.read(1)) + "." + String(EEPROM.read(2)) + "." + String(EEPROM.read(3));

        EEPROM.end();

        IPAddress addr;

        addr.fromString(ip);

        return addr;
    }

    uint16_t getBrokerPort(void)
    {
        uint16_t port = 0;

        EEPROM.begin(EEPROM_SIZE);

        port = EEPROM.readUShort(4);

        EEPROM.end();

        return port;
    }

    uint8_t getUsedEEPROMSize(void)
    {
        return EEPROM_SIZE;
    }
}