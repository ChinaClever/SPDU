/*
 * app.c
 *
 *  Created on: 2019Äê6ÔÂ26ÈÕ
 *      Author: luozhiyong
 */
//#include "btn.h"
#include "cpu_temp.h"
#include "rtu_thread.h"
#include "web_main.h"
#include "dt_dingtalk.h"
#include "iwdg.h"

extern int manager_main();
//extern void telnet_server(void);

void app_thread(void)
{
	modbus_thread();
	net_work_thread();
	mqtt_work_thread();

//	btn_thread();
	ali_thread();
	web_main();
	rtu_thread_pool();
	manager_main();

//	char *data = "this is text";
//	dt_talk(data);

//	snmp_main();
//	telnet_server();
	iwdg_thread();
	cpu_temp_get();
}

