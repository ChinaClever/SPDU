/*
 * swctr.c
 *
 *  Created on: 2019年6月10日
 *      Author: luozhiyong
 */
#include "swctr.h"

#define PCF8574_I2C_BUS    "i2c1"
#define PCF8574_NUM 	(((OUTPUT_NUM_MAX-1)/8)+1)

#define PCF8574_ADDR_1 	PCF8574_ADDR_DEFAULT   //  0x20
#define PCF8574_ADDR_2 	0x27
#define PCF8574_ADDR_3 	0x21

/* 指向互斥量的指针 */
static rt_mutex_t dynamic_mutex = RT_NULL;
static pcf8574_device_t gPcfDev[3] = {RT_NULL, RT_NULL, RT_NULL};
static uchar pcf8574_dev_addr[3] = {PCF8574_ADDR_1, PCF8574_ADDR_2, PCF8574_ADDR_3};

#define SW_EN 0  // 因为还没有硬件，所以暂时不用

boolean sw_init(void)
{
	uchar i;
	pcf8574_device_t dev = RT_NULL;

	for(i=0; i<PCF8574_NUM; ++i) {
		dev = pcf8574_init(PCF8574_I2C_BUS, pcf8574_dev_addr[i]);
		if (dev) gPcfDev[i] = dev;
		else return false;
	}

	/* 创建一个动态互斥量 */
	dynamic_mutex = rt_mutex_create("dmutex", RT_IPC_FLAG_FIFO);

	return true;
}

void sw_deinit(void)
{
	uchar i;
	pcf8574_device_t dev = RT_NULL;

	for(i=0; i<PCF8574_NUM; ++i) {
		dev = gPcfDev[i];
		if(dev) pcf8574_deinit(dev);
	}
}

boolean sw_pin_write(int pin, int v)
{
	boolean ret = true;
#if SW_EN
	rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
	pcf8574_device_t dev = gPcfDev[pin/8];
	if(dev) {
		pcf8574_pin_write(dev, pin%8, v);
		setSwStatus(pin, v);
	} else {
		ret = false;
	}
	msleep(80);// 等上电稳定，再执行
	rt_mutex_release(dynamic_mutex);
#else
	setSwStatus(pin, v);
#endif

	return ret;
}

void sw_all_write(int v)
{
	uchar i, value=0;
	pcf8574_device_t dev = RT_NULL;
	if(v) value = 0xff;
#if SW_EN
	rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
	for(i=0; i<PCF8574_NUM; ++i) {
		dev = gPcfDev[i];
		if(dev) {
			pcf8574_port_write(dev,value);
		}
	}
	setAllSwStatus(v);
	rt_mutex_release(dynamic_mutex);
#else
	setAllSwStatus(v);
#endif
}

int sw_pin_read(int pin)
{
	int ret = 0;
#if SW_EN
	rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
	pcf8574_device_t dev = gPcfDev[pin/8];
	if(dev) {
		ret = pcf8574_pin_read(dev, pin%8);
		setSwStatus(pin, ret);
	}else {
		ret = -1;
	}
	rt_mutex_release(dynamic_mutex);
#else
	ret = getSwStatus(pin);
#endif
	return ret;
}


static int output_sw_write(int argc, char **argv)
{
	if (argc != 3)
	{
		rt_kprintf("Input param error! Example: output_sw_write 1 0\n");
		return -1;
	}

	int id = atoi(argv[1])-1;
	int v = atoi(argv[2]);
	int ret = sw_pin_write(id, v);
	rt_kprintf("%d\n", ret);

	return ret;
}


static int output_sw_read(int argc, char **argv)
{
	if (argc != 2)
	{
		rt_kprintf("Input param error! Example: output_sw_read 1\n");
		return -1;
	}

	int id = atoi(argv[1])-1;
	int ret = sw_pin_read(id);
	rt_kprintf("%d\n", ret);

	return ret;
}


#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(output_sw_write, write output swtch);
FINSH_FUNCTION_EXPORT(output_sw_read, read output swtch);
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(output_sw_write, write output swtch)
MSH_CMD_EXPORT(output_sw_read, read output swtch)
#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
