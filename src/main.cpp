#include <Arduino.h>
#include "Wlan.hpp"
#include "Gateway.hpp"
#include "Messages.hpp"
#include "MQTT_SettingsPage.hpp"

IPAddress broker;

#define CONFIG_BUTTON_PIN 39

void setup() {
  /* init Serial Port */
  Serial.begin(115200);

  pinMode(CONFIG_BUTTON_PIN, INPUT_PULLUP);

  /* Connect to WiFi */
  Wlan::connect(!digitalRead(CONFIG_BUTTON_PIN));
  
  /* Init Gateway */
  Gateway::init(MQTT_SETTINGS_PAGE::getBrokerIP(), MQTT_SETTINGS_PAGE::getBrokerPort());
}

void loop() {
  Gateway::loop();
}