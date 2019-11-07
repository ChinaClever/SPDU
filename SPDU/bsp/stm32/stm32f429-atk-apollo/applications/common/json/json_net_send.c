/*
 * json_net.c
 *
 *{
		"company": "公司标识",
		"version":版本号,
		"item_list": [
			{
				"uid": 编号,
				"status": “测试结果”
			},
			{
			 …….
			}
		……
		] ,
	 }

 *  Created on: 2019年6月17日
 *      Author: luozhiyong
 */
#include "json_net_send.h"


//将传入的JSON结构转化为字符串 并打印
void json_printf(char *data)
{
	cJSON *json = cJSON_Parse(data); //从缓冲区中解析出JSON结构
	char *json_data = cJSON_Print(json);
	printf("data:%s\n",json_data);
	free(json_data);
	cJSON_Delete(json);
}

//打开文件写入json内容
void json_save(char *fn, char *data)
{
	cJSON * json = cJSON_Parse(data); //从缓冲区中解析出JSON结构
	char *buf = cJSON_Print(json); //将json结构格式化到缓冲区
	FILE *fp = fopen(fn,"w");
	fwrite(buf,strlen(buf),1,fp);
	free(buf);
	fclose(fp);
	cJSON_Delete(json);
}

void json_dataUnit(const char *str,int i, sDataUnit *unit, double rate, cJSON *json)
{
	char prefix[24]={0}, string[24]={0};

	sprintf(prefix, "%s_value", str);
	cJSON_AddNumberToObject(json, prefix, unit->value[i]/rate);

	sprintf(prefix, "%s_min", str);
	cJSON_AddNumberToObject(json, prefix, unit->min[i]/rate);

	sprintf(prefix, "%s_max", str);
	cJSON_AddNumberToObject(json, prefix, unit->max[i]/rate);
}

int json_objDataById(int i, sObjData *ObjData, cJSON *jsonArray)
{
	boolean ret = true;
	char string[24]={0};

	if(i < ObjData->size) {
		cJSON *subObj = cJSON_CreateObject();
		cJSON_AddNumberToObject(subObj, "id", i+1);
		//cJSON_AddStringToObject(subObj, "name", ObjData.name[i]);

		//if(ObjData->vol.value[i])
		json_dataUnit("vol", i, &(ObjData->vol), 1, subObj);
		json_dataUnit("cur", i, &(ObjData->cur), COM_RATE_CUR, subObj);

		double value = ObjData->pow[i] / COM_RATE_POW;
		cJSON_AddNumberToObject(subObj, "pow", value);

		value = ObjData->ele[i] / COM_RATE_ELE;
		cJSON_AddNumberToObject(subObj, "ele", value);

		if(ObjData->pf[i] > 99) ObjData->pf[i]= 99;
		value = ObjData->pf[i] / COM_RATE_PF;
		cJSON_AddNumberToObject(subObj, "pf", value);
		cJSON_AddNumberToObject(subObj, "switch", ObjData->sw[i]);

		cJSON_AddItemToArray(jsonArray,subObj);
	} else {
		ret = false;
	}
	return ret;
}

int json_objData(const char *str, sObjData *ObjData, cJSON *obj)
{
	char string[24]={0};
	int i,num=ObjData->size;
	if(num>0) {
		cJSON *jsonArray=cJSON_CreateArray();
		for(i=0; i<num; ++i) {
			json_objDataById(i, ObjData, jsonArray);
		}
		sprintf(string, "%s_item_list", str);
		cJSON_AddItemToObject(obj,string,jsonArray);
	}

	return num;
}

void json_envItem(const char *str, sDataUnit *unit, double rate, cJSON *obj)
{
	char i, string[24]={0};
	cJSON *jsonArray=cJSON_CreateArray();
	for(i=0; i<unit->size; ++i) {
		cJSON *subObj = cJSON_CreateObject();
		cJSON_AddNumberToObject(subObj, "id", i+1);
		json_dataUnit(str, i, unit, rate, subObj);
		cJSON_AddItemToArray(jsonArray,subObj);
	}

	if(unit->size){
		sprintf(string, "%s_items", str);
		cJSON_AddItemToObject(obj,string,jsonArray);
	} else {
		cJSON_Delete(jsonArray);
	}
}

int json_envs(sEnvData *ObjData, cJSON *json)
{
	if(ObjData->size) {
		cJSON *obj = cJSON_CreateObject();
		json_envItem("tem", &(ObjData->tem), 1, obj);
		json_envItem("hum", &(ObjData->hum), 1, obj);
		cJSON_AddItemToObject(json,"env_item_list",obj);
	}

	return ObjData->size;
}

void json_pduInfo(sDataPacket *packet, cJSON *json)
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddStringToObject(obj, "pdu_name", "SI-PDU");
	cJSON_AddNumberToObject(obj, "pdu_num", packet->id);
	cJSON_AddNumberToObject(obj, "pdu_spec", packet->devSpec);
	cJSON_AddNumberToObject(obj, "pdu_dc", packet->dc);
	cJSON_AddNumberToObject(obj, "pdu_hz", packet->hz);
	cJSON_AddNumberToObject(obj, "pdu_ver", packet->version);
	cJSON_AddItemToObject(json, "pdu_info", obj);
}

void json_head(cJSON *json)
{
	cJSON_AddStringToObject(json, "company", "CLEVER");
	cJSON_AddStringToObject(json, "version", "1.0.0");
	cJSON_AddStringToObject(json, "ip_addr", "192.168.1.163");
}

// 返回Buf 需释放 free(buf) ，不然会内存泻
char *json_build(short id)
{
	sDataPacket *packet = data_packet_get(id);
	if(packet->offLine<1) return nullptr;

	cJSON *json = cJSON_CreateObject(); //创建一个空的文档（对象）
	json_head(json);
	json_pduInfo(packet, json);

	sDevData *devData = &(packet->data);
	json_objData("line", &(devData->line), json);
	json_envs(&(devData->env), json);

	char *buf = cJSON_PrintUnformatted(json); //将json结构格式化到缓冲区
	cJSON_Delete(json);

	return buf;
}
