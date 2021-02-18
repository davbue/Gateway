#include "EnvSensor.hpp"
#include "analogWrite.h"

#define SEALEVELPRESSURE_HPA 1013.25
#define I2C_FREQ             100000

/*Base Class*/

Device_Env_Sensor::Device_Env_Sensor(JsonObject &config) 
    : Device(config)
{
    if(config[DEVICE_PIN][0].isNull() || config[DEVICE_PIN][1].isNull())
    {
        config[DEVICE_DELETE] = true;
        return;
    }

    _sda = config[DEVICE_PIN][0].as<uint8_t>();
    _scl = config[DEVICE_PIN][1].as<uint8_t>();

    if(!Wire.begin(_sda, _scl, I2C_FREQ))
    {
        config[DEVICE_DELETE] = true;
        return;
    }

    if(!_sensor.begin())
    {
       Serial.println("no BME680 Sensor found");
       config[DEVICE_DELETE] = true;
       return;
    }

    _sensor.setHumidityOversampling(BME680_OS_8X);
    _sensor.setPressureOversampling(BME680_OS_2X);
    _sensor.setTemperatureOversampling(BME680_OS_4X);
    _sensor.setIIRFilterSize(BME680_FILTER_SIZE_3);

    _temperature     = 0;
    _humidity        = 0;
    _pressure        = 0;
    _gasResistance   = 0;
    _altitude        = 0;

    _initialized = true;
}

Device_Env_Sensor::~Device_Env_Sensor()
{

}

void Device_Env_Sensor::setConfig(JsonObject &config)
{
    uint8_t pin;

    /* Validate ID & Type */
    if(!Device::validate(config))
        return;

    Device::setConfig(config);

    if(!config[DEVICE_PIN][0].isNull())
    {
        pin = config[DEVICE_PIN][0].as<uint8_t>();

        if(pin != _sda)
        {
            if(Wire.begin(pin, _scl, I2C_FREQ))
                _sda = pin;
        }
    }

    if(!config[DEVICE_PIN][1].isNull())
    {
        pin = config[DEVICE_PIN][1].as<uint8_t>();

        if(pin != _scl)
        {
            if(Wire.begin(_sda, pin, I2C_FREQ))
                _scl = pin;
        }
    }
}

void Device_Env_Sensor::setData(JsonObject &data)
{
    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);
}

void Device_Env_Sensor::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    config[DEVICE_PIN][0] = _sda;
    config[DEVICE_PIN][1] = _scl;
}

void Device_Env_Sensor::getData(JsonObject &data)
{
    /* Get Base information */
    Device::getData(data);
}

void Device_Env_Sensor::update()
{
    if(_enable)
    {
        if(Wire.begin(_sda, _scl, I2C_FREQ))
        {
            if(_sensor.performReading())
            {
                _temperature    = _sensor.temperature;
                _humidity       = _sensor.humidity;
                _pressure       = _sensor.pressure;
                _gasResistance  = _sensor.gas_resistance;
                _altitude       = _sensor.readAltitude(SEALEVELPRESSURE_HPA);
            }
        }
    }
    else
    {
        _temperature     = 0;
        _humidity        = 0;
        _pressure        = 0;
        _gasResistance   = 0;
        _altitude        = 0;
    }
}

/* Derived Sensors */
Device_Temperature_Sensor::Device_Temperature_Sensor(JsonObject &config)
    : Device_Env_Sensor(config)
{
    
}

void Device_Temperature_Sensor::getData(JsonObject &data)
{
    Device_Env_Sensor::getData(data);
    data[DEVICE_VALUE] = _temperature;
}

Device_Humidity_Sensor::Device_Humidity_Sensor(JsonObject &config)
    : Device_Env_Sensor(config)
{
    
}

void Device_Humidity_Sensor::getData(JsonObject &data)
{
    Device_Env_Sensor::getData(data);
    data[DEVICE_VALUE] = _humidity;
}

Device_Pressure_Sensor::Device_Pressure_Sensor(JsonObject &config)
    : Device_Env_Sensor(config)
{
    
}

void Device_Pressure_Sensor::getData(JsonObject &data)
{
    Device_Env_Sensor::getData(data);
    data[DEVICE_VALUE] = _pressure;
}

Device_GasResistance_Sensor::Device_GasResistance_Sensor(JsonObject &config)
    : Device_Env_Sensor(config)
{
    
}

void Device_GasResistance_Sensor::getData(JsonObject &data)
{
    Device_Env_Sensor::getData(data);
    data[DEVICE_VALUE] = _gasResistance;
}

Device_Altitude_Sensor::Device_Altitude_Sensor(JsonObject &config)
    : Device_Env_Sensor(config)
{
    
}

void Device_Altitude_Sensor::getData(JsonObject &data)
{
    Device_Env_Sensor::getData(data);
    data[DEVICE_VALUE] = _altitude;
}