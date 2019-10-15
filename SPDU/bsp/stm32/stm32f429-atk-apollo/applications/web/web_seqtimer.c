/*
 * web_seqtimer.c
 *
 *  Created on: 2019��6��24��
 *      Author: luozhiyong
 */
#include "web_seqtimer.h"

void web_seqtimer_slave(int en,uchar tm, const char *openStr, const char *closeStr)
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
	timer_seq_setTime(en, open, close, tm);
}

void web_seqtimer_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *en_value = webnet_request_get_query(request, "en");
	const char *tm_value = webnet_request_get_query(request, "delay");
	const char *open = webnet_request_get_query(request, "open");
	const char *close = webnet_request_get_query(request, "close");

	int en = atoi(en_value);
	int tm = atoi(tm_value);
	web_seqtimer_slave(en,tm, open, close);

	static const char* status = "delay=%d&en=%d&open=%s&close=%s";
	webnet_session_printf(session, status, tm, en, open, close);
}

char *web_seqtimer_getStr(char *ptr)
{
	char str_open[22] = {0};
	char str_close[22] = {0};
	struct sTitem *t = getSequence();

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

	sprintf(ptr, "en=%d", t->en); ptr += strlen(ptr);
	sprintf(ptr, "&open=%s", str_open); ptr += strlen(ptr);
	sprintf(ptr, "&close=%s",str_close); ptr += strlen(ptr);
	sprintf(ptr, "&delay=%d",getDelaytm()); ptr += strlen(ptr);

	return ptr;
}


void web_seqtimer_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;

	ptr[0] = 0;
	web_seqtimer_getStr(ptr);
	webnet_session_printf(session, "%s", pWebQuest);
}

void web_seq_timer(void)
{
	webnet_cgi_register("setSeqTimer", web_seqtimer_set);
	webnet_cgi_register("getSeqTimers", web_seqtimer_get);
}

