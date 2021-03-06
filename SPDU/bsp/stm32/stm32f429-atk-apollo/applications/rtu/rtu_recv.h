/*
 * rtu_recv.h
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_
#include "rtu_sentcmd.h"

#define RTU_LINE_NUM LINE_NUM

typedef struct sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;

    sDataPacket *data;
    ushort crc; // 检验码
}sRtuRecv;

boolean rtu_recv_packet(uchar *buf, int len, sRtuRecv *pkt);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_RECV_H_ */
