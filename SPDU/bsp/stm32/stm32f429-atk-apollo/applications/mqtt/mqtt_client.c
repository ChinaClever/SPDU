/*
 * mqtt_client.c
 *
 *   测试网址:http://tongxinmao.com/App/Detail/id/126
 *
 *  Created on: 2019年6月13日
 *      Author: luozhiyong
 */

#include "paho_mqtt.h"
#include "mqtt_client.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "mqtt.client"
#define DBG_LEVEL           DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>


#define MQTT_WILLMSG            "Goodbye!"
#define MQTTPacket_connectData_initializer { {'M', 'Q', 'T', 'C'}, 0, 4, {NULL, {0, NULL}}, 60, 1, 0, \
		MQTTPacket_willOptions_initializer, {NULL, {0, NULL}}, {NULL, {0, NULL}} }


// 动态延时，当延时时间变化时立即做出响应
void mqtt_delay()
{
	uint16_t i, d=mqtt_cfg_mdelay();

	for(i=0; i<d; ++i) {
		sleep(1);
		d=mqtt_cfg_mdelay();
	}
}

static void mqtt_stop(MQTTClient *client)
{
	if(client->isconnected) {
		paho_mqtt_stop(client);
		client->isconnected = 0;
	}
}

static void mqtt_sub_callback(MQTTClient *c, MessageData *msg_data)
{
	*((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
	LOG_D("mqtt sub callback: %.*s %.*s",
			msg_data->topicName->lenstring.len,
			msg_data->topicName->lenstring.data,
			msg_data->message->payloadlen,
			(char *)msg_data->message->payload);

	if(msg_data->message->payloadlen > 0) {
		json_iot_analysis((char *)msg_data->message->payload);
	}
}

static void mqtt_sub_default_callback(MQTTClient *c, MessageData *msg_data)
{
	*((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
	LOG_D("mqtt sub default callback: %.*s %.*s",
			msg_data->topicName->lenstring.len,
			msg_data->topicName->lenstring.data,
			msg_data->message->payloadlen,
			(char *)msg_data->message->payload);
}

static void mqtt_connect_callback(MQTTClient *c)
{
	LOG_D("inter mqtt_connect_callback!");
}

static void mqtt_online_callback(MQTTClient *c)
{
	c->isconnected = 1;
	LOG_D("inter mqtt_online_callback!");
}

static void mqtt_offline_callback(MQTTClient *c)
{
	mqtt_stop(c);
	LOG_D("inter mqtt_offline_callback!");
}

static void mqtt_malloc(MQTTClient *client)
{
	/* malloc buffer. */
	client->buf_size = client->readbuf_size = 1024;
	client->buf = rt_calloc(1, client->buf_size);
	client->readbuf = rt_calloc(1, client->readbuf_size);
	if (!(client->buf && client->readbuf)) {
		LOG_E("no memory for MQTT client buffer!");
	}
}


static int mqtt_start(MQTTClient *client, sMqtt *ci)
{
	static char curi[36] = { 0 };
	MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
	sprintf(curi, "%s:%d", ci->host, ci->port);

	mqtt_stop(client);
	client->uri = curi;

	/* config connect param */
	memcpy(&client->condata, &condata, sizeof(condata));
	client->condata.clientID.cstring = ci->cid;
	client->condata.keepAliveInterval = ci->keep_alive; // 60
	client->condata.cleansession = ci->cleansession; // 1
	client->condata.username.cstring = ci->user;
	client->condata.password.cstring = ci->pass;

	/* config MQTT will param. */
	client->condata.willFlag = 1;
	client->condata.will.qos = ci->pub_qos; // QOS1
	client->condata.will.retained = ci->retain;
	client->condata.will.topicName.cstring = ci->pub_topic;
	client->condata.will.message.cstring = MQTT_WILLMSG;

	/* set event callback function */
	client->connect_callback = mqtt_connect_callback;
	client->online_callback = mqtt_online_callback;
	client->offline_callback = mqtt_offline_callback;

	/* set subscribe table and event callback */
	client->messageHandlers[0].topicFilter = rt_strdup(ci->sub_topic);
	client->messageHandlers[0].callback = mqtt_sub_callback;
	client->messageHandlers[0].qos = ci->sub_qos; // QOS1

	/* set default subscribe event callback */
	client->defaultMessageHandler = mqtt_sub_default_callback;

	/* run mqtt client */
	paho_mqtt_start(client);

	return 0;
}

static int mqtt_publish(MQTTClient *client, sMqtt *ci)
{
	int ret = 0;
	if(client->isconnected) {
		ret = paho_mqtt_publish(client, ci->pub_qos, ci->pub_topic, ci->pub_payload);
	}

	return ret;
}

void mqtt_done_work(MQTTClient *client, sMqtt *ci, ushort id)
{
	char *msg = nullptr; // "PubSubHubLubJub";
	if(client->isconnected) {
		msg = json_iot_bulid(id); //推送的有效数据(负载)
		if(msg) {
			ci->pub_payload = msg;
			mqtt_publish(client, ci);
			mqtt_delay();
			free(msg);
		}
	} else {
		mqtt_start(client, ci);
	}
}

void mqtt_task(void)
{
	int i = 0;
	MQTTClient client;
	sMqtt *ci = mqtt_cfg_get();

	sleep(10);
	mqtt_malloc(&client);
	client.isconnected = 0;
	while(1)
	{
		if(ci->en) {
			for(i=0; i<DEV_NUM; ++i) {
				mqtt_done_work(&client, ci, i);
			}
		} else {
			mqtt_stop(&client);
		}
		sleep(1+rand()%3);
	}
}

void mqtt_work_thread(void)
{
	rt_thread_t tid = rt_thread_create("mqttc",mqtt_task, NULL,2*1024,24, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}


