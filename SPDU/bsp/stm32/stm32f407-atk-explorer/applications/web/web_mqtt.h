/*
 * web_mqtt.h
 *
 *  Created on: 2019��7��2��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_WEB_WEB_MQTT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_WEB_WEB_MQTT_H_
#include "web_network.h"

#ifdef PKG_USING_MYMQTT
#include "mqtt_thread.h"

void web_mqtt(void);
#endif

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_WEB_WEB_MQTT_H_ */
