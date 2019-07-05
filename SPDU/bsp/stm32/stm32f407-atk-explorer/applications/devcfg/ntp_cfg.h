/*
 * ntp_cfg.h
 *
 *  Created on: 2019Äê7ÔÂ4ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_NTP_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_NTP_CFG_H_
#include "ip_cfg.h"
#include "ntp.h"
#include "ctime.h"

void ntp_datetime_get(char* time);
void ntp_datetime_set(const char *str_time);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_DEVCFG_NTP_CFG_H_ */
