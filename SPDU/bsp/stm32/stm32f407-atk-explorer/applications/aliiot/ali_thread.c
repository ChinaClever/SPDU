/*
 * ali_thread.c
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */
#include "ali_thread.h"

#define PRODUCT_KEY             PKG_USING_ALI_IOTKIT_PRODUCT_KEY
#define DEVICE_NAME             PKG_USING_ALI_IOTKIT_DEVICE_NAME
#define DEVICE_SECRET           PKG_USING_ALI_IOTKIT_DEVICE_SECRET

void ali_main_task(void *arg)
{
	ushort ret = 0;
	while(1) {
		sleep(30);
		ret = ali_mqtt_isrun();
		if(!ret) {
			ali_mqtt_main(PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET);
		}
	}
}

void ali_pub_task(void *arg)
{
	ushort ret = 0;
	char *msg_pub = NULL;
	static ushort pub_msg_cnt = 1;

	while(1) {
		sleep(25);
		ret = ali_mqtt_isrun();
		if(ret) {
			msg_pub = json_iot_bulid(pub_msg_cnt++);
			ali_mqtt_pub(msg_pub);
			sleep(5);
			free(msg_pub);
		}
	}
}

void ali_thread_pool(void)
{
	thread_pool pool;

	init_thread_pool(&pool, "ali", 2, 3*1024);
	pool.add_task(&pool, ali_main_task, NULL);
	pool.add_task(&pool, ali_pub_task, NULL);
}
