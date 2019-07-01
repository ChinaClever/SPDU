/*
 * mqtt_cfg.h
 *
 *  Created on: 2019��6��28��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#include "network.h"


struct sMqtt {
	char en;

	char host[32]; 	// Host����
	unsigned short port; 	// Port�˿�

	char user[32]; 	// Username�û���
	char pass[32]; 	// Password����

	char cid[32];	// Client ID
	short keep_alive; // Keep-Alive����
	char cleansession;

	char pub_topic[32];
	char qos; // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���
	char retain;

	char sub_topic[32];

	char *pub_payload;
	short mdelay;
};

struct sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
