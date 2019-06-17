/*
 * json_packet.c
 *
 *  Created on: 2019年6月12日
 *      Author: luozhiyong
 *
 *
	 {
		"id": "公司标识",
		"version":版本号,
		"params":
			{
				"PowerSwitch_X": 开关,
			},

		"method": "thing.event.property.post"
	 }
 *
 */

#include "json_iot.h"


//  以下函数用于MQTT的JSON格式
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
	char *buf = cJSON_PrintUnformatted(json); //将json结构格式化到缓冲区

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
	cJSON *json = cJSON_Parse(str);  //从缓冲区中解析出JSON结构
	boolean ret = json_analysis_params(json);
	cJSON_Delete(json); //将JSON结构所占用的数据空间释放
	return ret;
}
