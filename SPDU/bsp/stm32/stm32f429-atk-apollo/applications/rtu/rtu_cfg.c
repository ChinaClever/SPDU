/*
 * rtu_cfg.c
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */
#include "rtu_cfg.h"

void rtu_env_write(sRtus *rtu)
{
	ef_set_env_blob("rtu_en", &(rtu->ac_dc), sizeof(rtu->ac_dc));
	ef_set_env_blob("rtu_port", &(rtu->portDevs), sizeof(rtu->portDevs));
}

void rtu_env_default(sRtus *rtu)
{
	rtu->ac_dc = 0;
	rtu->portDevs = UART_PORT_NUM;
	rtu_env_write(rtu);
}

void rtu_env_read(sRtus *rtu)
{
	int len = ef_get_env_blob("rtu_ac_dc", &(rtu->ac_dc), sizeof(rtu->ac_dc), NULL);
	if(len) {
		ef_get_env_blob("rtu_port_devs", &(rtu->portDevs), sizeof(rtu->portDevs), NULL);
	} else { // 读取失败，恢复默认值
		rtu_env_default(rtu);
	}
}


void rtu_cfg_pin(sRtu *rtu)
{
	switch(rtu->id) {

	}
}




void rtu_cfg_init(sRtus *rtus)
{
	short i = 0;
	for(i=0; i<UARTS_NUM; ++i) {
		sRtu *rtu =  &(rtus->rtu[i]);
		rtu->id = i;
		rtu_cfg_pin(rtu);
		rtu->cmds = list_new();  // 初始化链表
		sprintf(rtu->name, "uart%d", 3+i);
		rtu->start = i*rtus->portDevs+1;
		rtu->end = (i+1)*rtus->portDevs;
	}
}

sRtus *rtus_cfg_get(void)
{
	static sRtus *rtus = nullptr;
	if(!rtus) {
		rtus = malloc(sizeof(sRtus));
		memset(rtus, 0, sizeof(sRtus));
		rtu_env_read(rtus);
		rtu_cfg_init(rtus);
	}

	return rtus;
}



sRtu *rtu_cfg_get(int id)
{
	sRtus *rtus = rtus_cfg_get();
	return &(rtus->rtu[id]);
}

uchar rtu_cfg_ad(void)
{
	sRtus *rtus = rtus_cfg_get();
	return rtus->ac_dc;
}

sRtu *rtu_cfg_addr(uchar addr)
{
	sRtus *rtus = rtus_cfg_get();
	short id = (addr-1)/rtus->portDevs;
	return rtu_cfg_get(id);
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

