/*
 * web_timer.c
 *
 *  Created on: 2019��6��20��
 *      Author: luozhiyong
 */
#include "web_timer.h"


void web_timer_slave(int id, int en,const char *openStr, const char *closeStr)
{
	int open=0, close=0;
	switch(en) {
	case Daily:
		open = dt_timeToSec(openStr);
		close = dt_timeToSec(closeStr);
		break;

	case Once:
		open = dt_strToDatetime(openStr);
		close = dt_strToDatetime(closeStr);
		break;

	default:
		open = atoi(openStr);
		close = atoi(closeStr);
		break;
	}
	timer_set_time(id, en, open, close);
}

void web_timer_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *en_value = webnet_request_get_query(request, "en");
	const char *open = webnet_request_get_query(request, "open");
	const char *close = webnet_request_get_query(request, "close");

	int id = atoi(id_value);
	int en = atoi(en_value);
	if(id>0) {
		web_timer_slave(id-1, en, open, close);
	} else {
		uchar i, num;
		num = getOutputNum();
		for(i=0; i<num; ++i) {
			web_timer_slave(i, en, open, close);
		}
	}

	static const char* status = "id=%d&en=%d&open=%s&close=%s";
	webnet_session_printf(session, status, id, en, open, close);
}

char *web_timer_getStr(uchar id,char *ptr)
{
	char str_open[22] = {0};
	char str_close[22] = {0};
	struct sSwItem *it = getSwItem(id);
	struct sTitem *t = &(it->timer);

	switch(t->en) {
	case Daily:
		dt_secToTime(t->open, str_open);
		dt_secToTime(t->close, str_close);
		break;

	case Once:
		dt_datetimeToStr(t->open, str_open);
		dt_datetimeToStr(t->close, str_close);
		break;

	default:
		sprintf(str_open, "%d", t->open);
		sprintf(str_close, "%d", t->close);
		break;
	}

	sprintf(ptr, "&en_%d=%d",id+1, t->en); ptr += strlen(ptr);
	sprintf(ptr, "&open_%d=%s",id+1, str_open); ptr += strlen(ptr);
	sprintf(ptr, "&close_%d=%s",id+1, str_close); ptr += strlen(ptr);

	return ptr;
}


void web_timer_get(struct webnet_session* session)
{
	char num, i,v, *ptr=pWebQuest;

	num = getOutputNum();
	sprintf(ptr, "num=%d", num);
	ptr += strlen(ptr);

	for(i=0; i<num; ++i) {
		ptr = web_timer_getStr(i, ptr);
	}

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_timer_sw(void)
{
	webnet_cgi_register("setTimer", web_timer_set);
	webnet_cgi_register("getTimers", web_timer_get);
}
