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
#include "json_net.h"


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


//添加数组
uchar json_bulid_array(cJSON *json)
{
	cJSON *array =cJSON_CreateArray();
	cJSON_AddItemToObject(json,"item_list",array);

	uchar i, num = getOutputNum();
	for(i=0; i<num; ++i) { //在数组上添加对象
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToArray(array,obj);
		cJSON_AddNumberToObject(obj, "uid", i+1);
		cJSON_AddBoolToObject(obj, "status",  getSwStatus(i));
	}

	return num;
}

// 返回Buf 需释放 free(buf) ，不然会内存泻
char *json_build(void)
{
	cJSON *json = cJSON_CreateObject(); //创建一个空的文档（对象）

	cJSON_AddStringToObject(json, "version", "1.0.0");
	json_bulid_array(json);

	char *buf = cJSON_PrintUnformatted(json); //将json结构格式化到缓冲区
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
		cJSON *arr_item = arr_node->child;// 获取数组对象孩子节点 子对象
		for(i=0; i<size; ++i){
			id = cJSON_GetObjectItem(arr_item,"uid")->valueint;
			v = cJSON_GetObjectItem(arr_item,"status")->valueint;
			arr_item = arr_item->next;//下一个子对象
			setSwStatus(id-1, v);
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_analysis(char *str)
{
	cJSON *json = cJSON_Parse(str);  //从缓冲区中解析出JSON结构
	boolean ret = json_analysis_array(json);
	cJSON_Delete(json); //将JSON结构所占用的数据空间释放
	return ret;
}

