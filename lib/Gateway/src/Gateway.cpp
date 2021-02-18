#include "Gateway.hpp"
#include "Wlan.hpp"
#include "DeviceManager.hpp"
#include "Messages.hpp"

namespace Gateway
{
    /* Private Namespace */
    namespace
    {
        IPAddress _broker;
        PubSubClient *_client;

        String _gwLWTTopic;

        String _gwSubConfigTopic;
        String _gwSubDataTopic;

        String _gwPubConfigTopic;
        String _gwPubDataTopic;

        bool _gwConfigUpdated;

        String _id;

        void MQTT_CB(char *topic, byte *payload, unsigned int length)
        {
            JsonObject Obj;
            JsonArray list;
            DynamicJsonDocument doc(MQTT_MSG_MAX_SIZE);

            payload[length] = '\0';

            String Topic = String(topic);
            String Payload = String((char*)payload);

            Serial.println("\nTopic: " + Topic);
            Serial.println("Payload: " + Payload);
            Serial.println("length: " + String(length));

            if((Topic != _gwSubConfigTopic) && (Topic != _gwSubDataTopic))
            {
                Serial.printf("\nWrong Topic received!\n");
                return;
            }

            /* Deserialize the document */
            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.c_str());
                return;
            }
            else
            {
                Serial.println("\nReceived Payload:");
                /* Check transmittet id */
                if(!doc[GATEWAY_ID].isNull())
                {
                    Serial.println("\nID: " + doc[GATEWAY_ID].as<String>());

                    if(doc[GATEWAY_ID].as<String>() != _id)
                        return;
                }
                else
                {
                    Serial.println("No Gateway ID received!");
                    return;
                }

                if(Topic == _gwSubConfigTopic)
                {
                    /* Get Device Configs */
                    if(!doc[GATEWAY_DEVICE_CONFIGS].isNull())
                    {
                        Serial.println("\nConfig:\n" + doc[GATEWAY_DEVICE_CONFIGS].as<String>());
                        list = doc[GATEWAY_DEVICE_CONFIGS].as<JsonArray>();
                        DeviceManager::updateDeviceConfigs(list);

                        _gwConfigUpdated = true;
                    }
                }
                else if(Topic == _gwSubDataTopic)
                {
                    /* Get Device Data */
                    if(!doc[GATEWAY_DATA_ENTITIES].isNull())
                    {
                        Serial.println("\nData:\n" + doc[GATEWAY_DATA_ENTITIES].as<String>());
                        list = doc[GATEWAY_DATA_ENTITIES].as<JsonArray>();
                        DeviceManager::updateDeviceData(list);
                    }
                }
            }
            
        }

        void MQTT_Push(String &topic, DynamicJsonDocument &doc)
        {
            char *payload;
            uint16_t payloadLength = 0; 

            /* reserve memory for serialization */
            payload = (char*)malloc(MQTT_MSG_MAX_SIZE);

            serializeJson(doc, payload, MQTT_MSG_MAX_SIZE);

            payloadLength = String(payload).length();

            /* Publish document */
            if(!_client->publish(topic.c_str(), (uint8_t*)payload, payloadLength))
            {
                Serial.println("Falied to publish. Msg: " + String(_client->getWriteError()));
            }

            free(payload);
        }

        void MQTT_Push_Data(void)
        {
            JsonArray data;
            DynamicJsonDocument doc(MQTT_MSG_MAX_SIZE);

            /* set Gateway ID & Timestamp */
            doc[GATEWAY_ID]           = _id;
            doc[GATEWAY_TIMESTAMP]    = millis();

            data = doc.createNestedArray(GATEWAY_DATA_ENTITIES);
            DeviceManager::getDeviceData(data);

            MQTT_Push(_gwPubDataTopic, doc);
        }

        void MQTT_Push_Config(void)
        {
            JsonArray config;
            DynamicJsonDocument doc(MQTT_MSG_MAX_SIZE);

            /* set Gateway ID & Timestamp */
            doc[GATEWAY_ID]           = _id;
            doc[GATEWAY_TIMESTAMP]    = millis();

            config = doc.createNestedArray(GATEWAY_DEVICE_CONFIGS);
            DeviceManager::getDeviceConfigs(config);

            MQTT_Push(_gwPubConfigTopic, doc);

            _gwConfigUpdated = false;
        }

        String MQTT_Create_LWT_Msg(bool online)
        {
            StaticJsonDocument<128> doc;

            char jsonBuffer[128];
    
            doc[GATEWAY_ID] = _id;
            doc[GATEWAY_ONLINE] = online;

            serializeJson(doc, jsonBuffer);

            return String(jsonBuffer);
        }

        void MQTTReconnect(void)
        {
            uint8_t count = 0;

            /* Check if Wifi is Connected */
            Serial.printf("\nchecking wifi");
            while (Wlan::getStatus() != WL_CONNECTED) {
                Serial.print(".");
                delay(1000);
                count++;
                if(count++ > 5)
                {
                Serial.printf("\nwifi not connected!\n");
                return;
                }
            }

            count = 0;

            Serial.printf("\nconnecting to MQTT Broker");
            while (!_client->connect(_id.c_str(), _gwLWTTopic.c_str(), 2, true, MQTT_Create_LWT_Msg(false).c_str())) {
                Serial.print(".");
                delay(1000);
                if(count++ > 5)
                {
                Serial.printf("\nconnection to broker failed\n");
                return;
                }
            }

            Serial.println("\nconnected!");

            _client->subscribe(_gwSubConfigTopic.c_str());
            _client->subscribe(_gwSubDataTopic.c_str());

            
            /* set online flag to true when connection */
            _client->publish(_gwLWTTopic.c_str(), MQTT_Create_LWT_Msg(true).c_str(), true);
        }
    }

    void init(IPAddress broker, uint16_t port)
    {
        char gwID[30];
        sprintf(gwID, "Esp32-%12llx", ESP.getEfuseMac());

        /* broker ip address */
        _broker = broker;

        _gwConfigUpdated = false;

        /* create gateway id */
        _id = String(gwID);

        /* set gateway topics */
        _gwLWTTopic = _id + MQTT_TOPIC_PUB_AVAILABILITY;

        _gwSubConfigTopic = _id + MQTT_TOPIC_SUB_CONFIG;
        _gwSubDataTopic   = _id + MQTT_TOPIC_SUB_DATA;

        _gwPubConfigTopic = _id + MQTT_TOPIC_PUB_CONFIG;
        _gwPubDataTopic = _id + MQTT_TOPIC_PUB_DATA;

        /* init mqtt client */
        _client = new PubSubClient(*Wlan::getWifiClient());
        _client->setServer(_broker, port);
        _client->setCallback(MQTT_CB);
        _client->setBufferSize(MQTT_MSG_MAX_SIZE);
        _client->setKeepAlive(10);

        Serial.println("Gateway Initialized!");
    }

    void loop(void)
    {
        uint32_t start;

        /* Try to reconnect to broker */
        while(!_client->connected() || Wlan::getStatus() != WL_CONNECTED)
            MQTTReconnect();

        start = millis();

        /* Update Devices */
        DeviceManager::updateDevices();

        /* send Config if updated */
        if(_gwConfigUpdated)
            MQTT_Push_Config();

        /* Send data */
        MQTT_Push_Data();

        _client->loop();

        /* make sure, that data is only published every second */
        delay(1000 - (millis() - start));

        Wlan::loop();
    }
}