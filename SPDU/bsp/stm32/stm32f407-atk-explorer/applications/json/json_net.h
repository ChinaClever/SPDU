/*
 * json_net.h
 *
 *  Created on: 2019��6��17��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_
#include "dev_cfg.h"
#include "stddef.h"
#include "cJSON.h"

void json_printf(char *data);
void json_save(char *fn, char *data);

// ����Buf ���ͷ� free(buf) ����Ȼ���ڴ�к
char *json_build(void);
boolean json_analysis(char *str);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_ */
