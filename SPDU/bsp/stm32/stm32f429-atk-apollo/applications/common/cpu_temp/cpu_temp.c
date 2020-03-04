/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-21     Lzy       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_ADC1

#define ADC_DEV_NAME        "adc1"      /* ADC �豸���� */
#define ADC_CH_TEMP     18          //ͨ��18,�ڲ��¶ȴ�����ר��ͨ��
#define ADC_DEV_CHANNEL     ADC_CH_TEMP           /* ADC ͨ�� */
static rt_adc_device_t adc_cpu_dev = NULL;

static int adc_temp_init(void)
{
    int ret = RT_EOK;

    /* �����豸 */
    adc_cpu_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_cpu_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    /* ʹ���豸 */
    ret = rt_adc_enable(adc_cpu_dev, ADC_DEV_CHANNEL);
    return ret;
}


//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ��
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
static int adc_temp_average(void)
{
    int temp_val=0;
    char t, times=10;

    for(t=0;t<times;t++)
    {
        rt_thread_mdelay(5);
        temp_val += rt_adc_read(adc_cpu_dev, ADC_DEV_CHANNEL);
    }

    return temp_val/times;
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��,��λ:��.)
short cpu_temp_get(void)
{
    if(!adc_cpu_dev) {
        adc_temp_init();
        rt_thread_mdelay(100);
    }

    int adcx = adc_temp_average();  //��ȡͨ��16�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
    double temperate = (float)adcx*(3.3/4096);      //��ѹֵ
    temperate=(temperate-0.76)/0.0025 + 25; //ת��Ϊ�¶�ֵ
    short result = temperate*=100;                  //����100��.

    return result;
}


static void cpu_temp_entry(void *p)
{
    rt_thread_mdelay(200);
    short result = cpu_temp_get();
    rt_kprintf(" [TEMP] STM32F429 the cpu temp is : %d.%02d \n", result / 100, result % 100);
}

static int cpu_temp_thread(void)
{
    rt_thread_t thread = rt_thread_create("cputemp", cpu_temp_entry, NULL, 512, 3, 5);
    if (thread != RT_NULL)  rt_thread_startup(thread);
    return 0;
}

INIT_ENV_EXPORT(cpu_temp_thread);
#endif
