/*
 * json_net_recv.c
 *
 *  Created on: 2019年10月12日
 *      Author: luozhiyong
 */
#include "json_net_recv.h"






boolean json_recv_array(cJSON *json)
{
	boolean ret = true;
	cJSON *arr_node = cJSON_GetObjectItem(json, "line_vol_items");
	if(arr_node->type == cJSON_Array)
	{
		int i, size = cJSON_GetArraySize(arr_node);
		cJSON *arr_item = arr_node->child;// 获取数组对象孩子节点 子对象
		for(i=0; i<size; ++i){
			int id = cJSON_GetObjectItem(arr_item,"id")->valueint;
			double min = cJSON_GetObjectItem(arr_item,"min")->valuedouble;
			double max = cJSON_GetObjectItem(arr_item,"max")->valuedouble;

			arr_item = arr_item->next;//下一个子对象
			//setSwStatus(id-1, v);
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_analysis(char *str)
{
	cJSON *json = cJSON_Parse(str);  //从缓冲区中解析出JSON结构
	boolean ret = json_recv_array(json);
	cJSON_Delete(json); //将JSON结构所占用的数据空间释放
	return ret;
}



