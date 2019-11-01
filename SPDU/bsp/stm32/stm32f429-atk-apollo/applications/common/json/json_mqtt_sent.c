/*
 * json_mqtt_sent.c
 *
 * 	因为最大传输512字节，所以一个PDU数据分开传输
 *  第一次传输数据，第一相和环境数据
 *
 *  Created on: 2019年11月1日
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


// 一个设备数据分二次传输，因为这里用到的mqtt最大传输长度为512字节, 所以把数据分开
char *json_mqtt_build(short id, short line)
{
	sDataPacket *packet = data_packet_get(id);
	if(packet->offLine<1) return nullptr;

	cJSON *json = cJSON_CreateObject(); //创建一个空的文档（对象）
	json_head(json);
	json_pduInfo(packet, json);

	sDevData *devData = &(packet->data);
	int ret = json_mqtt_objData_oneLine(line, "line", &(devData->line), json);
	if(line == 3) { // 第一次传输，传输第一相和环境数据
		ret = json_envs(&(devData->env), json);
	}

	char *buf=nullptr;
	if(ret) buf = cJSON_PrintUnformatted(json); //将json结构格式化到缓冲区
	cJSON_Delete(json);

	return buf;
}
