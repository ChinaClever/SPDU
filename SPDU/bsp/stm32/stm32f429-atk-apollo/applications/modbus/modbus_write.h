/*
 * modbus_write.h
 *
 *  Created on: 2019��10��24��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_WRITE_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_WRITE_H_
#include "modbus_read.h"

int mb_write_reg(uchar addr, ushort reg, ushort value);
int mb_write_regs(uchar addr,ushort reg, ushort num,  const uchar *ptr);


#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_WRITE_H_ */
