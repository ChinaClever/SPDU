/*
 * app.c
 *
 *  Created on: 2019��6��26��
 *      Author: luozhiyong
 */
#include "btn.h"
#include "ctimer.h"
#include "modbus_server.h"
#include "ali_thread.h"

void app_thread_pool(void)
{
	modbus_thread();
	timer_thread();
//	btn_thread();
//	ali_thread();
	web_main();
}

