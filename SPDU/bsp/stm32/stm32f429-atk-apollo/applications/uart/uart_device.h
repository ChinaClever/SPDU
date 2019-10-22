/*
 * uarts.h
 *
 *  Created on: 2019Äê10ÔÂ21ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_DEVICE_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_DEVICE_H_
#include "uart_cfg.h"

rt_device_t uart_open(char *name);
rt_err_t uart_control(rt_device_t dev);
int uart_sent(sUart *uart);
int uart_trans(sUart *uart);


#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_DEVICE_H_ */
