/*
 * dev_cfg.h
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#include "data_packet.h"

#define CFG_NAME_LEN 12

struct sNetAddr {
	boolean dhcp;
	boolean ipV4;
	boolean isUpload; // �����Ƿ��ϴ�

	char ip[20]; // IP��ַ
	char gw[20]; // ����
	char mask[20]; //��������
	char dns[20]; // DNS
	char mac[20]; // mac��ַ
};

struct sLocalAddr {
	boolean isUpload; // �����Ƿ��ϴ�
	char idc[CFG_NAME_LEN];
	char room[CFG_NAME_LEN]; // ������
	char cabinet[CFG_NAME_LEN]; // ������
	char line[CFG_NAME_LEN]; // ������
};


struct sDevCfg {
	char devName[CFG_NAME_LEN];

	struct sNetAddr net;
	struct sLocalAddr local;
};


#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_ */
