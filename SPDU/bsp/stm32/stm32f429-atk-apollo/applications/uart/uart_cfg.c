/*
 * uart_cfg.c
 *
 *  Created on: 2019Äê10ÔÂ22ÈÕ
 *      Author: luozhiyong
 */
#include "uart_cfg.h"

void uart_cfg_pin(sUart *uart)
{
	switch(uart->id) {

	}
}

void uart_cfg_init(sUarts *uarts)
{
	short i = 0;
	for(i=0; i<UARTS_NUM; ++i) {
		sUart *uart =  &(uarts->uart[i]);
		uart->id = i;
		uart_cfg_pin(uart);
		sprintf(uart->name, "uart%d", 2+i);
		uart->start = i*UART_PORT_NUM+1;
		uart->end = (i+1)*UART_PORT_NUM;
	}
}

sUart *uart_cfg_get(int id)
{
	static sUarts *uarts = nullptr;
	if(!uarts) {
		uarts = malloc(sizeof(sUarts));
		memset(uarts, 0, sizeof(sUarts));
		uart_cfg_init(uarts);
	}

	return &(uarts->uart[id]);
}

sUart *uart_cfg_device(rt_device_t dev)
{
	short i = 0;
	sUart *uart = nullptr;
	for(i=0; i<=UARTS_NUM; ++i) {
		uart = uart_cfg_get(i);
		if(uart->dev == dev) break;
	}
	return uart;
}
