/*
 * net_cfg.h
 *
 *  Created on: 2019��6��27��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_
#include "http_client.h"

struct sNetPush {
	boolean en;
	ushort mdelay;

	char url[32]; // ��ַ
	ushort port; // �˿�
	char path[32]; // ·��
	uchar connects; // �������Ӵ���
};

void net_cfg_set(void);
struct sNetPush *net_cfg_get(void);
int net_dalay_get(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_ */
