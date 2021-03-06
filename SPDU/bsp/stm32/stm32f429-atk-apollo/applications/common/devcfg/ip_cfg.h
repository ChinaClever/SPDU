/*
 * ip_cfg.h
 *
 *  Created on: 2019年7月4日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_IP_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_IP_CFG_H_
#include "user_cfg.h"

typedef struct sNetAddr {
	boolean dhcp;
	boolean ipV4;
	boolean isUpload; // 数据是否上传

	char ip[20]; // IP地址
	char gw[20]; // 网关
	char mask[20]; //子网掩码
	char dns[20]; // DNS
	char mac[20]; // mac地址
}sNetAddr;

sNetAddr *ip_cfg_get(void);
void ip_cfg_set(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_IP_CFG_H_ */
