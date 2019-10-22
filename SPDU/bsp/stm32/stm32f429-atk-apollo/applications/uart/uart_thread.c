/*
 * uart_thread.c
 *
 *  Created on: 2019年10月21日
 *      Author: luozhiyong
 */
#include "uart_thread.h"

static void serial_thread_entry(void *parameter)
{
    int rx_length;

    sUart *uart = uart_cfg_get(0);
    uart->dev = uart_open(uart->name);

    while (1)
    {
    	sprintf(uart->sentBuf,"luozhiyong\n");
    	uart->sentLen = strlen(uart->sentBuf);

    	rx_length = uart_trans(uart);
    	if(rx_length > 0) {
    		rt_kprintf("%s\n", uart->recvBuf);
//    		 rx_buffer[rx_length] = '\0';
//    		 uart_write(serial, rx_buffer, rx_length);
    	} else {
    		rt_kprintf("AAAAAAAA %d\n", rx_length);
    	}
    	sleep(1);
    }
}


int uart_sample(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL) {
        rt_thread_startup(thread);
    } else {
        ret = RT_ERROR;
    }

    return ret;
}


