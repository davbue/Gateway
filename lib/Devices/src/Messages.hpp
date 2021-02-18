#ifndef _MESSAGES_H_
#define _MESSAGES_H_

/* MQTT*/
#define MQTT_MSG_MAX_SIZE (16 * 1024)

/* Server */
#define MQTT_SERVER_IP      "192.168.1.112"
#define MQTT_SERVER_PORT    1883

/* Client */
#define MQTT_CLIENT_USERNAME NULL
#define MQTT_CLIENT_PASSWORD NULL

/* Topics */
#define MQTT_TOPIC_PUB_DATA         "/state/data"
#define MQTT_TOPIC_PUB_CONFIG       "/state/config"
#define MQTT_TOPIC_PUB_AVAILABILITY "/state/availability"

#define MQTT_TOPIC_SUB_DATA         "/update/data"
#define MQTT_TOPIC_SUB_CONFIG       "/update/config"

/* JSON Objects */
/* Gateway JSON-Object Entries*/
#define GATEWAY_ID              "GatewayId"
#define GATEWAY_TIMESTAMP       "Timestamp"
#define GATEWAY_DATA_ENTITIES   "DataEntities"
#define GATEWAY_DEVICE_CONFIGS  "DeviceConfigs"
#define GATEWAY_ONLINE          "Online"

/* Device JSON-Object Entries*/
#define DEVICE_ID       "DeviceId"
#define DEVICE_TYPE_ID  "DeviceTypeId"
#define DEVICE_ENABLE   "Enabled"
#define DEVICE_DELETE   "Delete"
#define DEVICE_PIN      "Pins"
#define DEVICE_VALUE    "Value"

#endif