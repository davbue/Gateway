#ifndef _DEVICE_TYPES_H_
#define _DEVICE_TYPES_H_

#include "ArduinoJson.h"

#include "Base/DeviceBase.hpp"

#include "RGB_Leds/RGB_Led.hpp"
#include "Leds/Leds.hpp"
#include "PowerSwitch/PowerSwitch.hpp"
#include "EnvSensor/EnvSensor.hpp"
#include "AmbLightSensor/AmbLightSensor.hpp"

/* Device Types */
typedef enum 
{
    RGB_Leds            = 1,
    PowerSwitch         = 2,
    Leds                = 150,
    AmbLightSensor      = 4,
    TemperatureSensor   = 3,
    HumiditySensor      = 6,
    PressureSensor      = 7,
    GasResitanceSensor  = 8,
    AltitudeSensor      = 9
}DeviceType_t;

/* Creating new Devices */
Device* createDevice(DeviceType_t type, JsonObject &config);

#endif