/*
 * app.c
 *
 *  Created on: 2019Äê6ÔÂ26ÈÕ
 *      Author: luozhiyong
 */
#include "btn.h"
#include "ctimer.h"
#include "web_main.h"

void app_thread_pool(void)
{
	timer_thread();
//	modbus_thread();
//	net_work_thread();
//	mqtt_work_thread();

//	btn_thread();
//	ali_thread();
	web_main();
}

