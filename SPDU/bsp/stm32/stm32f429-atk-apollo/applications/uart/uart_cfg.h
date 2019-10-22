/*
 * uart_cfg.h
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_CFG_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_CFG_H_
#include <rtthread.h>
#include "rtdevice.h"
#include "data_opt.h"

#define UARTS_NUM 6
#define UART_DELAY 100
#define UART_TIMEOUT 1000
#define UART_PORT_NUM 5

#define UART_RECV_SIZE 128
#define UART_SENT_SIZE 32


/* 串口接收消息结构*/
typedef struct sUart
{
	ushort id;
    rt_device_t dev;
    uint pin;
    char name[RT_NAME_MAX];

    ushort recvLen;
    uchar recvBuf[UART_RECV_SIZE];

    ushort sentLen;
    uchar sentBuf[UART_SENT_SIZE];
    boolean lock;

    uchar start, end;
}sUart;

typedef struct sUarts {
	sUart uart[UARTS_NUM+1];
}sUarts;

sUart *uart_cfg_get(int id);
sUart *uart_cfg_device(rt_device_t dev);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_UART_CFG_H_ */
