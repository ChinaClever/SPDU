/*
 * json_net.h
 *
 *  Created on: 2019��6��17��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_

#include "stddef.h"
#include "cJSON.h"
#include "data_packet.h"

void json_printf(char *data);
void json_save(char *fn, char *data);

void json_head(cJSON *json);
void json_pduInfo(sDataPacket *packet, cJSON *json);
int json_envs(sEnvData *ObjData, cJSON *json);
int json_objDataById(int i, sObjData *ObjData, cJSON *jsonArray);


// ����Buf ���ͷ� free(buf) ����Ȼ���ڴ�к
char *json_build(short id);
boolean json_analysis(char *str);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_JSON_JSON_NET_H_ */
