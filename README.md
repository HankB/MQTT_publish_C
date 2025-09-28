# MQTT_publish_C

Code to publish to an MQTT broker

## Description

Code that will

1. Connect to am MQTT broker.
1. Publish a message to a specified topic.
1. Disconnect from the broker and return a status.

This is needed for another project written in `C` and the plan is to produce a single function that does all of this.

## Status

Complete as intended.

## Plan

Write two C files, one of which performs the actions described abote and another that calls it in order to test the function. And a header to declared shared functions.

## Requirements

```text
sudo apt install libpaho-mqtt-dev
```

## Build

```text
gcc -Wall [-g] -o publish_mqtt_msg publish_mqtt_msg.c test_publish.c -lpaho-mqtt3c
```

## Usage

```text
./publish_mqtt_msg
valgrind ./publish_mqtt_msg
./publish_mqtt_msg some_MQTT_broker # defaults to localhost
```

## Resources

* <https://github.com/eclipse-paho/paho.mqtt.c>
* <https://eclipse.dev/paho/files/mqttdoc/MQTTClient/html/pubsync.html>

## Errata

* `MQTTClient_destroy()` is never called. The example uses it during cleanup but it is reused when `publish_mqtt_msg()` is called multiple times and without some kind of `mqtt_deinit()` function it is never cleaned up. The intended use for this is in a program that starts and never exits unless it is killed.
* When using this w/out a password, itr mayu be necesary to add the following to the broker hosts `/etc/mosquitto/mosquitto.conf`. (It might also help when connecting from other than `localhost`)

```text
listener 1883
allow_anonymous true
```

* There are outher decisions made WRT the execution environment (private LAN behind a firewall) and first resource will help to identify things that should be different for other applications (line encryption, user/password.)
