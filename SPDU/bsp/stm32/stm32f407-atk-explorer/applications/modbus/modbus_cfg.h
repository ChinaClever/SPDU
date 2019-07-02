/*
 * modbus_cfg.h
 *
 *  Created on: 2019年6月25日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_
#include "swthread.h"

struct sMdCfg{
	boolean en; // 0 TCP 1 RTU
	ushort port; // 端口号

	uchar addr; // 地址
	uint baud; // 波特率
};

struct sMdCfg *md_cfg_get(void);
void md_cfg_set(struct sMdCfg *t);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MODBUS_MODBUS_CFG_H_ */
