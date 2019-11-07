/*
 * ali_iot.h
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_
#include "ali_cfg.h"

int ali_master_connect();
int ali_mqtt_pub(int id, char *msg);
int ali_event_alarm(int id, int code);
int ali_event_error(int id, int code);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_ALIIOT_ALI_IOT_H_ */
