#include "PowerSwitch.hpp"

Device_Power_Switch::Device_Power_Switch(JsonObject &config) 
    : Device(config)
{
    /* Initialize pin of Led */
    if(config[DEVICE_PIN][0].isNull())
    {
        config[DEVICE_DELETE] = true;
        return;
    }

    _pin = config[DEVICE_PIN][0].as<uint8_t>();

    /* init pin */
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, 0);

    _initialized = true;
}

Device_Power_Switch::~Device_Power_Switch()
{
    if(_initialized)
    {
        /* reset Pin */
        pinMode(_pin, INPUT);
    }
}

void Device_Power_Switch::setConfig(JsonObject &config)
{
    /* Validate ID & Type */
    if(!Device::validate(config))
        return;

    Device::setConfig(config);

    if(!config[DEVICE_PIN][0].isNull())
    {
        uint8_t pin = config[DEVICE_PIN][0].as<uint8_t>();

        /* check whether pin has changed or not */
        if(pin != _pin)
        {
            /* reset old pin */
            pinMode(_pin, INPUT);

            /* init new pin */
            _pin = pin;
            pinMode(_pin, OUTPUT);
            digitalWrite(_pin, 0);
        }
    }
}

void Device_Power_Switch::setData(JsonObject &data)
{
    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);
}

void Device_Power_Switch::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    /* get config */
    config[DEVICE_PIN][0] = _pin;
}

void Device_Power_Switch::getData(JsonObject &data)
{
    /* Get Base information */
    Device::getData(data);
}

void Device_Power_Switch::update()
{
    if(_enable)
        digitalWrite(_pin, 1);
    else
        digitalWrite(_pin, 0);
}
