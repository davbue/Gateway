#include "Template.hpp"
/* Include here additional libraries */

Device_Template::Device_Template(JsonObject &config) 
    : Device(config)
{
    /* set additional config for device 

    style:
        if(!config[DEVICE_PIN]["xyz"].isNull())
        {
            _xyz = config[DEVICE_PIN]["xyz"].as<xyz_type>();

            -> init xyz
        }

        ...
    */
}

Device_Template::~Device_Template()
{
    /* free here all used resources
    
        e.g. :

        pins,
        peripheral components (i2c, spi ...),
        memory
        ...
    */
}

void Device_Template::setConfig(JsonObject &config)
{
    /* Validate ID & Type */
    if(!Device::validate(config))
        return;

    Device::setConfig(config);

    /* set additional config for device 

    style:
        xyz_type xyz;

        if(!config[DEVICE_PIN]["xyz"].isNull())
        {
            xyz = config[DEVICE_PIN]["xyz"].as<xyz_type>();

            if(xyz != _xyz)
            {
                free resources for old config

                _xyz = xyz;

                init new config
            }
        }

        ...
    */
}

void Device_Template::setData(JsonObject &data)
{
    /* Validate ID & Type */
    if(!Device::validate(data))
        return;

    Device::setData(data);

    /* set here additional data 
    
    style:

    if(!data[DEVICE_VALUE]["xyz"].isNull())
    {
        _xyz = data[DEVICE_VALUE]["xyz"].as<xyz_type>();
    }

    ...
    
    */
}

void Device_Template::getConfig(JsonObject &config)
{
    /* Get Base infromation */
    Device::getConfig(config);

    /* get here additional config 
    
    style:

    config[DEVICE_PIN]["xyz"] = _xyz
    ...
    
    */
}

void Device_Template::getData(JsonObject &data)
{
    /* Get Base information */
    Device::getData(data);

    /* get here additional data 
    
    style:

    data[DEVICE_VALUE]["xyz"] = _xyz
    ...
    
    */
}

void Device_Template::update()
{
    /* update here the device
    
    style:

    if(_enable)
    {
        turn device on
        get / set data from/to device
    }
    else
    {
        turn device off
    }
    
    */
}
