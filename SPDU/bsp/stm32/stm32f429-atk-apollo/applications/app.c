/*
 * app.c
 *
 *  Created on: 2019��6��26��
 *      Author: luozhiyong
 */
//#include "btn.h"
#include "cpu_temp.h"
#include "rtu_thread.h"
#include "web_main.h"

extern int manager_main();
//extern void telnet_server(void);

void app_thread(void)
{
	modbus_thread();
	net_work_thread();
	mqtt_work_thread();

//	btn_thread();
//	ali_thread();
	web_main();
	rtu_thread_pool();
	manager_main();

//	snmp_main();
//	telnet_server();
//	cpu_temp_get();
}

