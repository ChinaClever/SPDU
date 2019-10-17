/*
 * app.c
 *
 *  Created on: 2019Äê6ÔÂ26ÈÕ
 *      Author: luozhiyong
 */
//#include "btn.h"
#include "cpu_temp.h"
#include "web_main.h"

//extern void telnet_server(void);

void app_thread(void)
{
//	timer_thread();
//	modbus_thread();
//	net_work_thread();
//	mqtt_work_thread();

//	btn_thread();
//	ali_thread();
	web_main();
	//wdt_init();

//	snmp_main();
//	telnet_server();
//	cpu_temp_get();
}

