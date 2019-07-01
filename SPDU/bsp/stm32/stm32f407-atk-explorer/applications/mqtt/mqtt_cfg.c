/*
 * mqtt_cfg.c
 *
 *  Created on: 2019年6月28日
 *      Author: luozhiyong
 */
#include "mqtt_cfg.h"

static struct sMqtt gMqtt;

#define MQTT_CID 				"spdu"
#define MQTT_URI                "iot.eclipse.org" //"tcp://iot.eclipse.org:1883"
#define MQTT_USERNAME           "admin"
#define MQTT_PASSWORD           "admin"
#define MQTT_SUBTOPIC           "/public/clever/spdu"
#define MQTT_PUBTOPIC           "/public/clever/spdu"
#define MQTT_PORT 				1883

/**
 * MQTT URI farmat:
 * domain mode
 * tcp://iot.eclipse.org:1883
 *
 * ipv4 mode
 * tcp://192.168.10.1:1883
 * ssl://192.168.10.1:1884
 *
 * ipv6 mode
 * tcp://[fe80::20c:29ff:fe9a:a07e]:1883
 * ssl://[fe80::20c:29ff:fe9a:a07e]:1884
 */
struct sMqtt *mqtt_cfg_get(void)
{
	struct sMqtt *cfg = &gMqtt;

	cfg->en = 1;
	cfg->port = MQTT_PORT;
	sprintf(cfg->host, MQTT_URI);
	sprintf(cfg->user, MQTT_USERNAME);
	sprintf(cfg->pass, MQTT_PASSWORD);

	sprintf(cfg->cid, MQTT_CID);
	cfg->keep_alive = 60;
	cfg->cleansession = 1;

	sprintf(cfg->pub_topic, MQTT_PUBTOPIC);
	sprintf(cfg->sub_topic, MQTT_SUBTOPIC);

	cfg->qos = 1; /* 0 1或2，请参阅MQTT规范 */
	cfg->retain = 0; /* =0 的意思应该是不保留有效负载（有效数据） */

	return cfg;
}

int mqtt_cfg_mdelay(void)
{
	struct sMqtt *cfg = &gMqtt;
	if(cfg->mdelay < 15) {
		cfg->mdelay = 15;
	}
	return cfg->mdelay;
}
