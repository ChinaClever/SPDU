/*
 * web_timer.c
 *
 *  Created on: 2019Äê6ÔÂ20ÈÕ
 *      Author: luozhiyong
 */
#include "web_thresholds.h"

void web_threshold_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *line_value = webnet_request_get_query(request, "line");
	const char *vol_min = webnet_request_get_query(request, "vol_min");
	const char *vol_max = webnet_request_get_query(request, "vol_max");
	const char *cur_min = webnet_request_get_query(request, "cur_min");
	const char *cur_max = webnet_request_get_query(request, "cur_max");

	int id = atoi(id_value);
	int line = atoi(line_value);
	sObjData *t = &(data_packet_get(id)->data.line);

	int value = atoi(vol_min);
	t->vol.min[line] = value;

	value = atoi(vol_max);
	t->vol.max[line] = value;

	value = atoi(cur_min);
	t->cur.min[line] = value;

	value = atoi(cur_max);
	t->cur.max[line] = value;

	static const char* status = "id=%d&line=%d";
	webnet_session_printf(session, status, id, line);
}



void web_threshold_get(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_str = webnet_request_get_query(request, "id");
	const char *line_str = webnet_request_get_query(request, "line");

	char *ptr=pWebQuest;
	int id = atoi(id_str);
	int line = atoi(line_str);
	sObjData *t = &(data_packet_get(id-1)->data.line);

	ptr[0] = 0;
	sprintf(ptr, "id=%d", id); ptr += strlen(ptr);
	sprintf(ptr, "&line=%d", line); ptr += strlen(ptr);
	sprintf(ptr, "&vol=%d",t->vol.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&vol_alarm=%d",t->vol.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&vol_min=%d",t->vol.min[line]); ptr += strlen(ptr);
	sprintf(ptr, "&vol_max=%d",t->vol.max[line]); ptr += strlen(ptr);

	sprintf(ptr, "&cur=%d",t->cur.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur_alarm=%d",t->cur.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur_min=%d",t->cur.min[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur_max=%d",t->cur.max[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}


void web_values_get(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_str = webnet_request_get_query(request, "id");
	const char *line_str = webnet_request_get_query(request, "line");

	char *ptr=pWebQuest;
	int id = atoi(id_str)-1;
	int line = atoi(line_str);
	sObjData *t = &(data_packet_get(id)->data.line);

	ptr[0] = 0;
	sprintf(ptr, "id=%d", id); ptr += strlen(ptr);
	sprintf(ptr, "&line=%d", line); ptr += strlen(ptr);
	sprintf(ptr, "&vol=%d",t->vol.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&vol_alarm=%d",t->vol.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur=%d",t->cur.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur_alarm=%d",t->cur.alarm[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}


void web_thresholds(void)
{
	webnet_cgi_register("getValues", web_values_get);
	webnet_cgi_register("getThresholds", web_threshold_get);
	webnet_cgi_register("setThreshold", web_threshold_set);
}
