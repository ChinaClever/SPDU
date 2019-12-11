/*
 * rtu_sent.h
 *
 *  Created on: 2019��10��22��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_
#include "rtu_device.h"

#define SI_RTU_AC_LEN 0x51  // �������ݳ���
#define SI_RTU_DC_LEN 0x1B  // ֱ�����ݳ���

typedef struct sRtuSent{
    uchar addr; // ��ʾ�ӻ���ַ��
    uchar fn;  // ��ʾ������
    ushort reg; // ��ʾ�Ĵ����׵�ַ
    ushort len; // ��ʾ���ݳ���
    ushort crc; // ��ʾCRCУ��
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
