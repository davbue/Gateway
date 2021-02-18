#ifndef _DEVICE_POWER_SWITCH_H_
#define _DEVICE_POWER_SWITCH_H_

#include "Arduino.h"
#include "ArduinoJson.h"

#include "DeviceTypes/Base/DeviceBase.hpp"

class Device_Power_Switch : public Device
{
    private:
        uint8_t _pin;

    public:
        Device_Power_Switch(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        void getData(JsonObject &data);

        void update(void);

        ~Device_Power_Switch();
};

#endif