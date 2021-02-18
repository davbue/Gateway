#ifndef _DEVICE_TEMPLATE_SWITCH_H_
#define _DEVICE_TEMPLATE_SWITCH_H_

#include "Arduino.h"
#include "ArduinoJson.h"
#include "hp_BH1750.h"

#include "DeviceTypes/Base/DeviceBase.hpp"

class Device_AmbLightSensor : public Device
{
    private:
        hp_BH1750 _sensor;

        uint8_t _sda;
        uint8_t _scl;

        float  _lux;

    public:
        Device_AmbLightSensor(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        void getData(JsonObject &data);

        void update(void);

        ~Device_AmbLightSensor();
};

#endif