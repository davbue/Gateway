#include "Wlan.hpp"
#include "MQTT_SettingsPage.hpp"

namespace Wlan
{
    /* Private Namespace */
    namespace
    {
        /* Autoconnect */
        WebServer Server;
        AutoConnect Portal(Server);
        AutoConnectConfig PortalConfig;

        void rootPage(void)
        {
            char content[] = "Hello World";
            Server.send(200, "text/plain", content);
        }

        /* Wifi Client */
        WiFiClient net;
    }

    void connect(bool newConnection)
    {
        /* Create Access Point SSID */
        char name[30];
        sprintf(name, "Esp32-%12llx", ESP.getEfuseMac());

        /* Set Settings for Autoconnec */
        PortalConfig.autoReconnect = true;
        PortalConfig.hostName = name;
        PortalConfig.apid = name;
        PortalConfig.immediateStart = newConnection;
        PortalConfig.boundaryOffset = MQTT_SETTINGS_PAGE::getUsedEEPROMSize();

        Serial.println("Hostname: " + PortalConfig.hostName);
        Serial.println("AP SSID: " + PortalConfig.apid);
        Serial.println("Pw: " + PortalConfig.password);

        /* Turn on Autoconnect Server */
        Server.on("/", rootPage);
        Portal.config(PortalConfig);

        MQTT_SETTINGS_PAGE::loadPage(Portal);
        MQTT_SETTINGS_PAGE::setHandlers(Portal);

        if(Portal.begin())
        {
            /* If connected print SSID + IP */
            Serial.println(WiFi.SSID());
            Serial.println(WiFi.localIP().toString());
            Serial.println(WiFi.gatewayIP().toString());
        }

        /* Check if Wifi really is connected */
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
        }

        Serial.println("Wifi Connected");
    }

    WiFiClient* getWifiClient(void)
    {
        return &net;
    }

    wl_status_t getStatus(void)
    {
        return WiFi.status();
    }

    void loop(void)
    {
        Portal.handleClient();
    }
}



