/*
 * timer.h
 *
 *  Created on: 2019��6��10��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_TIMER_CTIMER_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_TIMER_CTIMER_H_
#include "ctimerfile.h"
#include "thread_pool.h"
#include "swctr.h"

void timer_set_en(int id, boolean en);
void timer_set_time(int id, boolean en, int open, int close);

void timer_seq_setEn(boolean en);
void timer_seq_setTime(boolean en, int open, int close, uchar delay);

void timer_thread(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_TIMER_CTIMER_H_ */
