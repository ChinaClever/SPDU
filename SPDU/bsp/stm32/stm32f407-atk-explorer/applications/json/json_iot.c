/*
 * json_packet.c
 *
 *  Created on: 2019��6��12��
 *      Author: luozhiyong
 *
 *
	 {
		"id": "��˾��ʶ",
		"version":�汾��,
		"params":
			{
				"PowerSwitch_X": ����,
			},

		"method": "thing.event.property.post"
	 }
 *
 */

#include "json_iot.h"


//  ���º�������MQTT��JSON��ʽ
int json_iot_params(cJSON *json)
{
	cJSON *object =cJSON_CreateObject();
	cJSON_AddItemToObject(json,"params",object);

	char key[10] = {0};
	uchar i, num = getOutputNum();
	num = 1;

	for(i=0; i<num; ++i) {
		sprintf(key, "PowerSwitch_%d", i+1);
		cJSON_AddNumberToObject(object, key,  getSwStatus(i));
	}

	return num;
}

char *json_iot_bulid(ushort id)
{
	cJSON *json = cJSON_CreateObject();

	cJSON_AddNumberToObject(json, "id", id);
	cJSON_AddStringToObject(json, "version", "1.0");
	json_iot_params(json);

	cJSON_AddStringToObject(json, "method", "thing.event.property.post");
	char *buf = cJSON_PrintUnformatted(json); //��json�ṹ��ʽ����������

	cJSON_Delete(json);
	return buf;
}

boolean json_analysis_params(cJSON *json)
{
	boolean ret = true;
	cJSON *obj_node = cJSON_GetObjectItem(json,"params");
	if(obj_node->type == cJSON_Object)
	{
		char key[10] = {0};
		uchar i, num = getOutputNum();
		for(i=0; i<num; ++i) {
			sprintf(key, "PowerSwitch_%d", i+1);
			cJSON *item = cJSON_GetObjectItem(obj_node,key);
			if(item) {
				setSwStatus(i, item->valueint);
			} else {
				break;
			}
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_iot_analysis(char *str)
{
	cJSON *json = cJSON_Parse(str);  //�ӻ������н�����JSON�ṹ
	boolean ret = json_analysis_params(json);
	cJSON_Delete(json); //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
	return ret;
}
