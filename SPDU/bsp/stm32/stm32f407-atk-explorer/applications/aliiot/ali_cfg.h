/*
 * ali_cfg.h
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_
#include "json_iot.h"

struct sAli {
	boolean en;
	char name[32];
	char key[32];
	char secret[46];
};
struct sAli *ali_cfg_get(void);
void ali_cfg_set(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_ */
