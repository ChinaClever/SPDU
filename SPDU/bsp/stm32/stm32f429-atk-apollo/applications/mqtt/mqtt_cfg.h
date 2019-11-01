/*
 * mqtt_cfg.h
 *
 *  Created on: 2019年6月28日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#include "json_iot_recv.h"


typedef struct sMqtt {
	char en;

	char host[32]; 	// Host主机
	unsigned short port; 	// Port端口

	char user[32]; 	// Username用户名    默认为空
	char pass[32]; 	// Password密码   默认为空

	char cid[32];	// Client ID
	short keep_alive; // Keep-Alive保活
	char cleansession; // 默认为1

	char pub_topic[32];
	char pub_qos; // 默认为1 // QoS服务质量 	0最多一次传输   1至少一次传输   2 只有一次传输
	char retain; // 默认为0

	char sub_topic[32];
	char sub_qos; // 默认为1 // QoS服务质量 	0最多一次传输   1至少一次传输   2 只有一次传输

	char *pub_payload;
	short mdelay;
	char isRun;
	void *pclient;
}sMqtt;

sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

void mqtt_cfg_set(void);
#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
