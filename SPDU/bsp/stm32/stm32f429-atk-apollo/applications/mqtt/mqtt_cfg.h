/*
 * mqtt_cfg.h
 *
 *  Created on: 2019��6��28��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#include "json_iot_recv.h"


typedef struct sMqtt {
	char en;

	char host[32]; 	// Host����
	unsigned short port; 	// Port�˿�

	char user[32]; 	// Username�û���    Ĭ��Ϊ��
	char pass[32]; 	// Password����   Ĭ��Ϊ��

	char cid[32];	// Client ID
	short keep_alive; // Keep-Alive����
	char cleansession; // Ĭ��Ϊ1

	char pub_topic[32];
	char pub_qos; // Ĭ��Ϊ1 // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���
	char retain; // Ĭ��Ϊ0

	char sub_topic[32];
	char sub_qos; // Ĭ��Ϊ1 // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���

	char *pub_payload;
	short mdelay;
	char isRun;
	void *pclient;
}sMqtt;

sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

void mqtt_cfg_set(void);
#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
