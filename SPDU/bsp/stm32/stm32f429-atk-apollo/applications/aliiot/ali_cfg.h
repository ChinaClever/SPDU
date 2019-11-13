/*
 * ali_cfg.h
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_
#include "json_iot_recv.h"
#include "infra_defs.h"

typedef struct sAli {
	boolean id, en;
	int iot_devid;
	char name[IOTX_DEVICE_NAME_LEN + 1];
	char key[IOTX_PRODUCT_KEY_LEN + 1];
	char dev_secret[IOTX_DEVICE_SECRET_LEN + 1];
	char pro_secret[IOTX_PRODUCT_SECRET_LEN + 1];
}sAli;

typedef struct sAlis {
	sAli ali[DEV_NUM+2];
}sAlis;

sAli *ali_cfg_get(int id);
int ali_cfg_getByIot(const int id);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_CFG_H_ */
