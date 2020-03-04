/*
 * rtu_cfg.h
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_CFG_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_CFG_H_
#include <rtthread.h>
#include "rtdevice.h"
#include "data_packet.h"
#include "list.h"

#define UARTS_NUM 7
#define UART_DELAY 100
#define UART_TIMEOUT 1000
#define UART_PORT_NUM 6

#define UART_RECV_SIZE 256
#define UART_SENT_SIZE 24

#define RTU_CMD_LEN 8


/* 串口接收消息结构*/
typedef struct sRtu
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
    list_t *cmds;
}sRtu;

typedef struct sRtus {
	uchar ac_dc; // 交直流标志
	uchar portDevs; // 一个端口设备数据

	sRtu rtu[UARTS_NUM+1];
}sRtus;

uchar rtu_cfg_ad(void);
sRtus *rtus_cfg_get(void);

sRtu *rtu_cfg_get(int id);
sRtu *rtu_cfg_addr(uchar addr);
sRtu *rtu_cfg_device(rt_device_t dev);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_CFG_H_ */
