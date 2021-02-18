#ifndef _DEVICE_TEMPLATE_SWITCH_H_
#define _DEVICE_TEMPLATE_SWITCH_H_

#include "Arduino.h"
#include "ArduinoJson.h"
/* Include here additional libraries */

#include "DeviceTypes/Base/DeviceBase.hpp"

/* Change Classname/Constructor/Destructor to: Device_XYZ */
class Device_Template : public Device
{
    private:
        /* device data */

    public:
        Device_Template(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        void getData(JsonObject &data);

        void update(void);

        ~Device_Template();
};

#endif