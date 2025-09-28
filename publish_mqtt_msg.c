/*
 * Connect to an MQTT broker, publish a message, disconnect
 * and return a status.
 */

#include "MQTTClient.h"
#include "publish_mqtt_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

static bool chatty = true; // control console output
static MQTTClient client;
static MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
static MQTTClient_message pubmsg = MQTTClient_message_initializer;

#define ID_LEN 30
static char client_id[ID_LEN];
static const char client_prefix[] = "MQTT_test.";
static time_t t;

static bool mqtt_initiailzed = false;

static int init_mqtt(const char *broker, int QOS)
{
    int rc;
    // prepare some strings used to communicate with broker
    srand((unsigned)time(&t)); // seed RNG
    snprintf(client_id, ID_LEN, "%s%8.8X", client_prefix, rand());
    conn_opts.keepAliveInterval = 10;
    conn_opts.cleansession = 1;
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    if ((rc = MQTTClient_create(&client, broker, client_id,
                                MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        if (chatty)
            printf("MQTTClient_create() returned %d\n", rc);
        return rc;
    }

    mqtt_initiailzed = true;
    return 0;
}

#define TIMEOUT 10000L

static MQTTClient_deliveryToken token = 0;

int publish_mqtt_msg(const char *topic, const char *payload, const char *broker, int QOS)
{
    int rc;

    if (!mqtt_initiailzed)
    {
        rc = init_mqtt(broker, QOS);
        if (chatty)
            printf("init_mqtt() returned %d\n", rc);
        if (0 != rc)
        {
            return rc;
        }
    }

    // copied, modified from https://www.hivemq.com/blog/implementing-mqtt-in-c/
    // which was not particularly helpful. Reverted to (mostly)
    // https://github.com/HankB/MQTT_will/blob/main/C/MQTT_will.c
    // and then https://eclipse.dev/paho/files/mqttdoc/MQTTClient/html/pubsync.html
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        if (chatty)
            printf("MQTTClient_connect() returned %d\n", rc);
        return rc;
    }

    pubmsg.payload = (char *)payload;
    pubmsg.payloadlen = strlen(payload);
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
           "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT / 1000), payload, topic, client_id);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    MQTTClient_disconnect(client, 10000);

    //MQTTClient_destroy(&client);
    return rc;
}
