/*
 * json_net.c
 *
 *{
		"company": "��˾��ʶ",
		"version":�汾��,
		"item_list": [
			{
				"uid": ���,
				"status": �����Խ����
			},
			{
			 ����.
			}
		����
		] ,
	 }

 *  Created on: 2019��6��17��
 *      Author: luozhiyong
 */
#include "json_net.h"


//�������JSON�ṹת��Ϊ�ַ��� ����ӡ
void json_printf(char *data)
{
	cJSON *json = cJSON_Parse(data); //�ӻ������н�����JSON�ṹ
	char *json_data = cJSON_Print(json);
	printf("data:%s\n",json_data);
	free(json_data);
	cJSON_Delete(json);
}


//���ļ�д��json����
void json_save(char *fn, char *data)
{
	cJSON * json = cJSON_Parse(data); //�ӻ������н�����JSON�ṹ
	char *buf = cJSON_Print(json); //��json�ṹ��ʽ����������
	FILE *fp = fopen(fn,"w");
	fwrite(buf,strlen(buf),1,fp);
	free(buf);
	fclose(fp);
	cJSON_Delete(json);
}


//�������
uchar json_bulid_array(cJSON *json)
{
	cJSON *array =cJSON_CreateArray();
	cJSON_AddItemToObject(json,"item_list",array);

	uchar i, num = getOutputNum();
	for(i=0; i<num; ++i) { //����������Ӷ���
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToArray(array,obj);
		cJSON_AddNumberToObject(obj, "uid", i+1);
		cJSON_AddBoolToObject(obj, "status",  getSwStatus(i));
	}

	return num;
}

// ����Buf ���ͷ� free(buf) ����Ȼ���ڴ�к
char *json_build(void)
{
	cJSON *json = cJSON_CreateObject(); //����һ���յ��ĵ�������

	cJSON_AddStringToObject(json, "version", "1.0.0");
	json_bulid_array(json);

	char *buf = cJSON_PrintUnformatted(json); //��json�ṹ��ʽ����������
	cJSON_Delete(json);
	return buf;
}

boolean json_analysis_array(cJSON *json)
{
	boolean ret = true;
	cJSON *arr_node = cJSON_GetObjectItem(json,"item_list");
	if(arr_node->type == cJSON_Array)
	{
		int i, id, v, size = cJSON_GetArraySize(arr_node);
		cJSON *arr_item = arr_node->child;// ��ȡ��������ӽڵ� �Ӷ���
		for(i=0; i<size; ++i){
			id = cJSON_GetObjectItem(arr_item,"uid")->valueint;
			v = cJSON_GetObjectItem(arr_item,"status")->valueint;
			arr_item = arr_item->next;//��һ���Ӷ���
			setSwStatus(id-1, v);
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_analysis(char *str)
{
	cJSON *json = cJSON_Parse(str);  //�ӻ������н�����JSON�ṹ
	boolean ret = json_analysis_array(json);
	cJSON_Delete(json); //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
	return ret;
}

