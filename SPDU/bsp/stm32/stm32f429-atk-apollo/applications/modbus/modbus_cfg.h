/*
 * modbus_cfg.h
 *
 *  Created on: 2019年6月25日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_
#include "data_packet.h"

typedef struct sMdCfg{
	boolean en;
	ushort port; // 端口号

	uchar addr; // 地址
	uint baud; // 波特率
}sMdCfg;

sMdCfg *mb_cfg_get(void);
void mb_cfg_set(sMdCfg *t);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_ */
