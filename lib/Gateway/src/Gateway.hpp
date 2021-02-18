#ifndef _GATEWAY_H_
#define _GATEWAY_H_

#include "Arduino.h"
#include "PubSubClient.h"

namespace Gateway
{
    void init(IPAddress broker, uint16_t port);
    void loop(void);
}

#endif