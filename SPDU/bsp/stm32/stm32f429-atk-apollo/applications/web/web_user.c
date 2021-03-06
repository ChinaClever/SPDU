/*
 * web_user.c
 *
 *  Created on: 2019��7��4��
 *      Author: luozhiyong
 */
#include "web_user.h"


void web_user_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sUser *t = user_cfg_get();

	ptr[0] = 0;
	sprintf(ptr, "name=%s", t->name); ptr += strlen(ptr);
	sprintf(ptr, "&pass=%s",t->pass); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_user_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *name = webnet_request_get_query(request, "name");
	const char *pass = webnet_request_get_query(request, "pass");
	user_cfg_set(name, pass);

	static const char* status = "name=%s&pass=%s";
	webnet_session_printf(session, status, name, pass);
}


void web_user(void)
{
	webnet_cgi_register("getUser", web_user_get);
	webnet_cgi_register("setUser", web_user_set);
}
