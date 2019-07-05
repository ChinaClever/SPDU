/*
 * web_settime.c
 *
 *  Created on: 2019��7��4��
 *      Author: luozhiyong
 */
#include "web_settime.h"


void web_ntptime_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;

	ptr[0] = 0;
	sprintf(ptr, "time="); ptr += strlen(ptr);
	ntp_datetime_get(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_ntptime_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *time = webnet_request_get_query(request, "settime");

	ntp_datetime_set(time);
	static const char* status = "time=%s";
	webnet_session_printf(session, status, time);
}


void web_ntp_time(void)
{
	webnet_cgi_register("getNtpTime", web_ntptime_get);
	webnet_cgi_register("setNtpTime", web_ntptime_set);
}

