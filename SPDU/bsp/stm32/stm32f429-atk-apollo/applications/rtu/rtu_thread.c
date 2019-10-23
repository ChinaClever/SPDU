/*
 * rtu_thread.c
 *
 *  Created on: 2019Äê10ÔÂ21ÈÕ
 *      Author: luozhiyong
 */
#include "rtu_thread.h"


static void rtu_task(int id, sRtu *rtu, sRtuRecv *rtuRecv)
{
	rtuRecv->data = data_packet_get(id);
	rtu->sentLen = rtu_sentAc(1, rtu->sentBuf);
	if(rtuRecv->data->offLine > 0) rtuRecv->data->offLine--;

	short rtn = rtu_trans(rtu);
	if(rtn > 0) {
		boolean ret = rtu_recv_packet(rtu->recvBuf, rtn, rtuRecv);
		if(ret) {
			rtuRecv->data->offLine = 3;
			rt_kprintf("rtu recv packet OK %d\n", id);
		} else {
			rt_kprintf("rtu recv packet err %d\n", id);
		}
	} else {
		//rt_kprintf("rtu recv no len err %d\n", id);
	}
}

static void rtu_thread_entry(void *arg)
{
	sRtuRecv rtuRecv;
	int i, id = (uint)arg;
	sRtu *rtu = rtu_cfg_get(id);
	rtu->dev = rtu_open(rtu->name);

	rtu->start = rtu->end = 1;
	while (1)
	{
		for(i=rtu->start; i<=rtu->end; ++i) {
			rtu_task(i, rtu, &rtuRecv);
			msleep(300);
		}
	}
}


void rtu_thread_pool(void)
{
	char name[8];
	uint i=0, num=UARTS_NUM;

	for(i=0; i<=num; ++i) {
		sprintf(name, "rtu_%d", i+1);
		rt_thread_t thread = rt_thread_create(name, rtu_thread_entry, (void *)(i), 512, 4+i, 10+i);
		if (thread != RT_NULL) {
			rt_thread_startup(thread);
		}
	}
}


