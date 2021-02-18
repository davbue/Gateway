#include "DeviceTypes.hpp"

Device* createDevice(DeviceType_t type, JsonObject &config)
{
    Device *dev = NULL;

    switch (type)
    {
        case DeviceType_t::RGB_Leds:            dev = new Device_RGB_LEDs(config);              break;
        case DeviceType_t::PowerSwitch:         dev = new Device_Power_Switch(config);          break;
        case DeviceType_t::Leds:                dev = new Device_Leds(config);                  break;
        case DeviceType_t::AmbLightSensor:      dev = new Device_AmbLightSensor(config);        break;
        case DeviceType_t::TemperatureSensor:   dev = new Device_Temperature_Sensor(config);    break;
        case DeviceType_t::HumiditySensor:      dev = new Device_Humidity_Sensor(config);       break;
        case DeviceType_t::PressureSensor:      dev = new Device_Pressure_Sensor(config);       break;
        case DeviceType_t::GasResitanceSensor:  dev = new Device_GasResistance_Sensor(config);  break;
        case DeviceType_t::AltitudeSensor:      dev = new Device_Altitude_Sensor(config);       break;

        default:                            dev = NULL;                                 break;
    }

    return dev;
}