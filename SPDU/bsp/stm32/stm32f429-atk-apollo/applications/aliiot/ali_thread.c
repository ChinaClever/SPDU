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
	char *msg_pub = "{\"Voltage\":223}"; //NULL;

	sleep(10);
	while(1)
	{
		ret = ali_master_connect();
		if(ret>0) {
			for(i=1; i<=DEV_NUM; ++i) {
//				msg_pub = json_iot_bulid(i);  /////=========
				if(msg_pub)	{
					ret = ali_subdev_connect(i);
					if(ret > 0) {
						ret = ali_mqtt_pub(i, msg_pub);
					}
					msleep(300);
					break; //////============
					free(msg_pub);
				}
			}
		}

		if(ret > 0) ret = 10;
		else ret = 1;
		sleep(ret);
	}
}


void ali_thread(void)
{
	rt_thread_t tid = rt_thread_create("ali",ali_pub_task, NULL,6*1024,19, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

