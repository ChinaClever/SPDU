/*
 * uarts.c
 *
 *  Created on: 2019年10月21日
 *      Author: luozhiyong
 */
#include "uart_device.h"

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
	sUart *uart = uart_cfg_device(dev);
	uart->recvLen = size;

	return size;
}

static int uart_write(sUart *uart)
{
	//rt_pin_write(uart->pin, PIN_LOW); msleep(1);
	int ret = rt_device_write(uart->dev, 0, uart->sentBuf, uart->sentLen);
	if(ret > 0) {
		// msleep(UART_DELAY); rt_pin_write(uart->pin, PIN_HIGH);
		uart->recvLen = 0;
		uart->sentLen = 0;
	}

	return ret;
}

static int uart_read(rt_device_t dev, uchar *buf)
{
	int ret, rtn=0;

	do {
		ret = rt_device_read(dev, 0, buf, UART_RECV_SIZE); //RT_SERIAL_RB_BUFSZ;
		if(ret > 0) {
			buf[ret] = 0;
			buf += ret;
			rtn += ret;
			msleep(UART_DELAY);
		}
	} while(ret > 0);

	return rtn;
}

static int uart_recv(sUart *uart)
{
	short i, rtn=0, delay_ms=UART_TIMEOUT/UART_DELAY;

	for(i=0; i<delay_ms; ++i) {
		rtn = uart_read(uart->dev, uart->recvBuf);
		if(rtn > 0) {
			uart->recvLen = rtn;
			break;
		} else {
			msleep(UART_DELAY);
		}
	}

	return rtn;
}



static void uart_lock(sUart *uart)
{
	while(uart->lock) {
		msleep(UART_DELAY);
	}
	uart->lock = true;
}

static void uart_unlock(sUart *uart)
{
	msleep(UART_DELAY);
	uart->lock = false;
}

int uart_trans(sUart *uart)
{
	uart_lock(uart);
	int ret = uart_write(uart);
	if(ret > 0) {
		ret = uart_recv(uart);
	}
	uart_unlock(uart);

	return ret;
}

int uart_sent(sUart *uart)
{
	uart_lock(uart);
	int ret = uart_write(uart);
	msleep(2*UART_DELAY);
	uart_unlock(uart);

	return ret;
}


rt_err_t uart_control(rt_device_t dev)
{
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; /* 配置参数 */

	config.baud_rate = BAUD_RATE_115200;
	config.data_bits = DATA_BITS_8;
	config.stop_bits = STOP_BITS_1;
	config.parity = PARITY_NONE;

	return rt_device_control(dev, RT_DEVICE_CTRL_CONFIG, &config);
}

rt_device_t uart_open(char *name)
{
	char uart_name[RT_NAME_MAX];
	rt_strncpy(uart_name, name, RT_NAME_MAX);

	rt_device_t  serial = rt_device_find(uart_name);  /* 查找串口设备 */
	if (serial) {
		rt_device_open(serial, RT_DEVICE_FLAG_DMA_RX); /* 以 DMA 接收及轮询发送方式打开串口设备 */
		//rt_device_set_rx_indicate(serial, uart_input); /* 设置接收回调函数 */
		uart_control(serial);
	} else {
		rt_kprintf("find %s failed!\n", uart_name);
		return NULL;
	}

	return serial;
}





