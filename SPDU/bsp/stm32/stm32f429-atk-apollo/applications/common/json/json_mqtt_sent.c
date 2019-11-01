/*
 * json_mqtt_sent.c
 *
 * 	��Ϊ�����512�ֽڣ�����һ��PDU���ݷֿ�����
 *  ��һ�δ������ݣ���һ��ͻ�������
 *
 *  Created on: 2019��11��1��
 *      Author: luozhiyong
 */
#include "json_mqtt_sent.h"

int json_mqtt_objData_oneLine(int id, const char *str, sObjData *ObjData, cJSON *obj)
{
	int ret = true;
	char string[24]={0};
	int num=ObjData->size;
	if(id < num) {
		num = 1;
		cJSON *jsonArray=cJSON_CreateArray();
		json_objDataById(id, ObjData, jsonArray);
		sprintf(string, "%s_item_list", str);
		cJSON_AddItemToObject(obj,string,jsonArray);
	} else {
		ret = false;
	}

	return num;
}


// һ���豸���ݷֶ��δ��䣬��Ϊ�����õ���mqtt����䳤��Ϊ512�ֽ�, ���԰����ݷֿ�
char *json_mqtt_build(short id, short line)
{
	sDataPacket *packet = data_packet_get(id);
	if(packet->offLine<1) return nullptr;

	cJSON *json = cJSON_CreateObject(); //����һ���յ��ĵ�������
	json_head(json);
	json_pduInfo(packet, json);

	sDevData *devData = &(packet->data);
	int ret = json_mqtt_objData_oneLine(line, "line", &(devData->line), json);
	if(line == 3) { // ��һ�δ��䣬�����һ��ͻ�������
		ret = json_envs(&(devData->env), json);
	}

	char *buf=nullptr;
	if(ret) buf = cJSON_PrintUnformatted(json); //��json�ṹ��ʽ����������
	cJSON_Delete(json);

	return buf;
}
