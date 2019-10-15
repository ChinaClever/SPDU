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
				"SocketSwitch_X": ����,
			},

		"method": "thing.event.property.post"
	 }
 *
 */

#include "json_iot_send.h"


void json_iot_unit(const char *str,int i, sDataUnit *unit, double rate, cJSON *json)
{
	char id=i+1, prefix[24]={0}, string[24]={0};

	sprintf(prefix, "%s_value_%d", str, id);
	sprintf(string, "%f", unit->value[i]/rate);
	cJSON_AddStringToObject(json, prefix, string);

	sprintf(prefix, "%s_min_%d", str, id);
	sprintf(string, "%f", unit->min[i]/rate);
	cJSON_AddStringToObject(json, prefix, string);

	sprintf(prefix, "%s_max_%d", str, id);
	sprintf(string, "%f", unit->max[i]/rate);
	cJSON_AddStringToObject(json, prefix, string);
}


//  ���º�������MQTT��JSON��ʽ
int json_iot_objData(const char *str, sObjData *ObjData, cJSON *obj)
{
	char key[32]={0}, string[24]={0};
	uchar i, num = ObjData->size;

	for(i=0; i<num; ++i) {
		sprintf(key, "%s_vol", str);
		//if(ObjData->vol.value[i])
		json_iot_unit(key, i, &(ObjData->vol), COM_RATE_VOL, obj);

		sprintf(key, "%s_cur", str);
		json_iot_unit(key, i, &(ObjData->cur), COM_RATE_CUR, obj);

		double value = ObjData->pow[i] / COM_RATE_POW;
		sprintf(string, "%f", value);
		sprintf(key, "%s_pow_%d", str, i+1);
		cJSON_AddStringToObject(obj, key, string);

		value = ObjData->ele[i] / COM_RATE_ELE;
		sprintf(string, "%f", value);
		sprintf(key, "%s_ele_%d", str, i+1);
		cJSON_AddStringToObject(obj, key, string);

		value = ObjData->pf[i] / COM_RATE_PF;
		sprintf(string, "%.2f", value);
		sprintf(key, "%s_pf_%d", str, i+1);
		cJSON_AddStringToObject(obj, key, string);

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
		json_objData("line", &(devData->line), json);
		json_iot_envData(&(devData->env), json);

		buf = cJSON_PrintUnformatted(json); //��json�ṹ��ʽ����������
		cJSON_Delete(json);
	}

	return buf;
}
