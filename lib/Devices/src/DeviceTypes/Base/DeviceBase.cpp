#include "DeviceBase.hpp"

Device::Device(JsonObject &config)
{
    if(!config[DEVICE_ID].isNull())
        _id = config[DEVICE_ID].as<String>();

    if(!config[DEVICE_TYPE_ID].isNull())
        _type = config[DEVICE_TYPE_ID].as<uint32_t>();

    if(!config[DEVICE_ENABLE].isNull())
        _enable = config[DEVICE_ENABLE].as<bool>();
}

bool Device::validate(JsonObject &jsonObj)
{
    bool res = true;

    if(!jsonObj[DEVICE_ID].isNull())
    {
        if(jsonObj[DEVICE_ID].as<String>() != _id)
            res = false;
    }

    if(!jsonObj[DEVICE_TYPE_ID].isNull())
    {
        if(jsonObj[DEVICE_TYPE_ID].as<uint32_t>() != _type)
            res = false;
    }

    return res;
}

bool Device::isEnabled(void)
{
    return _enable;
}

void Device::setConfig(JsonObject &config)
{
    if(!config[DEVICE_ENABLE].isNull())
        _enable = config[DEVICE_ENABLE].as<bool>();
}

void Device::setData(JsonObject &data)
{
    
}

void Device::getConfig(JsonObject &config)
{
    config[DEVICE_ID]       = _id;
    config[DEVICE_TYPE_ID]  = _type;
    config[DEVICE_ENABLE]    = _enable;
}

void Device::getData(JsonObject &data)
{
    data[DEVICE_ID]        = _id;
    data[DEVICE_TYPE_ID]   = _type;
}

Device::~Device()
{
    
}