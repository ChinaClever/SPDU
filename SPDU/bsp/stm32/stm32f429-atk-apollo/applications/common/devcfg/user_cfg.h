/*
 * user_cfg.h
 *
 *  Created on: 2019��7��3��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_USER_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_USER_CFG_H_
#include "data_packet.h"

typedef struct sUser{
	char name[16];
	char pass[16];
}sUser;

sUser *user_cfg_get(void);
void user_cfg_set(const char *name, const char *pass);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_USER_CFG_H_ */
