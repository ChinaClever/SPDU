/*
 * ali_iot.c
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "iot_import.h"
#include "iot_export.h"

#include "rtthread.h"
#include "ali_iot.h"



#if 0
#define ALINK_PROPERTY_POST_PUB          "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post"
#define ALINK_PROPERTY_POST_REPLY_SUB    "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post_reply"
#define ALINK_PROPERTY_SET_REPLY_SUB     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/set_reply"
#define ALINK_SERVICE_SET_SUB            "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/property/set"
#else
static char  ALINK_PROPERTY_POST_PUB[64]={0};		   // "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post"
static char  ALINK_PROPERTY_POST_REPLY_SUB[64]={0};    // "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post_reply"
static char  ALINK_PROPERTY_SET_REPLY_SUB[64]={0};     // "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/set_reply"
static char  ALINK_SERVICE_SET_SUB[64]={0};            // "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/property/set"
#endif
#define MQTT_MSGLEN                      (512)

#define EXAMPLE_TRACE(fmt, ...)  \
		do { \
			HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
			HAL_Printf(fmt, ##__VA_ARGS__); \
			HAL_Printf("%s", "\r\n"); \
		} while(0)

static char __product_key[PRODUCT_KEY_LEN + 1];
static char __device_name[DEVICE_NAME_LEN + 1];
static char __device_secret[DEVICE_SECRET_LEN + 1];

static void   *pclient = NULL;
static uint8_t is_running = 0;

static char* rt_strlwr(char *str)
{
	if(str == NULL)
		return NULL;

	char *p = str;
	while (*p != '\0')
	{
		if(*p >= 'A' && *p <= 'Z')
			*p = (*p) + 0x20;
		p++;
	}
	return str;
}

static void event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
	iotx_mqtt_topic_info_pt topic_info = (iotx_mqtt_topic_info_pt)msg->msg;
	uintptr_t packet_id = (uintptr_t)(msg->msg);

	if (topic_info == NULL)
	{
		rt_kprintf("Topic info is null! Exit.");
		return;
	}

	switch (msg->event_type) {
	case IOTX_MQTT_EVENT_UNDEF:
		EXAMPLE_TRACE("undefined event occur.");
		break;

	case IOTX_MQTT_EVENT_DISCONNECT:
		EXAMPLE_TRACE("MQTT disconnect.");
		break;

	case IOTX_MQTT_EVENT_RECONNECT:
		EXAMPLE_TRACE("MQTT reconnect.");
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_SUCCESS:
		EXAMPLE_TRACE("subscribe success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_TIMEOUT:
		EXAMPLE_TRACE("subscribe wait ack timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_NACK:
		EXAMPLE_TRACE("subscribe nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_SUCCESS:
		EXAMPLE_TRACE("unsubscribe success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_TIMEOUT:
		EXAMPLE_TRACE("unsubscribe timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_NACK:
		EXAMPLE_TRACE("unsubscribe nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_SUCCESS:
		EXAMPLE_TRACE("publish success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_TIMEOUT:
		EXAMPLE_TRACE("publish timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_NACK:
		EXAMPLE_TRACE("publish nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_RECVEIVED:
		EXAMPLE_TRACE("topic message arrived but without any related handle: topic=%.*s, topic_msg=%.*s",
				topic_info->topic_len,
				topic_info->ptopic,
				topic_info->payload_len,
				topic_info->payload);
		break;

	case IOTX_MQTT_EVENT_BUFFER_OVERFLOW:
		EXAMPLE_TRACE("buffer overflow, %s", msg->msg);
		break;

	default:
		EXAMPLE_TRACE("Should NOT arrive here.");
		break;
	}
}

static void ali_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
	iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;

	/* print topic name and topic message */
	EXAMPLE_TRACE("----");
	EXAMPLE_TRACE("packetId: %d", ptopic_info->packet_id);
	EXAMPLE_TRACE("Topic: '%.*s' (Length: %d)",
			ptopic_info->topic_len,
			ptopic_info->ptopic,
			ptopic_info->topic_len);
	EXAMPLE_TRACE("Payload: '%.*s' (Length: %d)",
			ptopic_info->payload_len,
			ptopic_info->payload,
			ptopic_info->payload_len);
	EXAMPLE_TRACE("----");
}

static void ali_message_set(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
	iotx_mqtt_topic_info_pt ptopic_info = (iotx_mqtt_topic_info_pt) msg->msg;

	/* print topic name and topic message */
	EXAMPLE_TRACE("----");
	EXAMPLE_TRACE("packetId: %d", ptopic_info->packet_id);
	EXAMPLE_TRACE("Topic: '%.*s' (Length: %d)",
			ptopic_info->topic_len,
			ptopic_info->ptopic,
			ptopic_info->topic_len);
	EXAMPLE_TRACE("Payload: '%.*s' (Length: %d)",
			ptopic_info->payload_len,
			ptopic_info->payload,
			ptopic_info->payload_len);
	EXAMPLE_TRACE("----");
}

void ali_mqtt_close(void)
{
	if(is_running == 0) return ;
	IOT_MQTT_Yield(pclient, 200);

#ifdef PKG_USING_ALI_IOTKIT_IS_LINKDEVELOP
	IOT_MQTT_Unsubscribe(pclient, ALINK_PROPERTY_POST_REPLY_SUB);
	IOT_MQTT_Unsubscribe(pclient, ALINK_SERVICE_SET_SUB);
#else
	IOT_MQTT_Unsubscribe(pclient, TOPIC_DATA);
#endif

	IOT_MQTT_Yield(pclient, 200);
	IOT_MQTT_Destroy(&pclient);
	IOT_DumpMemoryStats(IOT_LOG_DEBUG);
	IOT_CloseLog();

	is_running = 0;
	pclient = NULL;

	EXAMPLE_TRACE("ali out of !");
}

static void ali_mqtt_client(void)
{
	int rc = 0;

	iotx_conn_info_pt pconn_info;
	iotx_mqtt_param_t mqtt_params;
	char *msg_buf = NULL, *msg_readbuf = NULL;

	IOT_OpenLog("mqtt");
	IOT_SetLogLevel(IOT_LOG_ERROR); // IOT_LOG_DEBUG

	if (NULL == (msg_buf = (char *)HAL_Malloc(MQTT_MSGLEN))) {
		EXAMPLE_TRACE("not enough memory");
		rc = -1;
		goto do_exit;
	}

	if (NULL == (msg_readbuf = (char *)HAL_Malloc(MQTT_MSGLEN))) {
		EXAMPLE_TRACE("not enough memory");
		rc = -1;
		goto do_exit;
	}

	HAL_GetProductKey(__product_key);
	HAL_GetDeviceName(__device_name);
	HAL_GetDeviceSecret(__device_secret);

	/* Device AUTH */
	if (0 != IOT_SetupConnInfo(__product_key, __device_name, __device_secret, (void **)&pconn_info)) {
		EXAMPLE_TRACE("AUTH request failed!");
		rc = -1;
		goto do_exit;
	}

	/* Initialize MQTT parameter */
	memset(&mqtt_params, 0x0, sizeof(mqtt_params));

	mqtt_params.port = pconn_info->port;
	mqtt_params.host = pconn_info->host_name;
	mqtt_params.client_id = pconn_info->client_id;
	mqtt_params.username = pconn_info->username;
	mqtt_params.password = pconn_info->password;
	mqtt_params.pub_key = pconn_info->pub_key;

	mqtt_params.request_timeout_ms = 2000;
	mqtt_params.clean_session = 0;
	mqtt_params.keepalive_interval_ms = 60000;
	mqtt_params.pread_buf = msg_readbuf;
	mqtt_params.read_buf_size = MQTT_MSGLEN;
	mqtt_params.pwrite_buf = msg_buf;
	mqtt_params.write_buf_size = MQTT_MSGLEN;

	mqtt_params.handle_event.h_fp = event_handle;
	mqtt_params.handle_event.pcontext = NULL;

	/* Convert uppercase letters in host to lowercase */
	rt_kprintf("host: %s\r\n", rt_strlwr((char*)mqtt_params.host));

	/* Construct a MQTT client with specify parameter */
	pclient = IOT_MQTT_Construct(&mqtt_params);
	if (NULL == pclient) {
		EXAMPLE_TRACE("MQTT construct failed");
		rc = -1;
		goto do_exit;
	}

#ifdef PKG_USING_ALI_IOTKIT_IS_LINKDEVELOP
	/* Subscribe the specific topic */
	rc = IOT_MQTT_Subscribe(pclient, ALINK_SERVICE_SET_SUB, IOTX_MQTT_QOS1, ali_message_set, NULL);
#else
	rc = IOT_MQTT_Subscribe(pclient, TOPIC_DATA, IOTX_MQTT_QOS1, ali_message_arrive, NULL);
#endif

	if (rc < 0) {
		EXAMPLE_TRACE("IOT_MQTT_Subscribe() failed, rc = %d", rc);
		rc = -1;
		goto do_exit;
	}

#ifdef PKG_USING_ALI_IOTKIT_IS_LINKDEVELOP
	/* Subscribe the specific topic */
	rc = IOT_MQTT_Subscribe(pclient, ALINK_PROPERTY_POST_REPLY_SUB, IOTX_MQTT_QOS1, ali_message_arrive, NULL);
	if (rc < 0) {
		EXAMPLE_TRACE("IOT_MQTT_Subscribe() failed, rc = %d", rc);
		rc = -1;
		goto do_exit;
	}
#endif

	IOT_MQTT_Yield(pclient, 200);

	do {
		/* handle the MQTT packet received from TCP or SSL connection */
		IOT_MQTT_Yield(pclient, 200);
		HAL_SleepMs(2*1000);
	} while (is_running && pclient);

	do_exit:
	ali_mqtt_close();
	if (NULL != msg_buf) {
		HAL_Free(msg_buf);
	}

	if (NULL != msg_readbuf) {
		HAL_Free(msg_readbuf);
	}
}


int ali_mqtt_isrun(void)
{
	int ret = 1;
	if ((!pclient) || (!is_running)) {
		// HAL_Printf("MQTT test is not running! ");
		ret = 0;
	}

	return ret;
}

int ali_mqtt_pub(char *msg_pub)
{
	int rc = 0;
	iotx_mqtt_topic_info_t topic_msg;

	rc = ali_mqtt_isrun();
	if(!rc) return rc;

	memset(&topic_msg, 0x0, sizeof(iotx_mqtt_topic_info_t));
	topic_msg.qos = IOTX_MQTT_QOS1;
	topic_msg.retain = 0;
	topic_msg.dup = 0;
	topic_msg.payload = (void *)msg_pub;
	topic_msg.payload_len = strlen(msg_pub);

	rc = IOT_MQTT_Publish(pclient, ALINK_PROPERTY_POST_PUB, &topic_msg);
	if (rc < 0) {
		EXAMPLE_TRACE("error occur when publish");
		ali_mqtt_close();
		rc = -1;
	}
	// EXAMPLE_TRACE("\n publish message: \n topic: %s\n payload: %s\n rc = %d", ALINK_PROPERTY_POST_PUB, topic_msg.payload, rc);

	return rc;
}

void ali_mqtt_init(char *key, char *name, char *secret)
{
	char *ptr = ALINK_PROPERTY_POST_PUB;
	sprintf(ptr, "/sys/%s/%s/thing/event/property/post", key, name);

	ptr = ALINK_PROPERTY_POST_REPLY_SUB;
	sprintf(ptr, "/sys/%s/%s/thing/event/property/post_reply", key, name);

	ptr = ALINK_PROPERTY_SET_REPLY_SUB;
	sprintf(ptr, "/sys/%s/%s/thing/event/property/set_reply", key, name);

	ptr = ALINK_SERVICE_SET_SUB;
	sprintf(ptr, "/sys/%s/%s/thing/service/property/set", key, name);
}

int ali_mqtt_main(char *key, char *name, char *secret)
{
	is_running = 1;
	HAL_SetProductKey(key);
	HAL_SetDeviceName(name);
	HAL_SetDeviceSecret(secret);
	ali_mqtt_init(key, name, secret);

#if 1
	ali_mqtt_client();
#else
	rt_thread_t tid = rt_thread_create("ali-mqtt", (void (*)(void *))ali_mqtt_client, NULL,
			4 * 1024, RT_THREAD_PRIORITY_MAX / 2 - 1, 10);
	if (tid != RT_NULL) rt_thread_startup(tid);
#endif

	return is_running;
}



