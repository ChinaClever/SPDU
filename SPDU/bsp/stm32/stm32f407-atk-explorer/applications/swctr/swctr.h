/*
 * swctr.h
 *
 *  Created on: 2019��6��10��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_SWCTR_SWCTR_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_SWCTR_SWCTR_H_

#include "../devcfg/dev_cfg.h"
#include "pcf8574.h"

#define SW_OPRN		1
#define SW_CLOSE	0

boolean sw_init(void);
void sw_deinit(void);

int sw_pin_read(int pin);
void sw_all_write(int v);
boolean sw_pin_write(int pin, int v);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_SWCTR_SWCTR_H_ */
