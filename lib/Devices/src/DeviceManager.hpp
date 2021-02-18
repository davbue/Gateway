#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "Arduino.h"
#include "ArduinoJson.h"

namespace DeviceManager
{
    /* Update Device Configs & Data */
    void updateDeviceConfigs(JsonArray &configList);
    void updateDeviceData(JsonArray &dataList);

    /* Get Device Configs & Data */
    void getDeviceConfigs(JsonArray &configList);
    void getDeviceData(JsonArray &dataList);

    /* Update Devices  (apply data/get new data) */
    void updateDevices(void);
}

#endif