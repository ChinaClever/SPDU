/*
 * wdt.c
   *    程序功能：程序通过设备名称查找看门狗设备，然后初始化设备并设置看门狗设备溢出时间。
   *           然后设置空闲线程回调函数，在回调函数里会喂狗
 *  Created on: 2019年10月9日
 *      Author: luozhiyong
 */
#include "iwdg.h"

#define IWDG_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */
static rt_device_t wdg_dev;         /* 看门狗设备句柄 */

/* 在空闲线程的回调函数里喂狗 */
static void idle_hook(void)
{
	rt_err_t ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
	if(ret != RT_EOK) {
		rt_kprintf("feed the dog err !\n ");
	}
}

static int iwdg_init()
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 10;    /* 溢出时间 10 秒 */
    char device_name[RT_NAME_MAX];

    rt_strncpy(device_name, IWDG_DEVICE_NAME, RT_NAME_MAX);
    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 初始化设备 */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 设置空闲线程回调函数 */
    rt_thread_idle_sethook(idle_hook);

    return ret;
}

static void iwdg_entry(void *parameter)
{
    rt_thread_mdelay(5500);
    iwdg_init();

    while (1)
    {
    	idle_hook();
        rt_thread_mdelay(500);
    }
}


int iwdg_thread(void)
{
	rt_thread_t tid = rt_thread_create("iwdg", iwdg_entry, RT_NULL, 512, 29, 5);
	if (tid) {
		rt_thread_startup(tid);
	}

	return 0;
}

