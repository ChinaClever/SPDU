/*
 * rtu_cfg.c
 *
 *  Created on: 2019Äê10ÔÂ22ÈÕ
 *      Author: luozhiyong
 */
#include "rtu_cfg.h"

void rtu_cfg_pin(sRtu *rtu)
{
	switch(rtu->id) {

	}
}

void rtu_cfg_init(sRtus *rtus)
{
	short i = 0;
	for(i=0; i<=UARTS_NUM; ++i) {
		sRtu *rtu =  &(rtus->rtu[i]);
		rtu->id = i;
		rtu_cfg_pin(rtu);
		sprintf(rtu->name, "uart%d", 2+i);
		rtu->start = i*UART_PORT_NUM+1;
		rtu->end = (i+1)*UART_PORT_NUM;
	}
}

sRtu *rtu_cfg_get(int id)
{
	static sRtus *rtus = nullptr;
	if(!rtus) {
		rtus = malloc(sizeof(sRtus));
		memset(rtus, 0, sizeof(sRtus));
		rtu_cfg_init(rtus);
	}

	return &(rtus->rtu[id]);
}

sRtu *rtu_cfg_device(rt_device_t dev)
{
	short i = 0;
	sRtu *rtu = nullptr;
	for(i=0; i<=UARTS_NUM; ++i) {
		rtu = rtu_cfg_get(i);
		if(rtu->dev == dev) break;
	}
	return rtu;
}
