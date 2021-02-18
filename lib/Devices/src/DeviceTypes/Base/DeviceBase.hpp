#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Messages.hpp"

/* Base Class */
class Device
{
    protected:
        bool _enable        = false;
        bool _initialized   = false;

        bool validate(JsonObject &jsonObj);

    public:
        Device(JsonObject &config);
        virtual ~Device() = 0;

        bool isEnabled(void);

        virtual void setConfig(JsonObject &config);
        virtual void setData(JsonObject &data);

        virtual void getConfig(JsonObject &config);
        virtual void getData(JsonObject &data);

        virtual void update(void) = 0;

    private:
        String   _id;
        uint32_t _type;
};

#endif