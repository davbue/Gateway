#include "AmbLightSensor.hpp"

#define I2C_FREQ 100000

Device_AmbLightSensor::Device_AmbLightSensor(JsonObject &config) 
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

   /* init sensor */
   if(!_sensor.begin(BH1750_TO_GROUND))
   {
       /* delete device if no sensor is found */
       Serial.println("No BH1750 Chip found!");
       config[DEVICE_DELETE] = true;
   }

   _lux = 0;

   _initialized = true;
}

Device_AmbLightSensor::~Device_AmbLightSensor()
{

}

void Device_AmbLightSensor::setConfig(JsonObject &config)
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

void Device_AmbLightSensor::setData(JsonObject &data)
{
    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);
}

void Device_AmbLightSensor::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    config[DEVICE_PIN][0] = _sda;
    config[DEVICE_PIN][1] = _scl;
}

void Device_AmbLightSensor::getData(JsonObject &data)
{
    /* Get Base information */
    Device::getData(data);

    data[DEVICE_VALUE] = _lux;
}

void Device_AmbLightSensor::update()
{
    if(_enable)
    {
        if(Wire.begin(_sda, _scl, I2C_FREQ))
        {
            _sensor.start();
            _lux = _sensor.getLux();
        }
    }
    else
    {
        _lux = 0;
    }
}
