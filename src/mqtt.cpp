#include "secrets.h"
#include <arduino.h>
#include <AsyncMqttClient.h>

#define QOS_1_AT_LEAST_ONCE 1
#define RETAIN true
#define BUFFER_LEN 64
char buffer[BUFFER_LEN];
const char * configuration_payload = R"END(
{
  "name": "Porch Lights Mode",
  "command_topic": "homeassistant/select/porch_lights_mode/set",
  "state_topic": "homeassistant/select/porch_lights_mode/state",
  "options": ["Option 1", "Option 2", "Option 3"],
  "unique_id": "porch_lights_mode",
  "device": {
    "identifiers": ["porch_lights_001"],
    "name": "Porch Lights",
    "manufacturer": "Tim Gage",
    "model": "Porch Lights"
  }
}
)END"; 

AsyncMqttClient mqttClient;

void sendConfigurationMessage() {
  mqttClient.publish("homeassistant/select/porch_lights_mode/config", QOS_1_AT_LEAST_ONCE, RETAIN, configuration_payload);
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);

  uint16_t packetIdSub = mqttClient.subscribe("homeassistant/select/porch_lights_mode/set", QOS_1_AT_LEAST_ONCE);
  Serial.print("Subscribe packet ID: ");
  Serial.println(packetIdSub);


  sendConfigurationMessage();
  Serial.println("Configured");
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Publish received.");
  if (len >= BUFFER_LEN) {
    Serial.println("Payload too big!");
    return;
  } 
  
  memcpy(payload, buffer, len);
  buffer[len] = 0;
  Serial.print("Message: [");
  Serial.print(buffer);
  Serial.println("]");
}

void connectToMqtt() {
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onMessage(onMqttMessage);

  Serial.println("Connecting to MQTT...");
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.connect();
  Serial.println("Connected");

}
