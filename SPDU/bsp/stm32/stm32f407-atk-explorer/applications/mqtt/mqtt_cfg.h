/*
 * mqtt_cfg.h
 *
 *  Created on: 2019年6月28日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_
#include "network.h"


struct sMqtt {
	char en;

	char host[32]; 	// Host主机
	unsigned short port; 	// Port端口

	char user[32]; 	// Username用户名
	char pass[32]; 	// Password密码

	char cid[32];	// Client ID
	short keep_alive; // Keep-Alive保活
	char cleansession;

	char pub_topic[32];
	char qos; // QoS服务质量 	0最多一次传输   1至少一次传输   2 只有一次传输
	char retain;

	char sub_topic[32];

	char *pub_payload;
	short mdelay;
};

struct sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
