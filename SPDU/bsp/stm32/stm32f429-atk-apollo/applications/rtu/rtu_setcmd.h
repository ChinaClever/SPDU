/*
 * rtu_setcmd.h
 *
 *  Created on: 2019年10月23日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_
#include "rtu_recv.h"

enum SI_SetCmdEnum {
    SI_Addr_CMD = 0x1001, //PDU地址
    SI_MaxVol1_CMD,   // 设置升压超限报警L1
    SI_MinVol1_CMD,   // 设置欠压超限报警L1
    SI_MaxVol2_CMD,   // 设置升压超限报警L2
    SI_MinVol2_CMD,   // 设置欠压超限报警L2
    SI_MaxVol3_CMD,   // 设置升压超限报警L3
    SI_MinVol3_CMD,   // 设置欠压超限报警L3

    SI_MaxCur1_CMD,   // 设置电流上限报警L1
    SI_MinCur1_CMD,   // 设置电流下限报警L1
    SI_MaxCur2_CMD,   // 设置电流上限报警L2
    SI_MinCur2_CMD,   // 设置电流下限报警L2
    SI_MaxCur3_CMD,   // 设置电流上限报警L3
    SI_MinCur3_CMD,   // 设置电流下限报警L3

    SI_MaxTem_CMD,   // 设置温度上限报警值
    SI_MinTem_CMD,   // 设置温度下限报警值2
    SI_MaxHum_CMD,   // 设置湿度度上限报警值
    SI_MinHum_CMD,   // 设置湿度下限报警值

    SI_BR_CMD, // 设置波特率（01为4800，02为9600，03为19200，04为38400）
    SI_ELE_CMD, // 电能值清零 （1111 0000自左往右依次为第一至第二、第三相和直流）

    SI_DC_MaxVol_CMD,   // 设置直流电压报警上限
    SI_DC_MinVol_CMD,   // 设置直流电压报警下限
	SI_DC_MaxCur_CMD,   // 设置直压电流报警上限
	SI_DC_MinCur_CMD,   // 设置直流电流报警下限

	SI_Mode_CMD, // Modbus RTU 模式切换
	// 00 00表示公司标准Modbus RTU模式(读取功能码	为 0x03，设置功能码为 0x10)
	// 00 01 行业标准 Modbus RTU 模式(读取功能码为	0x03，设置功能码为 0x06)
	// 01 10 10 19 00 01 D4 CE
};

int rtu_getCmd(sRtu *rtu);
int rtu_setCmd(sRtuSetCmd *cmd);
int rtu_setReg(uchar addr, ushort reg, ushort value);
int rtu_clean_ele(uchar addr);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_RTU_RTU_SETCMD_H_ */
