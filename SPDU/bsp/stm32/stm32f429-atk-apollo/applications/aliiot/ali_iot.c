/*
 * ali_iot.c
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */

#include "infra_config.h"
#ifdef DEPRECATED_LINKKIT
#include "gateway.c"
#else
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "cJSON.h"
#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "infra_log.h"
#include "infra_compat.h"
#include "infra_log.h"
#include "dev_model_api.h"
#include "dm_wrapper.h"

#ifdef LINKKIT_GATEWAY_TEST_CMD
#include "simulate_subdev/testcmd.h"
#endif

#if defined(OTA_ENABLED) && defined(BUILD_AOS)
#include "ota_service.h"
#endif

#include "ali_iot.h"

static char PRODUCT_KEY[IOTX_PRODUCT_KEY_LEN + 1] = {0};
static char PRODUCT_SECRET[IOTX_PRODUCT_SECRET_LEN + 1] = {0};
static char DEVICE_NAME[IOTX_DEVICE_NAME_LEN + 1] = {0};
static char DEVICE_SECRET[IOTX_DEVICE_SECRET_LEN + 1] = {0};

#define USER_EXAMPLE_YIELD_TIMEOUT_MS (200)

void HAL_Printf(const char *fmt, ...);
#define ALI_TRACE(...) \
		do { \
			HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__); \
			HAL_Printf(__VA_ARGS__); \
			HAL_Printf("\033[0m\r\n"); \
		} while (0)

#define EXAMPLE_SUBDEV_ADD_NUM          1
#define EXAMPLE_SUBDEV_MAX_NUM          (20+1)
iotx_linkkit_dev_meta_info_t subdevArr[EXAMPLE_SUBDEV_MAX_NUM] = {
		{
				"a14Ktp17XZ9",
				"x3sN98DSvSCaDQUH",
				"dev_spdu",
				"LBIWWvIrtMnevkNohenFexb4p1w83svB"
		}
};

typedef struct {
	int auto_add_subdev;
	int master_devid;
	int cloud_connected;
	int master_initialized;
	int subdev_index;
	int permit_join;
	void *g_user_dispatch_thread;
	int g_user_dispatch_thread_running;
} ali_user_ctx_t;

static ali_user_ctx_t g_ali_user_ctx;

static void *ali_malloc(size_t size)
{
	return HAL_Malloc(size);
}

static void ali_free(void *ptr)
{
	HAL_Free(ptr);
}

static ali_user_ctx_t *ali_user_get_ctx(void)
{
	return &g_ali_user_ctx;
}

static int user_connected_event_handler(void)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();

	ALI_TRACE("Cloud Connected");
	user_ctx->cloud_connected = 1;

	return 0;
}

static int user_disconnected_event_handler(void)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();

	ALI_TRACE("Cloud Disconnected");
	user_ctx->cloud_connected = 0;

	return 0;
}


static int user_property_set_event_handler(const int devid, const char *request, const int request_len)
{
	int res = 0;
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	ALI_TRACE("Property Set Received, Devid: %d, Request: %s", devid, request);

	res = IOT_Linkkit_Report(devid, ITM_MSG_POST_PROPERTY,
			(unsigned char *)request, request_len);
	ALI_TRACE("Post Property Message ID: %d", res);

	int id = ali_cfg_getByIot(devid);
	json_iot_analysis(devid, request);

	return 0;
}


static int user_report_reply_event_handler(const int devid, const int msgid, const int code, const char *reply,
		const int reply_len)
{
	const char *reply_value = (reply == NULL) ? ("NULL") : (reply);
	const int reply_value_len = (reply_len == 0) ? (strlen("NULL")) : (reply_len);

	ALI_TRACE("Message Post Reply Received, Devid: %d, Message ID: %d, Code: %d, Reply: %.*s", devid, msgid, code,
			reply_value_len,
			reply_value);
	return 0;
}


static int user_timestamp_reply_event_handler(const char *timestamp)
{
	ALI_TRACE("Current Timestamp: %s", timestamp);

	return 0;
}

static int user_initialized(const int devid)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	ALI_TRACE("Device Initialized, Devid: %d", devid);

	if (user_ctx->master_devid == devid) {
		user_ctx->master_initialized = 1;
		user_ctx->subdev_index++;
	}

	return 0;
}

static uint64_t user_update_sec(void)
{
	static uint64_t time_start_ms = 0;

	if (time_start_ms == 0) {
		time_start_ms = HAL_UptimeMs();
	}

	return (HAL_UptimeMs() - time_start_ms) / 1000;
}


int user_post_property(int devid, char *property_payload)
{
	//ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	//property_payload = "{\"Voltage\":223}";

	int res = IOT_Linkkit_Report(devid, ITM_MSG_POST_PROPERTY,
			(unsigned char *)property_payload, strlen(property_payload));
	ALI_TRACE("Post Property Message ID: %d", res);
	return res;
}

void user_post_event(int devid, char *event_id, char *event_payload)
{
	int res = 0;
	//	char *event_id = "Error";
	//	char *event_payload = "{\"ErrorCode\": 1}";
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();

	res = IOT_Linkkit_TriggerEvent(devid, event_id, strlen(event_id),
			event_payload, strlen(event_payload));
	ALI_TRACE("Post Event Message ID: %d", res);
}


void user_deviceinfo_update(void)
{
	int res = 0;
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	char *device_info_update = "[{\"attrKey\":\"abc\",\"attrValue\":\"hello,world\"}]";

	res = IOT_Linkkit_Report(user_ctx->master_devid, ITM_MSG_DEVICEINFO_UPDATE,
			(unsigned char *)device_info_update, strlen(device_info_update));
	ALI_TRACE("Device Info Update Message ID: %d", res);
}


void user_deviceinfo_delete(void)
{
	int res = 0;
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	char *device_info_delete = "[{\"attrKey\":\"abc\"}]";

	res = IOT_Linkkit_Report(user_ctx->master_devid, ITM_MSG_DEVICEINFO_DELETE,
			(unsigned char *)device_info_delete, strlen(device_info_delete));
	ALI_TRACE("Device Info Delete Message ID: %d", res);
}


static int user_master_dev_available(void)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	if (user_ctx->cloud_connected && user_ctx->master_initialized) {
		return 1;
	}

	return 0;
}

static int ali_add_subdev(iotx_linkkit_dev_meta_info_t *meta_info)
{
	int res = -1, devid = -1;
	devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_SLAVE, meta_info);
	if (devid == FAIL_RETURN) {
		ALI_TRACE("subdev open Failed\n");
		return FAIL_RETURN;
	}
	ALI_TRACE("subdev open susseed, devid = %d\n", devid);

	res = IOT_Linkkit_Connect(devid);
	if (res == FAIL_RETURN) {
		ALI_TRACE("subdev connect Failed\n");
		return res;
	}
	ALI_TRACE("subdev connect success: devid = %d\n", devid);

	res = IOT_Linkkit_Report(devid, ITM_MSG_LOGIN, NULL, 0);
	if (res == FAIL_RETURN) {
		ALI_TRACE("subdev login Failed\n");
		return res;
	}
	ALI_TRACE("subdev login success: devid = %d\n", devid);
	return devid;
}

int user_permit_join_event_handler(const char *product_key, const int time)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	ALI_TRACE("Product Key: %s, Time: %d", product_key, time);
	user_ctx->permit_join = 1;

	return 0;
}


void *user_dispatch_yield(void *args)
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	while (user_ctx->g_user_dispatch_thread_running) {
		IOT_Linkkit_Yield(USER_EXAMPLE_YIELD_TIMEOUT_MS);
	}

	return NULL;
}

int ali_master_init()
{
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	iotx_linkkit_dev_meta_info_t master_meta_info;

	memset(user_ctx, 0, sizeof(ali_user_ctx_t));
	HAL_GetProductKey(PRODUCT_KEY);
	HAL_GetProductSecret(PRODUCT_SECRET);
	HAL_GetDeviceName(DEVICE_NAME);
	HAL_GetDeviceSecret(DEVICE_SECRET);

	user_ctx->subdev_index = -1;
	user_ctx->auto_add_subdev = 1;

	/* Register Callback */
	IOT_RegisterCallback(ITE_CONNECT_SUCC, user_connected_event_handler);
	IOT_RegisterCallback(ITE_DISCONNECTED, user_disconnected_event_handler);
	IOT_RegisterCallback(ITE_PROPERTY_SET, user_property_set_event_handler);
	IOT_RegisterCallback(ITE_REPORT_REPLY, user_report_reply_event_handler);
	IOT_RegisterCallback(ITE_TIMESTAMP_REPLY, user_timestamp_reply_event_handler);
	IOT_RegisterCallback(ITE_INITIALIZE_COMPLETED, user_initialized);
	IOT_RegisterCallback(ITE_PERMIT_JOIN, user_permit_join_event_handler);

	memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
	memcpy(master_meta_info.product_key, PRODUCT_KEY, strlen(PRODUCT_KEY));
	memcpy(master_meta_info.product_secret, PRODUCT_SECRET, strlen(PRODUCT_SECRET));
	memcpy(master_meta_info.device_name, DEVICE_NAME, strlen(DEVICE_NAME));
	memcpy(master_meta_info.device_secret, DEVICE_SECRET, strlen(DEVICE_SECRET));

	/* Create Master Device Resources */
	user_ctx->master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
	if (user_ctx->master_devid < 0) {
		ALI_TRACE("IOT_Linkkit_Open Failed\n");
		return -1;
	}

	/* Choose Login Server */
	int domain_type = IOTX_CLOUD_REGION_SHANGHAI;
	IOT_Ioctl(IOTX_IOCTL_SET_DOMAIN, (void *)&domain_type);

	/* Choose Login Method */
	int dynamic_register = 0;
	IOT_Ioctl(IOTX_IOCTL_SET_DYNAMIC_REGISTER, (void *)&dynamic_register);

	/* Choose Whether You Need Post Property/Event Reply */
	int post_event_reply = 0;
	IOT_Ioctl(IOTX_IOCTL_RECV_EVENT_REPLY, (void *)&post_event_reply);

	/* Start Connect Aliyun Server */
	int res = IOT_Linkkit_Connect(user_ctx->master_devid);
	if (res < 0) {
		ALI_TRACE("IOT_Linkkit_Connect failed, retry after 15s...\n");
		return res;
	}

	user_ctx->g_user_dispatch_thread_running = 1;
	res = HAL_ThreadCreate(&user_ctx->g_user_dispatch_thread, user_dispatch_yield, NULL, NULL, NULL);
	if (res < 0) {
		ALI_TRACE("HAL_ThreadCreate Failed\n");
		IOT_Linkkit_Close(user_ctx->master_devid);
		return -1;
	}

	return true;
}


/* Add subdev */
int ali_subdev_add(int id)
{
	int devid = -1;
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();

	user_ctx->subdev_index = id;
	if (user_ctx->master_initialized && user_ctx->subdev_index >= 0 &&
			(user_ctx->auto_add_subdev == 1 || user_ctx->permit_join != 0)) {
		if (user_ctx->subdev_index < EXAMPLE_SUBDEV_ADD_NUM) {
			/* Add next subdev */
			devid = ali_add_subdev((iotx_linkkit_dev_meta_info_t *)&subdevArr[user_ctx->subdev_index]);
			if (devid >= SUCCESS_RETURN) {
				ALI_TRACE("subdev %s add succeed", subdevArr[user_ctx->subdev_index].device_name);
			} else {
				ALI_TRACE("subdev %s add failed", subdevArr[user_ctx->subdev_index].device_name);
			}
			user_ctx->subdev_index++;
			user_ctx->permit_join = 0;
		}
	}

	return devid;
}

int ali_subdev_remove(int devid)
{
	int res = IOT_Linkkit_Report(devid, ITM_MSG_LOGOUT, NULL, 0);
	if (res == FAIL_RETURN) {
		ALI_TRACE("subdev logout Failed\n");
		return res;
	}
	ALI_TRACE("subdev logout success: devid = %d\n", devid);

	return res;
}

void ali_set_subdevArr(uchar id, sAli *ali)
{
	int devid = -1;
	iotx_linkkit_dev_meta_info_t *sub = &(subdevArr[id]);

	memset(sub, 0, sizeof(iotx_linkkit_dev_meta_info_t));
	if(ali->en) {
		strcpy(sub->product_key, ali->key);
		strcpy(sub->product_secret, ali->pro_secret);
		strcpy(sub->device_name, ali->name);
		strcpy(sub->device_secret, ali->dev_secret);
	}
}

void ali_subdev_disconnect(sAli *ali)
{
	if(ali->iot_devid > 0) {
		ali_subdev_remove(ali->iot_devid);
		ali->iot_devid = -1;
	}
}

int ali_subdev_connect(int id)
{
	sAli *ali = ali_cfg_get(id);
	if(ali->en && user_master_dev_available()) {
		if(ali->iot_devid < 1) {
			//ali_set_subdevArr(id, ali);    //////==============
			ali->iot_devid = ali_subdev_add(id-1);
		}
	} else {
		ali_subdev_disconnect(ali);
	}

	return ali->iot_devid;
}

int ali_mqtt_pubid(int id)
{
	int ret = -1;
	if(id > EXAMPLE_SUBDEV_ADD_NUM) return ret;
	if(user_master_dev_available()) {
		ret = ali_subdev_connect(id);
	}

	return ret;
}

void ali_set_master(sAli *ali)
{
	if(ali->id == 0) {
		memset(PRODUCT_KEY, 0, sizeof(PRODUCT_KEY));
		memset(PRODUCT_SECRET, 0, sizeof(PRODUCT_SECRET));
		memset(DEVICE_NAME, 0, sizeof(DEVICE_NAME));
		memset(DEVICE_SECRET, 0, sizeof(DEVICE_SECRET));

		if(ali->en) {
			strcpy(PRODUCT_KEY, ali->key);
			strcpy(PRODUCT_SECRET, ali->pro_secret);
			strcpy(DEVICE_NAME, ali->name);
			strcpy(DEVICE_SECRET, ali->dev_secret);
		}
	}
}


void ali_subdev_quit()
{
	int i;
	for(i=1; i<=DEV_NUM; ++i) {
		int id = ali_subdev_connect(i);
		if(id > 0) ali_subdev_remove(id);

		sAli *ali = ali_cfg_get(i);
		ali->iot_devid = -1;
	}
}

int ali_quit()
{
	ali_subdev_quit();
	ali_user_ctx_t *user_ctx = ali_user_get_ctx();
	user_ctx->g_user_dispatch_thread_running = 0;
	IOT_Linkkit_Close(user_ctx->master_devid);
	HAL_ThreadDelete(user_ctx->g_user_dispatch_thread);

	user_ctx->cloud_connected =0;
	user_ctx->master_initialized = 0;
	IOT_DumpMemoryStats(IOT_LOG_DEBUG);
	IOT_SetLogLevel(IOT_LOG_NONE);

	return 0;
}


int ali_mqtt_pub(int id, char *msg)
{
	int ret = ali_mqtt_pubid(id);
	if(ret > 0) {
		ret = user_post_property(ret, msg);
	} else {
		ali_quit();
	}

	return ret;
}


int ali_master_connect()
{
	sAli *ali = ali_cfg_get(0);
	int ret = ali->en;
	if(ret) {
		ret = user_master_dev_available();
		if(!ret) {
			//ali_set_master(ali);   ///=============
			IOT_SetLogLevel(IOT_LOG_DEBUG); //IOT_LOG_DEBUG
			ret = ali_master_init();
			if(ret>0){sleep(5); rt_kprintf("ali_master_connect ok\n");};
		}
	} else {
		ret = user_master_dev_available();
		if(ret) ret = ali_quit();
	}

	return ret;
}

int ali_event_alarm(int id, int code)
{
	int ret = ali_mqtt_pubid(id);
	if(ret > 0) {
		char *event_id = "Alarm";
		char event_payload[32];
		sprintf(event_payload, "{\"AlarmCode\": %d}", code);
		user_post_event(ret, event_id, event_payload);
	}

	return ret;
}

int ali_event_error(int id, int code)
{
	int ret = ali_mqtt_pubid(id);
	if(ret > 0) {
		char *event_id = "Error";
		char event_payload[32];
		sprintf(event_payload, "{\"ErrorCode\": %d}", code);
		user_post_event(ret, event_id, event_payload);
	}

	return ret;
}

#endif















