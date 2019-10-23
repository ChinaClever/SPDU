/*
 * rtu_setcmd.h
 *
 *  Created on: 2019��10��23��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_
#include "rtu_recv.h"

enum SI_SetCmdEnum {
    SI_Addr_CMD = 0x1001, //PDU��ַ
    SI_MaxVol1_CMD,   // ������ѹ���ޱ���L1
    SI_MinVol1_CMD,   // ����Ƿѹ���ޱ���L1
    SI_MaxVol2_CMD,   // ������ѹ���ޱ���L2
    SI_MinVol2_CMD,   // ����Ƿѹ���ޱ���L2
    SI_MaxVol3_CMD,   // ������ѹ���ޱ���L3
    SI_MinVol3_CMD,   // ����Ƿѹ���ޱ���L3

    SI_MaxCur1_CMD,   // ���õ������ޱ���L1
    SI_MinCur1_CMD,   // ���õ������ޱ���L1
    SI_MaxCur2_CMD,   // ���õ������ޱ���L2
    SI_MinCur2_CMD,   // ���õ������ޱ���L2
    SI_MaxCur3_CMD,   // ���õ������ޱ���L3
    SI_MinCur3_CMD,   // ���õ������ޱ���L3

    SI_MaxTem_CMD,   // �����¶����ޱ���ֵ
    SI_MinTem_CMD,   // �����¶����ޱ���ֵ2
    SI_MaxHum_CMD,   // ����ʪ�ȶ����ޱ���ֵ
    SI_MinHum_CMD,   // ����ʪ�����ޱ���ֵ

    SI_BR_CMD, // ���ò����ʣ�01Ϊ4800��02Ϊ9600��03Ϊ19200��04Ϊ38400��
    SI_ELE_CMD, // ����ֵ���� ��1111 0000������������Ϊ��һ���ڶ����������ֱ����

    SI_DC_MaxVol_CMD,   // ����ֱ����ѹ��������
    SI_DC_MinVol_CMD,   // ����ֱ����ѹ��������
	SI_DC_MaxCur_CMD,   // ����ֱѹ������������
	SI_DC_MinCur_CMD,   // ����ֱ��������������

	SI_Mode_CMD, // Modbus RTU ģʽ�л�
	// 00 00��ʾ��˾��׼Modbus RTUģʽ(��ȡ������	Ϊ 0x03�����ù�����Ϊ 0x10)
	// 00 01 ��ҵ��׼ Modbus RTU ģʽ(��ȡ������Ϊ	0x03�����ù�����Ϊ 0x06)
	// 01 10 10 19 00 01 D4 CE
};

int rtu_getCmd(sRtu *rtu);
int rtu_setCmd(sRtuSetCmd *cmd);
int rtu_setReg(uchar addr, ushort reg, ushort value);
int rtu_clean_ele(uchar addr);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_ */
