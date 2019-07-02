/*
 * ali_iot.h
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_
#include "ali_cfg.h"

int ali_mqtt_isrun(void);
void ali_mqtt_close(void);
int ali_mqtt_main(char *key, char *name, char *secret);
int ali_mqtt_pub(char *msg_pub);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_ */
