/*
 * wdt.c
   *    程序功能：程序通过设备名称查找看门狗设备，然后初始化设备并设置看门狗设备溢出时间。
   *           然后设置空闲线程回调函数，在回调函数里会喂狗
 *  Created on: 2019年10月9日
 *      Author: luozhiyong
 */
#include "iwdg.h"
#include "data_opt.h"

#if	1

//初始化独立看门狗
//prer:分频数:0~7(只有低3位有效!)
//rlr:自动重装载值,0~0XFFF.
//分频因子=4*2^prer.但最大值只能是256!
//rlr:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_Init(uchar prer,ushort rlr)
{
	IWDG->KR=0X5555;//使能对IWDG->PR和IWDG->RLR的写
  	IWDG->PR=prer;  //设置分频系数
  	IWDG->RLR=rlr;  //从加载寄存器 IWDG->RLR
	IWDG->KR=0XAAAA;//reload
  	IWDG->KR=0XCCCC;//使能看门狗
}
//喂独立看门狗
void IWDG_Feed(void)
{
	IWDG->KR=0XAAAA;//reload
}

static void iwdg_entry(void *parameter)
{
    rt_thread_mdelay(5500);
    IWDG_Init(4,3*500);    	//预分频数为64,重载值为500,溢出时间为n*1s

    while (1)
    {
    	msleep(150);
    	IWDG_Feed();//喂狗
    }
}


int iwdg_thread(void)
{
	rt_thread_t tid = rt_thread_create("iwdg", iwdg_entry, RT_NULL, 256, 29, 5);
	if (tid) {
		rt_thread_startup(tid);
	}

	return 0;
}

#else

#define IWDG_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */
static rt_device_t wdg_dev;         /* 看门狗设备句柄 */

/* 在空闲线程的回调函数里喂狗 */
static void idle_hook(void)
{
	rt_err_t ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
	if(ret != RT_EOK) {
		rt_kprintf("feed the dog err !\n ");
	} else {
		 rt_kprintf("feed the dog!\n ");
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
        rt_thread_mdelay(150);
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

#endif
