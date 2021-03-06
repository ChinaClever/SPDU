/*
 * web_ipaddr.c
 *
 *  Created on: 2019��7��4��
 *      Author: luozhiyong
 */
#include "web_ipaddr.h"


void web_ipaddr_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sNetAddr *t = ip_cfg_get();

	ptr[0] = 0;
	sprintf(ptr, "ip=%s", t->ip); ptr += strlen(ptr);
	sprintf(ptr, "&mask=%s", t->mask); ptr += strlen(ptr);
	sprintf(ptr, "&gw=%s",t->gw); ptr += strlen(ptr);
	sprintf(ptr, "&dns=%s",t->dns); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_ipaddr_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *ip = webnet_request_get_query(request, "ip");
	const char *mask = webnet_request_get_query(request, "mask");
	const char *gw = webnet_request_get_query(request, "gw");
	const char *dns = webnet_request_get_query(request, "dns");

	struct sNetAddr *t = ip_cfg_get();
	strcpy(t->ip, ip);
	strcpy(t->mask, mask);
	strcpy(t->gw, gw);
	strcpy(t->dns, dns);
	ip_cfg_set();

	static const char* status = "ip=%s&mask=%s&gw=%s&dns=%s";
	webnet_session_printf(session, status, t->ip, t->mask, t->gw, t->dns);
}


void web_ip_addr(void)
{
	webnet_cgi_register("getIpAddr", web_ipaddr_get);
	webnet_cgi_register("setIpAddr", web_ipaddr_set);
}

