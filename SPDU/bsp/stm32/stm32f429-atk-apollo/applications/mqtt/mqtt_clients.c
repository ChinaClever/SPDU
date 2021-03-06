/*
 * mqtt_c.c
 *
 *  Created on: 2019��10��31��
 *      Author: luozhiyong
 */
#include "mqtt_clients.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "mqtt.client"
#define DBG_LEVEL           DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>


#define MQTT_WILLMSG            "Goodbye!"
#define MQTTPacket_connectData_initializer { {'M', 'Q', 'T', 'C'}, 0, 4, {NULL, {0, NULL}}, 60, 1, 0, \
		MQTTPacket_willOptions_initializer, {NULL, {0, NULL}}, {NULL, {0, NULL}} }

#ifdef PKG_USING_ALI_IOTKIT
enum connack_return_codes
{
  MQTT_CONNECTION_ACCEPTED = 0,
  MQTT_UNNACCEPTABLE_PROTOCOL = 1,
  MQTT_CLIENTID_REJECTED = 2,
  MQTT_SERVER_UNAVAILABLE = 3,
  MQTT_BAD_USERNAME_OR_PASSWORD = 4,
  MQTT_NOT_AUTHORIZED = 5,
};

const char *MQTTSerialize_connack_string(unsigned char connack_rc)
{
#define PAHO_STRING(s)                 #s
#define PAHO_TOSTRING(s)               PAHO_STRING(s)

    switch (connack_rc)
    {
    case MQTT_CONNECTION_ACCEPTED:
        return PAHO_TOSTRING(MQTT_CONNECTION_ACCEPTED);
    case MQTT_UNNACCEPTABLE_PROTOCOL:
        return PAHO_TOSTRING(MQTT_UNNACCEPTABLE_PROTOCOL);
    case MQTT_CLIENTID_REJECTED:
        return PAHO_TOSTRING(MQTT_CLIENTID_REJECTED);
    case MQTT_SERVER_UNAVAILABLE:
        return PAHO_TOSTRING(MQTT_SERVER_UNAVAILABLE);
    case MQTT_BAD_USERNAME_OR_PASSWORD:
        return PAHO_TOSTRING(MQTT_BAD_USERNAME_OR_PASSWORD);
    case MQTT_NOT_AUTHORIZED:
        return PAHO_TOSTRING(MQTT_NOT_AUTHORIZED);
    default:
        return "UNKNOWN_ERROR";
    }
}
#endif

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
			msg_data->topic_name->lenstring.len,
			msg_data->topic_name->lenstring.data,
			msg_data->message->payloadlen,
			(char *)msg_data->message->payload);

	if(msg_data->message->payloadlen > 0) {
		//json_analysis((char *)msg_data->message->payload);
	}
}



static void mqtt_sub_default_callback(MQTTClient *c, MessageData *msg_data)
{
	*((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
	LOG_D("mqtt sub default callback: %.*s %.*s",
			msg_data->topic_name->lenstring.len,
			msg_data->topic_name->lenstring.data,
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
	//mqtt_stop(c);
	LOG_D("inter mqtt_offline_callback!");
}

static void mqtt_malloc(MQTTClient *client)
{
	if(0 == client->buf_size)
	{  /* malloc buffer. */
		client->buf_size = client->readbuf_size = 512;
		client->buf = rt_calloc(1, client->buf_size);
		client->readbuf = rt_calloc(1, client->readbuf_size);
		if (!(client->buf && client->readbuf)) {
			LOG_E("no memory for MQTT client buffer!");
		}
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
	client->condata.keepAliveInterval = ci->keep_alive; // 30
	client->condata.cleansession = ci->cleansession; // 1

	if(strlen(ci->user)) {
		client->condata.username.cstring = ci->user;
		client->condata.password.cstring = ci->pass;
	}

	/* config MQTT will param. */
	client->condata.willFlag = 1;
	client->condata.will.qos = 1; // ci->pub_qos; // QOS1
	client->condata.will.retained = ci->retain;
	client->condata.will.topicName.cstring = ci->pub_topic;
	client->condata.will.message.cstring = MQTT_WILLMSG;

	/* set event callback function */
	client->connect_callback = mqtt_connect_callback;
	client->online_callback = mqtt_online_callback;
	client->offline_callback = mqtt_offline_callback;

	/* set subscribe table and event callback */
	client->message_handlers[0].topicFilter = rt_strdup(ci->sub_topic);
	client->message_handlers[0].callback = mqtt_sub_callback;
	client->message_handlers[0].qos = ci->sub_qos; // QOS1

	/* set default subscribe event callback */
	client->default_message_handlers = mqtt_sub_default_callback;

	{
		int value;
		uint16_t u16Value;
		value = 5;
		paho_mqtt_control(client, MQTT_CTRL_SET_CONN_TIMEO, &value);
		value = 5;
		paho_mqtt_control(client, MQTT_CTRL_SET_MSG_TIMEO, &value);
		value = 5;
		paho_mqtt_control(client, MQTT_CTRL_SET_RECONN_INTERVAL, &value);
		value = 30;
		paho_mqtt_control(client, MQTT_CTRL_SET_KEEPALIVE_INTERVAL, &value);
		u16Value = 3;
		paho_mqtt_control(client, MQTT_CTRL_SET_KEEPALIVE_COUNT, &u16Value);
	}

	/* run mqtt client */
	if(0 == ci->isRun) {
		mqtt_malloc(client);
		paho_mqtt_start(client, 8196, 16);
//		paho_mqtt_start(client);
		ci->isRun = 1;
	}

	return 0;
}


int mqtt_publish(MQTTClient *client, sMqtt *ci)
{
	int ret = 0;
	if(client->isconnected) {
		ret = paho_mqtt_publish(client, ci->pub_qos, ci->pub_topic, ci->pub_payload,strlen(ci->pub_payload));
		if(ret) rt_kprintf("mqtt publish err %d\n", ret);
	}

	return ret;
}



int mqtt_connect(MQTTClient *client, sMqtt *ci)
{
	int ret = 0;
	if(ci->en) {
		if(client->isconnected) {
			ret = 1;
		} else {
			mqtt_start(client, ci);
		}
	} else {
		mqtt_stop(client);
	}

	return ret;
}


