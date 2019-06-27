/*
 * net_cfg.h
 *
 *  Created on: 2019年6月27日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_
#include "http_client.h"

struct sNetPush {
	boolean en;
	ushort mdelay;

	char url[32]; // 地址
	ushort port; // 端口
	char path[32]; // 路径
	uchar connects; // 尝试连接次数
};

void set_net_cfg(void);
struct sNetPush *get_net_cfg(void);
int get_net_dalay(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_NET_CFG_H_ */
