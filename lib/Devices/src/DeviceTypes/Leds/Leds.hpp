#ifndef _DEVICE_LEDS_H_
#define _DEVICE_LEDS_H_

#include "Arduino.h"
#include "ArduinoJson.h"

#include "DeviceTypes/Base/DeviceBase.hpp"

class Device_Leds : public Device
{
    private:
        uint8_t _pin;
        uint8_t _brightness;

    public:
        Device_Leds(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        void getData(JsonObject &data);

        void update(void);

        ~Device_Leds();
};

#endif