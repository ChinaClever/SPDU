/*
 * rtus.h
 *
 *  Created on: 2019��10��21��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_DEVICE_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_DEVICE_H_
#include "rtu_cfg.h"

rt_device_t rtu_open(char *name);
rt_err_t rtu_control(rt_device_t dev);
int rtu_sent(sRtu *rtu);
int rtu_trans(sRtu *rtu);


#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_DEVICE_H_ */
