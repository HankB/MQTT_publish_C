# MQTT_publish_C

Code to publish to an MQTT broker

## Description

Code that will

1. Connect to am MQTT broker.
1. Publish a message to a specified topic.
1. Disconnect from the broker and return a status.

This is needed for another project written in `C` and the plan is to produce a single function that does all of this.

## Plan

Write two C files, one of which performs the actions described abote and another that calls it in order to test the function.

## Requirements

```text
sudo apt install libpaho-mqtt-dev
```

## Build

```text
gcc -o publish_mqtt_msg publish_mqtt_msg.c test_publish.c -lpaho-mqtt3c
```

## Resources

* <https://github.com/eclipse-paho/paho.mqtt.c>
* <https://eclipse.dev/paho/files/mqttdoc/MQTTClient/html/pubsync.html>
