/*
 * rtu_sent.h
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_
#include "rtu_device.h"

#define SI_RTU_AC_LEN 0x51  // 交流数据长度
#define SI_RTU_DC_LEN 0x1B  // 直流数据长度

typedef struct sRtuSent{
    uchar addr; // 表示从机地址码
    uchar fn;  // 表示功能码
    ushort reg; // 表示寄存器首地址
    ushort len; // 表示数据长度
    ushort crc; // 表示CRC校验
}sRtuSent;

typedef struct sRtuSetCmd
{
	uchar addr;
	ushort reg;
    ushort value;
}sRtuSetCmd;

int rtu_cmdBuf(uchar addr, uchar *buf);
int rtu_sentCmd(sRtuSetCmd *cmd, uchar *buf);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_ */
