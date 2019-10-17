/*
 * web_outputsw.c
 *
 *  Created on: 2019Äê6ÔÂ20ÈÕ
 *      Author: luozhiyong
 */
#include "web_devstatus.h"

void web_dev_status(struct webnet_session* session)
{
	static char qure[256] = {0};
	struct webnet_request* request = session->request;
	const char *id_str = webnet_request_get_query(request, "id");
	const char *line_str = webnet_request_get_query(request, "line");

	char *ptr=qure;
	int id = atoi(id_str);
	int line = atoi(line_str);
	sObjData *t = &(data_packet_get(id-1)->data.line);

	ptr[0] = 0;
	sprintf(ptr, "id=%d", id); ptr += strlen(ptr);
	sprintf(ptr, "&line=%d", line); ptr += strlen(ptr);
	sprintf(ptr, "&sw=%d", t->sw); ptr += strlen(ptr);
	sprintf(ptr, "&vol=%d",t->vol.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&vol_alarm=%d",t->vol.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur=%d",t->cur.value[line]); ptr += strlen(ptr);
	sprintf(ptr, "&cur_alarm=%d",t->cur.alarm[line]); ptr += strlen(ptr);
	sprintf(ptr, "&pow=%d",t->pow[line]); ptr += strlen(ptr);
	sprintf(ptr, "&pf=%d", t->pf[line]); ptr += strlen(ptr);
	sprintf(ptr, "&ele=%d",t->ele[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", qure);
}


void web_devstatus(void)
{
	webnet_cgi_register("getDevStatus", web_dev_status);
}
