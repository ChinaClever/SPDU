/*
 * mqtt_client.h
 *
 *  Created on: 2019Äê6ÔÂ13ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CLIENT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CLIENT_H_
#include "mqtt_cfg.h"
#include "paho_mqtt.h"
//#include "mqtt_client.h"

int mqtt_connect(MQTTClient *client, sMqtt *ci);
int mqtt_publish(MQTTClient *client, sMqtt *ci);

void mqtt_work_thread(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CLIENT_H_ */
