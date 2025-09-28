/*
 * exercise publish_mqtt_msg()
 */

#include <stdio.h>
#include "publish_mqtt_msg.h"
#include <unistd.h>

const char *broker = "localhost";

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        broker = argv[1];
    }
    int rc;
    for (int i = 0; i < 10; i++)
    {
        rc = publish_mqtt_msg("test/topic", "hello world", broker, 0);
        printf("publish_mqtt_msg returned %d\n", rc);
        sleep(1);
    }
    return 0;
}
