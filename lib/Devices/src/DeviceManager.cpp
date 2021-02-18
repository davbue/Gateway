#include "DeviceManager.hpp"
#include "DeviceTypes/DeviceTypes.hpp"
#include "map"

namespace DeviceManager
{
    namespace
    {   
        /* Device List*/
        std::map<String, Device*> _deviceList;

        /* Private Functions */
        /* Check if Device should be removed */
        bool chechForRemoval(JsonObject &jsonObj)
        {
            if(jsonObj[DEVICE_DELETE].isNull())
                return false;

            return jsonObj[DEVICE_DELETE].as<bool>();
        }

        /* Register & unregister Devices */
        void registerDevice(JsonObject &config)
        {
            String key;
            DeviceType_t type;
            Device *device;

            if(config[DEVICE_ID].isNull() || config[DEVICE_TYPE_ID].isNull())
                return;

            key = config[DEVICE_ID].as<String>();
            type = config[DEVICE_TYPE_ID].as<DeviceType_t>();

            device = createDevice(type, config);

            if(device != NULL && !chechForRemoval(config))
            {
                _deviceList.insert(std::pair<String, Device*>(key, device));

                Serial.println("\nDevice Registered:");
                Serial.println("ID = " + key);
                Serial.println("Type = " + String(type));
            }
            else
            {
                Serial.println("\nDevice could not be created:");
            }
        }

        void unregisterDevice(String Key)
        {
            Serial.println("\nDevice unregistered:");
            Serial.println("ID = " + Key);

            delete _deviceList[Key];
            _deviceList.erase(Key);
        }

        /* Validate Key & Type */
        bool validateKey(String key)
        {
            return _deviceList.count(key);
        }

        bool validateType(Device &device, JsonObject &jsonObj)
        {
            StaticJsonDocument<100> doc;
            JsonObject deviceObj;

            if(jsonObj[DEVICE_TYPE_ID].isNull())
                return true;
            
            deviceObj = doc.to<JsonObject>();

            device.getConfig(deviceObj);

            return (deviceObj[DEVICE_TYPE_ID] == jsonObj[DEVICE_TYPE_ID]);
        }
    }
    
    void updateDeviceConfigs(JsonArray &configList)
    {
        uint16_t jsonArrayLength = 0;

        JsonObject  Obj;
        String      Key;

        jsonArrayLength = configList.size();

        /* Iterate every Element in configList */
        for(uint16_t i = 0; i < jsonArrayLength; i++)
        {
            /* get config json-object */
            Obj = configList[i].as<JsonObject>();

            /* get Key */
            if(!Obj[DEVICE_ID].isNull())
                Key = Obj[DEVICE_ID].as<String>();
            else
                continue;
            
            /* check if device list contains device */
            if(validateKey(Key))
            {
                /* Remove Device if needed */
                if(chechForRemoval(Obj))
                {
                    Serial.println("Remove Device: " + Obj[DEVICE_ID].as<String>());
                    unregisterDevice(Key);
                }
                else
                {
                    /* check if device type stayed the same */
                    if(validateType(*_deviceList[Key], Obj))
                    {
                        /* Update Config */
                        _deviceList[Key]->setConfig(Obj);
                    }
                    else
                    {
                        /* Delete old Device & create a new one */
                        unregisterDevice(Key);
                        registerDevice(Obj);
                    }
                }
            }
            else
            {
                /* Create new Device */
                if(!chechForRemoval(Obj))
                    registerDevice(Obj);
            }
            
        }
    }

    void updateDeviceData(JsonArray &dataList)
    {
        uint16_t jsonArrayLength = 0;

        JsonObject  Obj;
        String      Key;

        jsonArrayLength = dataList.size();

        /* Iterate every Element in configList */
        for(uint16_t i = 0; i < jsonArrayLength; i++)
        {
            /* get config json-object */
            Obj = dataList[i].as<JsonObject>();

            /* get Key */
            if(!Obj[DEVICE_ID].isNull())
                Key = Obj[DEVICE_ID].as<String>();
            else
                continue;

            /* check if device list contains device */
            if(validateKey(Key))
            {
                /* check if device type stayed the same */
                if(validateType(*_deviceList[Key], Obj))
                {
                    /* Update data */
                    _deviceList[Key]->setData(Obj);
                }
                else
                {
                    Serial.println("Wrong Type");
                }
                
            }
            else
            {
                Serial.println("Key not Found: " + Key);
            }
        }
    }


    void getDeviceConfigs(JsonArray &configList)
    {
        JsonObject config;

        std::map<String, Device*>::iterator it;
        
        /* Check if Device is empty */
        if(_deviceList.size() == 0)
            return;

        /* Iterate through every device */
        for(it = _deviceList.begin(); it != _deviceList.end(); it++)
        {
            config = configList.createNestedObject();
            it->second->getConfig(config);
        }
    }

    void getDeviceData(JsonArray &dataList)
    {
        JsonObject data;

        std::map<String, Device*>::iterator it;
        
        /* Check if Device is empty */
        if(_deviceList.size() == 0)
            return;

        /* Iterate through every device */
        for(it = _deviceList.begin(); it != _deviceList.end(); it++)
        {
            if(it->second->isEnabled())
            {
                data = dataList.createNestedObject();
                it->second->getData(data);
            }
        }
    }


    void updateDevices(void)
    {
        std::map<String, Device*>::iterator it;
        
        /* Check if Device is empty */
        if(_deviceList.size() == 0)
            return;

        /* Iterate through every device */
        for(it = _deviceList.begin(); it != _deviceList.end(); it++)
        {
            it->second->update();
        }
    }
}

