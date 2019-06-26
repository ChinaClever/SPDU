/*
 * btn.c
 *
 *  Created on: 2019Äê6ÔÂ11ÈÕ
 *      Author: luozhiyong
 */
#include "btn.h"

#define    KEY_ON 		1
#define    BTN_PIN		GET_PIN(A, 0)


void Btn_Dowm_CallBack(void *btn)
{
	rt_kprintf("Button1 Click!");
}

void Btn_Double_CallBack(void *btn)
{
	rt_kprintf("Button1 Double click!");
}

void Btn_Long_CallBack(void *btn)
{
	rt_kprintf("Button1 Long press!");
}

void Btn_Continuos_CallBack(void *btn)
{
	rt_kprintf("Button1 Press continuously!");
}
void Btn_ContinuosFree_CallBack(void *btn)
{
	rt_kprintf("Button1 Press continuously free!");
}


int Read_KEY_Leve(void)
{
	return rt_pin_read(BTN_PIN);
}

int btn_task(void *arg)
{
	Button_t btn;

	rt_pin_mode(BTN_PIN, PIN_MODE_INPUT_PULLDOWN);
	Button_Create("btn", &btn, Read_KEY_Leve, KEY_ON);
	Button_Attach(&btn,BUTTON_DOWM,Btn_Dowm_CallBack);                       //Click
	Button_Attach(&btn,BUTTON_DOUBLE,Btn_Double_CallBack);                   //Double click
	Button_Attach(&btn,BUTTON_CONTINUOS,Btn_Continuos_CallBack);             //Press continuously
	Button_Attach(&btn,BUTTON_CONTINUOS_FREE,Btn_ContinuosFree_CallBack);    //Press continuously free
	Button_Attach(&btn,BUTTON_LONG,Btn_Long_CallBack);                       //Long press
	Get_Button_Event(&btn);

	while(1)
	{
		Button_Process();     //Need to call the button handler function periodically
		msleep(20);
	}
}

void btn_thread(void)
{
	rt_thread_t tid = rt_thread_create("btn",btn_task, NULL, 512, 22, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
