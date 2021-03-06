/*
 * modbus_read.h
 *
 *  Created on: 2019��10��24��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_READ_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_READ_H_
#include "modbus_cfg.h"
#include "modbus.h"

int mb_read_packet(uchar addr, modbus_mapping_t *mb);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_MODBUS_MODBUS_READ_H_ */
