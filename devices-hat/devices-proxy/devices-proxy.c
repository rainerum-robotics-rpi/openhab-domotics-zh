/*
 *  devices-proxy.c:
 *	Simple program to adapt IoT devices to a MQTT broker.
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <MQTTClient.h>

#include "ir_remote.h"
#include "dht11_sensor.h"

#define MQTT_ADDRESS  "tcp://localhost:1883"
#define MQTT_CLIENTID "DevicesProxyClient"
#define MQTT_TOPIC    "devices-proxy-exchange"
#define MQTT_QOS      1
#define MQTT_TIMEOUT  10000L

static void publish(MQTTClient client, const char* topic, char* payload) {
  MQTTClient_message pubmsg = MQTTClient_message_initializer;
  pubmsg.payload = payload;
  pubmsg.payloadlen = strlen(pubmsg.payload);
  pubmsg.qos = MQTT_QOS;
  pubmsg.retained = 0;
  MQTTClient_deliveryToken token;
  MQTTClient_publishMessage(client, topic, &pubmsg, &token);
  MQTTClient_waitForCompletion(client, token, MQTT_TIMEOUT);
}

static void publish_sensor(MQTTClient client, const char* topic, float value) {
  static char valBuf[8];
  memset(valBuf, 0, sizeof(valBuf));
  snprintf(valBuf, sizeof(valBuf), "%.1f", value);
  //send measurement
  publish(client, topic, valBuf);
}

static void handleMessage(char* topicName, char* payload) {
  if(strcmp(topicName, "cmd/ir/0") == 0) {
    irHandleCmd(payload);
  }
}

int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
  char* payload = message->payload;
  printf("Received command: %s from %s\n", payload, topicName);
  handleMessage(topicName, payload);
  MQTTClient_freeMessage(&message);
  MQTTClient_free(topicName);
  return 1;
}

int main(void) {
  int rc;
  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

  printf("IoT devices proxy program (MQTT: %s)\n", MQTT_TOPIC);
  irBegin();

  MQTTClient_create(&client, MQTT_ADDRESS, MQTT_CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;
  MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);

  if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
    fprintf(stderr, "Failed to connect MQTT: return code %d\n", rc);
    exit(1);
  }

  //create device
  publish(client, "get/ambient/devices", "0:DHT11_sensor:r");
  //create device
  publish(client, "cmd/ir/devices", "0:IR_I2C_device:w");

  //listen for operation
  MQTTClient_subscribe(client, "cmd/ir/0", 0);

  while(1) {
    static char valBuf[80];
    float tempDegC = 0.0f;
    float tempRelHumPrcnt = 0.0f;
    dht11_refresh(&tempDegC, &tempRelHumPrcnt);
    if(!isnan(tempDegC) && !isnan(tempRelHumPrcnt)) {
      memset(valBuf, 0, sizeof(valBuf));
      snprintf(valBuf, sizeof(valBuf),
               "[{\"DHT11\":{\"Temp\":%.1f,\"RHum\":%.1f},\"TempUnit\":\"°C\",\"RHumUnit\":\"%%\"}]",
               tempDegC, tempRelHumPrcnt);
      //send ambient measurement
      publish_sensor(client, "get/ambient/0/temp", tempDegC);
      publish_sensor(client, "get/ambient/0/rhum", tempRelHumPrcnt);

      publish(client, "get/ambient/0", valBuf);
    }
    delay(1000);
  }
  MQTTClient_disconnect(client, 1000);
  MQTTClient_destroy(&client);
  return rc;
}
