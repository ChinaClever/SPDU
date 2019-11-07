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
				"SocketSwitch_X": 开关,
			},

		"method": "thing.event.property.post"
	 }
 *
 */

#include "json_iot_send.h"


void json_iot_unit(const char *str,int i, sDataUnit *unit, double rate, cJSON *json)
{
	char id=i+1, prefix[24]={0};

	sprintf(prefix, "%s_value_%d", str, id);
	cJSON_AddNumberToObject(json, prefix, unit->value[i]/rate);

	sprintf(prefix, "%s_min_%d", str, id);
	cJSON_AddNumberToObject(json, prefix, unit->min[i]/rate);

	sprintf(prefix, "%s_max_%d", str, id);
	cJSON_AddNumberToObject(json, prefix, unit->max[i]/rate);
}


//  以下函数用于MQTT的JSON格式
int json_iot_objData(const char *str, sObjData *ObjData, cJSON *obj)
{
	char key[32]={0};
	uchar i, num = ObjData->size;

	for(i=0; i<num; ++i) {
		sprintf(key, "%s_vol", str);
		//if(ObjData->vol.value[i])
		json_iot_unit(key, i, &(ObjData->vol), 1, obj);

		sprintf(key, "%s_cur", str);
		json_iot_unit(key, i, &(ObjData->cur), COM_RATE_CUR, obj);

		double value = ObjData->pow[i] / COM_RATE_POW;
		sprintf(key, "%s_pow_%d", str, i+1);
		cJSON_AddNumberToObject(obj, key, value);

		value = ObjData->ele[i] / COM_RATE_ELE;
		sprintf(key, "%s_ele_%d", str, i+1);
		cJSON_AddNumberToObject(obj, key, value);

		if(ObjData->pf[i]>99)ObjData->pf[i]=99;
		value = ObjData->pf[i] / COM_RATE_PF;
		sprintf(key, "%s_pf_%d", str, i+1);
		cJSON_AddNumberToObject(obj, key, value);

		sprintf(key, "%s_sw_%d", str, i+1);
		cJSON_AddNumberToObject(obj, key, ObjData->sw[i]);
	}

	return num;
}

int json_iot_envData(sEnvData *env, cJSON *obj)
{
	uchar i, num = env->size;
	for(i=0; i<num; ++i) {
		json_iot_unit("tem", i, &(env->tem), COM_RATE_TEM, obj);
		json_iot_unit("hum", i, &(env->hum), COM_RATE_HUM, obj);
	}

	return num;
}



char *json_iot_bulid(ushort id)
{
	char *buf = nullptr;
	sDataPacket *packet = data_packet_get(id);

	if(packet->offLine > 0) {
		cJSON *json = cJSON_CreateObject();
		sDevData *devData = &(packet->data);
		json_iot_objData("line", &(devData->line), json);
		json_iot_envData(&(devData->env), json);

		buf = cJSON_PrintUnformatted(json); //将json结构格式化到缓冲区
		cJSON_Delete(json);
	}

	return buf;
}

