#include "RGB_Led.hpp"

Device_RGB_LEDs::Device_RGB_LEDs(JsonObject &config) 
    : Device(config)
{
    if(config[DEVICE_PIN][0].isNull() /*|| config[DEVICE_PIN]["nbrLeds"].isNull()*/)
    {
        config[DEVICE_DELETE] = true;
        return;
    }

    //_nbrLeds = config[DEVICE_PIN]["nbrLeds"].as<uint16_t>();
    _pin = config[DEVICE_PIN][0].as<uint8_t>();
    _nbrLeds = 10;

    _strip = new Adafruit_NeoPixel(_nbrLeds, _pin, NEO_GRB + NEO_KHZ800);

    _strip->begin();
    _strip->setBrightness(100);
    _strip->show();

    _red = 0xFF;
    _green = 0xFF;
    _blue = 0xFF;

    _brightness = 100;

    _initialized = true;
}

Device_RGB_LEDs::~Device_RGB_LEDs()
{
    if(_initialized)
    {
        _strip->clear();
        _strip->show();
        delete _strip;
    }
}

void Device_RGB_LEDs::setConfig(JsonObject &config)
{
    uint8_t pin;
    uint16_t nLeds;

    /* Validate ID & Type */
    if(!Device::validate(config))
        return;

    Device::setConfig(config);

    if(!config[DEVICE_PIN][0].isNull())
    {
        pin = config[DEVICE_PIN][0].as<uint8_t>();

        if(pin != _pin)
        {
            _strip->clear();
            _strip->show();

            _pin = pin;
            _strip->setPin(_pin);
        }
    }

    _nbrLeds = 10;

    // if(!config[DEVICE_PIN]["nbrLeds"].isNull())
    // {
    //     nLeds = config[DEVICE_PIN]["nbrLeds"].as<uint16_t>();

    //     if(nLeds != _nbrLeds)
    //     {
    //         if(nLeds < _nbrLeds)
    //         {
    //             /* Clear unused leds */
    //             for(uint16_t i = nLeds; i < _nbrLeds; i++)
    //                 _strip->setPixelColor(i, 0, 0, 0);

    //             _strip->show();
    //         }

    //         _nbrLeds = nLeds;
    //         _strip->updateLength(_nbrLeds);
    //     }
    // }


}

void Device_RGB_LEDs::setData(JsonObject &data)
{
    JsonArray rgbData;
    uint16_t size;
    
    uint32_t color;
    uint8_t r, g, b;

    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);

    /* Change Data */

    if(!data[DEVICE_VALUE].isNull())
    {
        _brightness = data[DEVICE_VALUE].as<uint8_t>();
        _strip->setBrightness(_brightness);
    }
/*
    if(data[DEVICE_VALUE]["rgb"].isNull())
        return;

    rgbData = data[DEVICE_VALUE]["rgb"].as<JsonArray>();

    size = (_nbrLeds < rgbData.size()) ? _nbrLeds : rgbData.size();

    for(uint16_t i = 0; i < size; i++)
    {
        color = _strip->getPixelColor(i);

        r = (color >> 16) & 0xFF;
        g = (color >> 8) & 0xFF;
        b = (color >> 0) & 0xFF;

        if(!rgbData[i]["red"].isNull())
            r = rgbData[i]["red"].as<uint8_t>();

        if(!rgbData[i]["green"].isNull())
            g = rgbData[i]["green"].as<uint8_t>();

        if(!rgbData[i]["blue"].isNull())
            b = rgbData[i]["blue"].as<uint8_t>();

        _strip->setPixelColor(i, r, g, b);
    }*/
}

void Device_RGB_LEDs::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    config[DEVICE_PIN][0] = _pin;
    //config[DEVICE_PIN]["nbrLeds"] = _nbrLeds;
}

void Device_RGB_LEDs::getData(JsonObject &data)
{
    JsonArray rgbData;

    /* Get Base information */
    Device::getData(data);

    /* Get Data */
   /* rgbData = data[DEVICE_VALUE].createNestedArray("rgb");

    for(uint16_t i = 0; i < _nbrLeds; i++)
    {
        rgbData[i]["red"] = (_strip->getPixelColor(i) >> 16) & 0xFF;
        rgbData[i]["green"] = (_strip->getPixelColor(i) >> 8) & 0xFF;
        rgbData[i]["blue"] = (_strip->getPixelColor(i) >> 0) & 0xFF;
    }*/
    data[DEVICE_VALUE] = _brightness;
}

void Device_RGB_LEDs::update()
{
    if(_enable)
    {
        _strip->fill(_strip->Color(_red, _green, _blue), 0, _nbrLeds);
        _strip->setBrightness(_brightness);
    }
    else
    {
        _strip->fill(0, 0, _nbrLeds);
        _strip->setBrightness(0);
    }

    _strip->show();
}
