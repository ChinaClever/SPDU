/*
 * web_seqtimer.c
 *
 *  Created on: 2019Äê6ÔÂ24ÈÕ
 *      Author: luozhiyong
 */
#include "web_envs.h"

void web_env_setThreshold(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *line_value = webnet_request_get_query(request, "line");
	const char *tem_min = webnet_request_get_query(request, "tem_min");
	const char *tem_max = webnet_request_get_query(request, "tem_max");
	const char *hum_min = webnet_request_get_query(request, "hum_min");
	const char *hum_max = webnet_request_get_query(request, "hum_max");

	int id = atoi(id_value);
	int line = atoi(line_value);
	sEnvData *t = &(data_packet_get(id)->data.env);

	int value = atoi(tem_min);
	t->tem.min[line] = value;

	value = atoi(tem_max);
	t->tem.max[line] = value;

	value = atoi(hum_min);
	t->hum.min[line] = value;

	value = atoi(hum_max);
	t->hum.max[line] = value;

	static const char* status = "id=%d&line=%d";
	webnet_session_printf(session, status, id, line);
}



void web_env_getThreshold(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_str = webnet_request_get_query(request, "id");
	const char *line_str = webnet_request_get_query(request, "line");

	char *ptr=pWebQuest;
	int id = atoi(id_str);
	int line = atoi(line_str);
	sEnvData *t = &(data_packet_get(id)->data.env);

	ptr[0] = 0;
	sprintf(ptr, "id=%d", id); ptr += strlen(ptr);
	sprintf(ptr, "&line=%d", line); ptr += strlen(ptr);
	sprintf(ptr, "&tem=%d",t->tem.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&tem_alarm=%d",t->tem.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&tem_min=%d",t->tem.min[line]); ptr += strlen(ptr);
	sprintf(ptr, "&tem_max=%d",t->tem.max[line]); ptr += strlen(ptr);

	sprintf(ptr, "&hum=%d",t->hum.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&hum_alarm=%d",t->hum.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&hum_min=%d",t->hum.min[line]); ptr += strlen(ptr);
	sprintf(ptr, "&hum_max=%d",t->hum.max[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}


void web_env_values(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_str = webnet_request_get_query(request, "id");
	const char *line_str = webnet_request_get_query(request, "line");

	char *ptr=pWebQuest;
	int id = atoi(id_str)-1;
	int line = atoi(line_str);
	sEnvData *t = &(data_packet_get(id)->data.env);

	ptr[0] = 0;
	sprintf(ptr, "id=%d", id); ptr += strlen(ptr);
	sprintf(ptr, "&line=%d", line); ptr += strlen(ptr);
	sprintf(ptr, "&tem=%d",t->tem.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&tem_alarm=%d",t->tem.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&hum=%d",t->hum.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&hum_alarm=%d",t->hum.alarm[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}


void web_envs(void)
{
	webnet_cgi_register("getEnvValues", web_env_values);
	webnet_cgi_register("getEnvThresholds", web_env_getThreshold);
	webnet_cgi_register("setEnvThreshold", web_env_setThreshold);
}

