/*
 * adc_temp.c
  *  获取CPU温度
 *  Created on: 2019年7月15日
 *      Author: luozhiyong
 */
#include <rtthread.h>
#include <rtdevice.h>

#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     16           /* ADC 通道 */
static rt_adc_device_t adc_cpu_dev = NULL;


static int adc_temp_init(void)
{
	int ret = RT_EOK;

	/* 查找设备 */
	adc_cpu_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
	if (adc_cpu_dev == RT_NULL)
	{
		rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
		return RT_ERROR;
	}

	/* 使能设备 */
	ret = rt_adc_enable(adc_cpu_dev, ADC_DEV_CHANNEL);
	return ret;
}


//获取通道ch的转换值，取times次,然后平均
//返回值:通道ch的times次转换结果平均值
static int adc_temp_average(void)
{
	int temp_val=0;
	char t, times=10;

	for(t=0;t<times;t++)
	{
		temp_val += rt_adc_read(adc_cpu_dev, ADC_DEV_CHANNEL);
		rt_thread_mdelay(5);
	}

	return temp_val/times;
}

//得到温度值
//返回值:温度值(扩大了100倍,单位:℃.)
short cpu_temp_get(void)
{
	if(!adc_cpu_dev) adc_temp_init();

	int adcx = adc_temp_average();	//读取通道16内部温度传感器通道,10次取平均
	double temperate = (float)adcx*(3.3/4096);		//电压值
	temperate=(temperate-0.76)/0.0025 + 25; //转换为温度值
	short result = temperate*=100;					//扩大100倍.

	rt_kprintf("the cpu temp is : %d.%02d \n", result / 100, result % 100);

	return result;
}


