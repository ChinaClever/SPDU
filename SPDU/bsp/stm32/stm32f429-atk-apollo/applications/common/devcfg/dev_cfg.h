/*
 * dev_cfg.h
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_
#include "data_packet.h"
#include <easyflash.h>

#define CFG_NAME_LEN 12

struct sLocalAddr {
	boolean isUpload; // �����Ƿ��ϴ�
	char idc[CFG_NAME_LEN];
	char room[CFG_NAME_LEN]; // ������
	char cabinet[CFG_NAME_LEN]; // ������
	char line[CFG_NAME_LEN]; // ������
};


struct sDevCfg {
	char devName[CFG_NAME_LEN];

	struct sLocalAddr local;
};

void boot_times_env(void);
void run_times_env(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_DEV_CFG_H_ */
