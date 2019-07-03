/*
 * dev_cfg.h
 *
 *  Created on: 2019年6月6日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#include "data_packet.h"

#define CFG_NAME_LEN 12

struct sNetAddr {
	boolean dhcp;
	boolean ipV4;
	boolean isUpload; // 数据是否上传

	char ip[20]; // IP地址
	char gw[20]; // 网关
	char mask[20]; //子网掩码
	char dns[20]; // DNS
	char mac[20]; // mac地址
};

struct sLocalAddr {
	boolean isUpload; // 数据是否上传
	char idc[CFG_NAME_LEN];
	char room[CFG_NAME_LEN]; // 机房名
	char cabinet[CFG_NAME_LEN]; // 机柜名
	char line[CFG_NAME_LEN]; // 相名称
};


struct sDevCfg {
	char devName[CFG_NAME_LEN];

	struct sNetAddr net;
	struct sLocalAddr local;
};


#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_ */
