/*
 * ali_thread.c
 *
 *  Created on: 2019��6��17��
 *      Author: luozhiyong
 */
#include "ali_thread.h"


void ali_pub_task()
{
	int i, ret = 0;
	char *msg_pub = NULL;

	sleep(10);
	while(1) {
		ali_master_connect();
		for(i=0; i<DEV_NUM; ++i) {
			sleep(1);
			ret = ali_subdev_connect(i);
			if(ret > 0) {
				msg_pub = json_iot_bulid(i);
				if(msg_pub) {
					ali_mqtt_pub(i, msg_pub);
					msleep(100); free(msg_pub);
				}
			}
		}
	}
}


void ali_thread(void)
{
	rt_thread_t tid = rt_thread_create("ali",ali_pub_task, NULL,7*1024,19, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
