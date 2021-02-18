#ifndef _DEVICE_RGB_LEDS_H_
#define _DEVICE_RGB_LEDS_H_

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Adafruit_NeoPixel.h"

#include "DeviceTypes/Base/DeviceBase.hpp"

class Device_RGB_LEDs : public Device
{
    private:
        Adafruit_NeoPixel *_strip;

        bool _initialized;

        uint8_t _pin;
        uint16_t _nbrLeds;
        uint8_t _brightness;

        uint8_t _red;
        uint8_t _green;
        uint8_t _blue;

    public:
        Device_RGB_LEDs(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        void getData(JsonObject &data);

        void update(void);

        ~Device_RGB_LEDs(void);
};

#endif