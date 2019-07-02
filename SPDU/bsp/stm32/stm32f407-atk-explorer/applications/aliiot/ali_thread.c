/*
 * ali_thread.c
 *
 *  Created on: 2019Äê6ÔÂ17ÈÕ
 *      Author: luozhiyong
 */
#include "ali_thread.h"



void ali_main_task(void *arg)
{
	ushort ret = 0;
	struct sAli *ali = ali_cfg_get();

	while(1) {
		sleep(5);
		if(ali->en) {
			ret = ali_mqtt_isrun();
			if(!ret) {
				ali_mqtt_main(ali->key, ali->name, ali->secret);
			} else {
				sleep(30);
			}
		}
	}
}

void ali_pub_task(void *arg)
{
	ushort ret = 0;
	char *msg_pub = NULL;
	static ushort pub_msg_cnt = 1;
	struct sAli *ali = ali_cfg_get();

	while(1) {
		sleep(30);
		if(ali->en) {
			ret = ali_mqtt_isrun();
			if(ret) {
				msg_pub = json_iot_bulid(pub_msg_cnt++);
				ali_mqtt_pub(msg_pub);
				sleep(5);
				free(msg_pub);
			}
		}
	}
}

void ali_thread(void)
{
	rt_thread_t tid = rt_thread_create("ali_main",ali_main_task, NULL,1*512,19, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);

	tid = rt_thread_create("ali_pub",ali_pub_task, NULL,3*512,18, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

