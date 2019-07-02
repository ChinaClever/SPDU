/*
 * web_modbus.c
 *
 *  Created on: 2019Äê6ÔÂ26ÈÕ
 *      Author: luozhiyong
 */
#include "web_modbus.h"


void web_modbus_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sMdCfg *t = md_cfg_get();

	ptr[0] = 0;
	sprintf(ptr, "en=%d", t->en); ptr += strlen(ptr);
	sprintf(ptr, "&port=%d", t->port); ptr += strlen(ptr);
	sprintf(ptr, "&addr=%d",t->addr); ptr += strlen(ptr);
	sprintf(ptr, "&baud=%d",t->baud); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_modbus_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *en_str = webnet_request_get_query(request, "en");
	const char *port_str = webnet_request_get_query(request, "port");
	const char *addr_str = webnet_request_get_query(request, "addr");
	const char *baud_str = webnet_request_get_query(request, "baud");

	struct sMdCfg t;
	t.en = atoi(en_str);
	t.port = atoi(port_str);
	t.addr = atoi(addr_str);
	t.baud = atoi(baud_str);
	md_cfg_set(&t);

	static const char* status = "en=%d&port=%d&addr=%d&baud=%d";
	webnet_session_printf(session, status, t.en, t.port, t.addr, t.baud);
}


void web_modbus(void)
{
	webnet_cgi_register("getModbus", web_modbus_get);
	webnet_cgi_register("setModbus", web_modbus_set);
}
