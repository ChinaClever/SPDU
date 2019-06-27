/*
 * app.c
 *
 *  Created on: 2019Äê6ÔÂ26ÈÕ
 *      Author: luozhiyong
 */
#include "btn.h"
#include "ctimer.h"
#include "modbus_server.h"
#include "ali_thread.h"
#include "network.h"

void app_thread_pool(void)
{
	timer_thread();
	modbus_thread();
	net_work_thread();

//	btn_thread();
//	ali_thread();
	web_main();
}

