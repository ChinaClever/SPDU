/*
 * wdt.c
   *    �����ܣ�����ͨ���豸���Ʋ��ҿ��Ź��豸��Ȼ���ʼ���豸�����ÿ��Ź��豸���ʱ�䡣
   *           Ȼ�����ÿ����̻߳ص��������ڻص��������ι��
 *  Created on: 2019��10��9��
 *      Author: luozhiyong
 */
#include "iwdg.h"
#include "data_opt.h"

#if	1

//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//rlr:�Զ���װ��ֵ,0~0XFFF.
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_Init(uchar prer,ushort rlr)
{
	IWDG->KR=0X5555;//ʹ�ܶ�IWDG->PR��IWDG->RLR��д
  	IWDG->PR=prer;  //���÷�Ƶϵ��
  	IWDG->RLR=rlr;  //�Ӽ��ؼĴ��� IWDG->RLR
	IWDG->KR=0XAAAA;//reload
  	IWDG->KR=0XCCCC;//ʹ�ܿ��Ź�
}
//ι�������Ź�
void IWDG_Feed(void)
{
	IWDG->KR=0XAAAA;//reload
}

static void iwdg_entry(void *parameter)
{
    rt_thread_mdelay(5500);
    IWDG_Init(4,3*500);    	//Ԥ��Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊn*1s

    while (1)
    {
    	msleep(150);
    	IWDG_Feed();//ι��
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

#define IWDG_DEVICE_NAME    "wdt"    /* ���Ź��豸���� */
static rt_device_t wdg_dev;         /* ���Ź��豸��� */

/* �ڿ����̵߳Ļص�������ι�� */
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
    rt_uint32_t timeout = 10;    /* ���ʱ�� 10 �� */
    char device_name[RT_NAME_MAX];

    rt_strncpy(device_name, IWDG_DEVICE_NAME, RT_NAME_MAX);
    /* �����豸���Ʋ��ҿ��Ź��豸����ȡ�豸��� */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* ��ʼ���豸 */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* ���ÿ��Ź����ʱ�� */
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
    /* ���ÿ����̻߳ص����� */
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
