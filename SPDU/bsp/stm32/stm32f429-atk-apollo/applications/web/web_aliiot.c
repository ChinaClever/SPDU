/*
 * web_aliiot.c
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */
#include "web_aliiot.h"


void web_aliiot_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sAli *t = ali_cfg_get();

	ptr[0] = 0;
	sprintf(ptr, "en=%d", t->en); ptr += strlen(ptr);
	sprintf(ptr, "&name=%s", t->name); ptr += strlen(ptr);
	sprintf(ptr, "&key=%s",t->key); ptr += strlen(ptr);
	sprintf(ptr, "&secret=%s",t->secret); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_aliiot_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *en_str = webnet_request_get_query(request, "en");
	const char *name_str = webnet_request_get_query(request, "name");
	const char *key_str = webnet_request_get_query(request, "key");
	const char *secret_str = webnet_request_get_query(request, "secret");

	struct sAli *t = ali_cfg_get();
	t->en = atoi(en_str);
	sprintf(t->name, name_str);
	sprintf(t->key, key_str);
	sprintf(t->secret, secret_str);
	ali_cfg_set();

	static const char* status = "en=%d&name=%s&key=%s&secret=%s";
	webnet_session_printf(session, status, t->en, t->name, t->key, t->secret);
}


void web_aliiot(void)
{
	webnet_cgi_register("getAliIot", web_aliiot_get);
	webnet_cgi_register("setAliIot", web_aliiot_set);
}

