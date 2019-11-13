/*
 * json_iot_recv.c
 *
 *  Created on: 2019年10月12日
 *      Author: luozhiyong
 */
#include "json_iot_recv.h"




boolean json_analysis_params(const int id, cJSON *json)
{
	boolean ret = true;
	cJSON *obj_node = cJSON_GetObjectItem(json,"params");
	if(obj_node->type == cJSON_Object)
	{
		char key[10] = {0};
		uchar i, num = 0;
		for(i=0; i<num; ++i) {
			sprintf(key, "line_vol_min%d", i+1);
			cJSON *item = cJSON_GetObjectItem(obj_node,key);
			//if(item) setSwStatus(i, item->valueint);
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_iot_analysis(const int id, const char *str)
{
	cJSON *json = cJSON_Parse(str);  //从缓冲区中解析出JSON结构
	boolean ret = json_analysis_params(json);
	cJSON_Delete(json); //将JSON结构所占用的数据空间释放
	return ret;
}
