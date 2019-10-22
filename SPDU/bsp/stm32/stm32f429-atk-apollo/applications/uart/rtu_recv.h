/*
 * rtu_recv.h
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_
#include "rtu_sent.h"

#define RTU_LINE_NUM LINE_NUM

typedef struct sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;

    sDataPacket *data;
    ushort crc; // 检验码
}sRtuRecv;

bool rtu_recvPacket(uchar *buf, int len);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_ */
