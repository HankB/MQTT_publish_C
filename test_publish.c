/*
 * exercise publish_mqtt_msg()
 */

#include <stdio.h>
#include "publish_mqtt_msg.h"
#include <unistd.h>

int main()
{
    int rc;
    for (int i = 0; i < 10; i++)
    {
        rc = publish_mqtt_msg("test/topic", "hello world", "localhost", 0);
        printf("publish_mqtt_msg returned %d\n", rc);
        sleep(1);
    }
    return 0;
}
