#ifndef _DEVICE_TEMP_SENSOR_H_
#define _DEVICE_TEMP_SENSOR_H_

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME680.h"

#include "DeviceTypes/Base/DeviceBase.hpp"

class Device_Env_Sensor : public Device
{
    private:
        /* Sensor */
        Adafruit_BME680 _sensor;

        /* Pins */
        uint8_t _sda;
        uint8_t _scl;

    protected:
        /* Sensor data */
        float _temperature;
        float _humidity;
        float _altitude;
        float _pressure;
        float _gasResistance;

    public:
        Device_Env_Sensor(JsonObject &config);

        void setConfig(JsonObject &config);
        void setData(JsonObject &data);

        void getConfig(JsonObject &config);
        virtual void getData(JsonObject &data);

        void update(void);

        ~Device_Env_Sensor();
};

class Device_Temperature_Sensor : public Device_Env_Sensor
{
    public:
        Device_Temperature_Sensor(JsonObject &config);

        void getData(JsonObject &data);
};

class Device_Humidity_Sensor : public Device_Env_Sensor
{
    public:
        Device_Humidity_Sensor(JsonObject &config);

        void getData(JsonObject &data);
};

class Device_Pressure_Sensor : public Device_Env_Sensor
{
    public:
        Device_Pressure_Sensor(JsonObject &config);

        void getData(JsonObject &data);
};

class Device_GasResistance_Sensor : public Device_Env_Sensor
{
    public:
        Device_GasResistance_Sensor(JsonObject &config);

        void getData(JsonObject &data);
};

class Device_Altitude_Sensor : public Device_Env_Sensor
{
    public:
        Device_Altitude_Sensor(JsonObject &config);

        void getData(JsonObject &data);
};

#endif