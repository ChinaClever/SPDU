/*
 * ali_ota.c
 *
 *  Created on: 2019Äê11ÔÂ1ÈÕ
 *      Author: luozhiyong
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "infra_compat.h"
#include "mqtt_api.h"
#include "ota_api.h"

#include "rtthread.h"
#include <fal.h>
#include "ali_iot.h"

static char g_product_key[IOTX_PRODUCT_KEY_LEN + 1];
static char g_product_secret[IOTX_PRODUCT_SECRET_LEN + 1];
static char g_device_name[IOTX_DEVICE_NAME_LEN + 1];
static char g_device_secret[IOTX_DEVICE_SECRET_LEN + 1];

void *HAL_Malloc(uint32_t size);
void HAL_Free(void *ptr);

void HAL_Printf(const char *fmt, ...);
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN]);
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN]);
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);
void HAL_SleepMs(uint32_t ms);

#define OTA_BUF_LEN        (5000)
#define OTA_MQTT_MSGLEN         (2048)

#define OTA_TRACE(fmt, ...)  \
		do { \
			HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
			HAL_Printf(fmt, ##__VA_ARGS__); \
			HAL_Printf("%s", "\r\n"); \
		} while(0)



static void ota_event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
	uintptr_t packet_id = (uintptr_t)msg->msg;
	iotx_mqtt_topic_info_pt topic_info = (iotx_mqtt_topic_info_pt)msg->msg;

	switch (msg->event_type) {
	case IOTX_MQTT_EVENT_UNDEF:
		OTA_TRACE("undefined event occur.");
		break;

	case IOTX_MQTT_EVENT_DISCONNECT:
		OTA_TRACE("MQTT disconnect.");
		break;

	case IOTX_MQTT_EVENT_RECONNECT:
		OTA_TRACE("MQTT reconnect.");
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_SUCCESS:
		OTA_TRACE("subscribe success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_TIMEOUT:
		OTA_TRACE("subscribe wait ack timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_SUBCRIBE_NACK:
		OTA_TRACE("subscribe nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_SUCCESS:
		OTA_TRACE("unsubscribe success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_TIMEOUT:
		OTA_TRACE("unsubscribe timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_UNSUBCRIBE_NACK:
		OTA_TRACE("unsubscribe nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_SUCCESS:
		OTA_TRACE("publish success, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_TIMEOUT:
		OTA_TRACE("publish timeout, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_NACK:
		OTA_TRACE("publish nack, packet-id=%u", (unsigned int)packet_id);
		break;

	case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
		OTA_TRACE("topic message arrived but without any related handle: topic=%.*s, topic_msg=%.*s",
				topic_info->topic_len,
				topic_info->ptopic,
				topic_info->payload_len,
				topic_info->payload);
		break;

	default:
		OTA_TRACE("Should NOT arrive here.");
		break;
	}
}

static void *ali_ota_init(void)
{
	iotx_conn_info_pt pconn_info;
	iotx_mqtt_param_t mqtt_params;

	/**< get device info*/
	HAL_GetProductKey(g_product_key);
	HAL_GetDeviceName(g_device_name);
	HAL_GetDeviceSecret(g_device_secret);
	/**< end*/

	/* Device AUTH */
	int rc = IOT_SetupConnInfo(g_product_key, g_device_name, g_device_secret, (void **)&pconn_info);
	if (0 != rc) {
		OTA_TRACE("AUTH request failed!");
		return NULL;
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
	mqtt_params.read_buf_size = OTA_MQTT_MSGLEN;
	mqtt_params.write_buf_size = OTA_MQTT_MSGLEN;

	mqtt_params.handle_event.h_fp = ota_event_handle;
	mqtt_params.handle_event.pcontext = NULL;


	/* Construct a MQTT client with specify parameter */
	void *pclient = IOT_MQTT_Construct(&mqtt_params);
	if (NULL == pclient) {
		OTA_TRACE("MQTT construct failed");
		return NULL;
	}

	return pclient;
}

static const struct fal_partition *ali_ota_fal(void)
{
	static const struct fal_partition *dl_part = RT_NULL;
	if(!dl_part) dl_part = fal_partition_find("download");
	if(!dl_part) OTA_TRACE("Ali Ota Firmware download failed! Partition (%s) find error!", "download");

	return dl_part;
}

static int ali_ota_erase(const struct fal_partition *dl_part, uint addr, ushort len)
{
	int size = 2*len;
	int ret = fal_partition_erase(dl_part, 0, size);
	if (ret < 0){
		OTA_TRACE("Ali Ota Firmware download failed! Partition (%s) erase error!", dl_part->name);
		return -RT_ERROR;
	}

	return ret;
}

static int ali_ota_write(char *buf, ushort len)
{
	static uint addr = 0;
	const struct fal_partition *dl_part = ali_ota_fal();
	if(dl_part) {
		int ret = ali_ota_erase(dl_part, addr, len);
		if(ret >= 0) {
			ret = fal_partition_write(dl_part, addr, buf, len);
			if(ret<0) {
				OTA_TRACE("Ali Ota Firmware download failed! Partition (%s) write data error!", dl_part->name);
				return -RT_ERROR;
			} else {
				addr += len;
			}
		}
	}

	return 1;
}

static int ali_ota_reset(void)
{
	OTA_TRACE("Ali Ota Download firmware to flash success.");
	OTA_TRACE("Ali Ota System now will restart...");

	rt_thread_delay(rt_tick_from_millisecond(5));

	/* Reset the device, Start new firmware */
	extern void rt_hw_cpu_reset(void);
	rt_hw_cpu_reset();

	return RT_EOK;
}

static int ali_ota_recv(void *pclient, void *h_ota)
{
	int ota_over = 0;
	char *buf_ota = (char *)HAL_Malloc(OTA_MQTT_MSGLEN);
	if (NULL == buf_ota) {
		OTA_TRACE("not enough memory");
		return -1;
	}

	do {
		uint32_t firmware_valid;
		OTA_TRACE("wait ota upgrade command....");
		/* handle the MQTT packet received from TCP or SSL connection */
		IOT_MQTT_Yield(pclient, 200);

		if (IOT_OTA_IsFetching(h_ota)) {
			uint32_t last_percent = 0, percent = 0;
			char md5sum[33];
			char version[128] = {0};
			uint32_t len, size_downloaded, size_file;
			do {
				len = IOT_OTA_FetchYield(h_ota, buf_ota, OTA_BUF_LEN, 1);
				if (len > 0) {
					if (1 != ali_ota_write(buf_ota, len)) {
						OTA_TRACE("Ali Ota write data to file failed");
						break;
					}
					OTA_TRACE("Here write OTA data to file or flash....");
				} else {
					IOT_OTA_ReportProgress(h_ota, IOT_OTAP_FETCH_FAILED, NULL);
					OTA_TRACE("ota fetch fail");
				}

				/* get OTA information */
				IOT_OTA_Ioctl(h_ota, IOT_OTAG_FETCHED_SIZE, &size_downloaded, 4);
				IOT_OTA_Ioctl(h_ota, IOT_OTAG_FILE_SIZE, &size_file, 4);
				IOT_OTA_Ioctl(h_ota, IOT_OTAG_MD5SUM, md5sum, 33);
				IOT_OTA_Ioctl(h_ota, IOT_OTAG_VERSION, version, 128);

				last_percent = percent;
				percent = (size_downloaded * 100) / size_file;
				if (percent - last_percent > 0) {
					IOT_OTA_ReportProgress(h_ota, percent, NULL);
					IOT_OTA_ReportProgress(h_ota, percent, "hello");
				}
				IOT_MQTT_Yield(pclient, 100);
			} while (!IOT_OTA_IsFetchFinish(h_ota));

			IOT_OTA_Ioctl(h_ota, IOT_OTAG_CHECK_FIRMWARE, &firmware_valid, 4);
			if (0 == firmware_valid) {
				OTA_TRACE("The firmware is invalid");
			} else {
				OTA_TRACE("The firmware is valid");
			}

			ota_over = 1;
		}
		HAL_SleepMs(2000);
	} while (!ota_over);

	HAL_SleepMs(200);
	if (NULL != buf_ota) {
		HAL_Free(buf_ota);
	}

	return ota_over;
}

static void ali_ota_task(void *p)
{
	int rc = 0;
	OTA_TRACE("ali ota main func");
	IOT_SetLogLevel(IOT_LOG_DEBUG);

	void *pclient = ali_ota_init();
	if(pclient) {
		void *h_ota = IOT_OTA_Init(g_product_key, g_device_name, pclient);
		if(h_ota) {
			/* if (0 != IOT_OTA_ReportVersion(h_ota, "iotx_ver_1.1.0")) { */
			/* rc = -1; */
			/* OTA_TRACE("report OTA version failed"); */
			/* goto do_exit; */
			/* } */

			HAL_SleepMs(1500);
			rc = ali_ota_recv(pclient, h_ota);
			if(rc) {
				ali_ota_reset();
			}
			IOT_OTA_Deinit(h_ota);

		} else {
			IOT_MQTT_Destroy(&pclient);
			OTA_TRACE("initialize OTA failed");
		}
	}


	if(pclient)IOT_MQTT_Destroy(&pclient);
	IOT_DumpMemoryStats(IOT_LOG_DEBUG);
	OTA_TRACE("ali ota out of sample!");
}

void ali_ota_thread(void)
{
	rt_thread_t tid = rt_thread_create("ali",ali_ota_task, NULL,6*1024,17, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
