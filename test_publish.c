/*
 * exercise publish_mqtt_msg()
 */

#include <stdio.h>
#include "publish_mqtt_msg.h"

int main()
{
    int rc = publish_mqtt_msg("test/topic", "hello world", "localhost", 0);
    printf("publish_mqtt_msg returned %d\n", rc);
    return 0;
}
