/*
 * mqtt_cfg.c
 *
 *  Created on: 2019年6月28日
 *      Author: luozhiyong
 */
#include "mqtt_cfg.h"

#define MQTT_CID 				"spdu"
#define MQTT_URI                "tcp://mq.tongxinmao.com" //"tcp://iot.eclipse.org:1883"
#define MQTT_USERNAME           "admin"
#define MQTT_PASSWORD           "admin"
#define MQTT_SUBTOPIC           "/public/clever/spdu"
#define MQTT_PUBTOPIC           "/public/clever/spdu"
#define MQTT_PORT 				18831

void mqtt_cfg_init(sMqtt *cfg)
{
	cfg->en = 0;
	cfg->port = MQTT_PORT;
	sprintf(cfg->host, MQTT_URI);
//	sprintf(cfg->user, MQTT_USERNAME);
//	sprintf(cfg->pass, MQTT_PASSWORD);

	sprintf(cfg->cid, MQTT_CID);
	cfg->keep_alive = 7;
	cfg->cleansession = 1;

	sprintf(cfg->pub_topic, MQTT_PUBTOPIC);
	sprintf(cfg->sub_topic, MQTT_SUBTOPIC);

	cfg->pub_qos = 1; /* 0 1或2，请参阅MQTT规范 */
	cfg->retain = 0; /* =0 的意思应该是不保留有效负载（有效数据） */
	cfg->sub_qos = 1;
}

sMqtt *mqtt_cfg_get(void)
{
	static sMqtt *cfg = nullptr;
	if(!cfg) {
		cfg = malloc(sizeof(sMqtt));
		memset(cfg, 0, sizeof(sMqtt));
		mqtt_cfg_init(cfg);
	}

	return cfg;
}

int mqtt_cfg_mdelay(void)
{
	sMqtt *cfg = mqtt_cfg_get();
	if(cfg->mdelay < 5) {
		cfg->mdelay = 5;
	}
	return cfg->mdelay;
}

void mqtt_cfg_set(void)
{

}
