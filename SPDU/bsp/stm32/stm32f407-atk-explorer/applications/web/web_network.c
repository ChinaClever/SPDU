/*
 * web_network.c
 *
 *  Created on: 2019Äê6ÔÂ27ÈÕ
 *      Author: luozhiyong
 */
#include "web_network.h"


void web_network_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sNetPush *t = get_net_cfg();

	ptr[0] = 0;
	sprintf(ptr, "en=%d", t->en); ptr += strlen(ptr);
	sprintf(ptr, "&url=%s",t->url); ptr += strlen(ptr);
	sprintf(ptr, "&port=%d", t->port); ptr += strlen(ptr);
	sprintf(ptr, "&path=%s",t->path); ptr += strlen(ptr);
	sprintf(ptr, "&mdelay=%d",t->mdelay); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_network_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *en_str = webnet_request_get_query(request, "en");
	const char *url_str = webnet_request_get_query(request, "url");
	const char *port_str = webnet_request_get_query(request, "port");
	const char *path_str = webnet_request_get_query(request, "path");
	const char *mdelay_str = webnet_request_get_query(request, "mdelay");

	struct sNetPush *t = get_net_cfg();
	t->en = atoi(en_str);
	t->port = atoi(port_str);
	sprintf(t->url, url_str);
	sprintf(t->path, path_str);
	t->mdelay = atoi(mdelay_str);
	set_net_cfg();

	static const char* status = "en=%d&port=%d&url=%s&path=%s&mdelay=%d";
	webnet_session_printf(session, status, t->en, t->port, t->url,t->path, t->mdelay);
}


void web_network(void)
{
	webnet_cgi_register("getNetworks", web_network_get);
	webnet_cgi_register("setNetworks", web_network_set);
}
