/*
 * web_mqtt.c
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */
#include "web_mqtt.h"
#ifdef PKG_USING_MYMQTT

void web_mqtt_get(struct webnet_session* session)
{
	char *ptr=pWebQuest;
	struct sMqtt *t = mqtt_cfg_get();

	ptr[0] = 0;
	sprintf(ptr, "en=%d", t->en); ptr += strlen(ptr);
	sprintf(ptr, "&url=%s",t->host); ptr += strlen(ptr);
	sprintf(ptr, "&port=%d", t->port); ptr += strlen(ptr);
	sprintf(ptr, "&user=%s",t->user); ptr += strlen(ptr);
	sprintf(ptr, "&pass=%s",t->pass); ptr += strlen(ptr);
	sprintf(ptr, "&cid=%s",t->cid); ptr += strlen(ptr);
	sprintf(ptr, "&keep_alive=%d",t->keep_alive); ptr += strlen(ptr);
	sprintf(ptr, "&cleansession=%d",t->cleansession); ptr += strlen(ptr);
	sprintf(ptr, "&pub_topic=%s",t->pub_topic); ptr += strlen(ptr);
	sprintf(ptr, "&pub_qos=%d",t->pub_qos); ptr += strlen(ptr);
	sprintf(ptr, "&retain=%d",t->retain); ptr += strlen(ptr);
	sprintf(ptr, "&sub_topic=%s",t->sub_topic); ptr += strlen(ptr);
	sprintf(ptr, "&sub_qos=%d",t->sub_qos); ptr += strlen(ptr);
	sprintf(ptr, "&mdelay=%d",t->mdelay); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_mqtt_set(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *en_str = webnet_request_get_query(request, "en");
	const char *url = webnet_request_get_query(request, "url");
	const char *port_str = webnet_request_get_query(request, "port");
	const char *user = webnet_request_get_query(request, "user");
	const char *pass = webnet_request_get_query(request, "pass");
	const char *cid = webnet_request_get_query(request, "cid");
	const char *keep_alive = webnet_request_get_query(request, "keep_alive");
	const char *cleansession = webnet_request_get_query(request, "cleansession");
	const char *pub_topic = webnet_request_get_query(request, "pub_topic");
	const char *pub_qos = webnet_request_get_query(request, "pub_qos");
	const char *retain = webnet_request_get_query(request, "retain");
	const char *sub_topic = webnet_request_get_query(request, "sub_topic");
	const char *sub_qos = webnet_request_get_query(request, "sub_qos");
	const char *mdelay_str = webnet_request_get_query(request, "mdelay");

	struct sMqtt *t = mqtt_cfg_get();
	t->en = atoi(en_str);
	t->port = atoi(port_str);
	sprintf(t->host, url);
	sprintf(t->user, user);
	sprintf(t->pass, pass);
	sprintf(t->cid, cid);
	t->keep_alive = atoi(keep_alive);
	t->cleansession = atoi(cleansession);
	sprintf(t->pub_topic, pub_topic);
	t->pub_qos = atoi(pub_qos);
	t->retain = atoi(retain);
	sprintf(t->sub_topic, sub_topic);
	t->sub_qos = atoi(sub_qos);
	t->mdelay = atoi(mdelay_str);
	mqtt_cfg_set();

	static const char* status = "en=%d";
	webnet_session_printf(session, status, t->en);
}


void web_mqtt(void)
{
	webnet_cgi_register("getMqtts", web_mqtt_get);
	webnet_cgi_register("setMqtts", web_mqtt_set);
}

#endif
