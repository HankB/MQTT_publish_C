#pragma once

int publish_mqtt_msg(const char *topic, const char *payload, const char *broker, int QOS);
