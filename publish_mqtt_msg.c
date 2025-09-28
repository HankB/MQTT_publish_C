/*
 * Connect to an MQTRT broker, publish a message, disconnect
 * and return a status.
 */

#include "MQTTClient.h"
#include "publish_mqtt_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static bool chatty = true; // control console output
static MQTTClient client;

#define ID_LEN 30
static char client_id[ID_LEN];
static const char client_prefix[] = "MQTT_test.";
static time_t t;
#define HOSTNAME_LEN 1024
static char hostname[HOSTNAME_LEN];

static int init_mqtt()
{
}

int publish_mqtt_msg(const char *topic, const char *payload, const char *broker, int QOS)
{
    int rc;
    // prepare some strings used to communicate with broker
    srand((unsigned)time(&t)); // seed RNG
    snprintf(client_id, ID_LEN, "%s%8.8X", client_prefix, rand());

    if ((rc = MQTTClient_create(&client, broker, client_id,
                                MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        if (chatty)
            printf("MQTTClient_create() returned %d\n", rc);
        return rc;
    }

    // copied, modified from https://www.hivemq.com/blog/implementing-mqtt-in-c/
    // which was not particularly helpful. Reverted to (mostly)
    // https://github.com/HankB/MQTT_will/blob/main/C/MQTT_will.c
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 10;
    conn_opts.cleansession = 1;
    // conn_opts.username = "username";
    // conn_opts.password = "password";
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        if (chatty)
            printf("MQTTClient_connect() returned %d\n", rc);
        return rc;
    }
    return rc;
}
