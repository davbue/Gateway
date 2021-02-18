#include "Leds.hpp"
#include "analogWrite.h"

Device_Leds::Device_Leds(JsonObject &config) 
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

Device_Leds::~Device_Leds()
{
    if(_initialized)
    {
        /* reset Pin */
        ledcDetachPin(_pin);
        pinMode(_pin, INPUT);
    }
}

void Device_Leds::setConfig(JsonObject &config)
{
    /* Validate ID & Type */
    if(!Device::validate(config))
        return;

    Device::setConfig(config);

    if(!config[DEVICE_PIN].isNull())
    {
        if(!config[DEVICE_PIN][0].isNull())
        {
            uint8_t pin = config[DEVICE_PIN][0].as<uint8_t>();

            /* check whether pin has changed or not */
            if(pin != _pin)
            {
                /* reset old pin */
                ledcDetachPin(_pin);
                pinMode(_pin, INPUT);

                /* init new pin */
                _pin = pin;
                pinMode(_pin, OUTPUT);
                digitalWrite(_pin, 0);
            }
        }
    }
}

void Device_Leds::setData(JsonObject &data)
{
    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);

    if(!data[DEVICE_VALUE].isNull())
    {
        _brightness = data[DEVICE_VALUE].as<uint8_t>();
    }
}

void Device_Leds::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    /* get config */
    config[DEVICE_PIN][0] = _pin;
}

void Device_Leds::getData(JsonObject &data)
{
    /* Get Base information */
    Device::getData(data);

    data[DEVICE_VALUE] = _brightness;
}

void Device_Leds::update()
{
    if(_enable)
        analogWrite(_pin, _brightness);
    else
        analogWrite(_pin, 0);
}
