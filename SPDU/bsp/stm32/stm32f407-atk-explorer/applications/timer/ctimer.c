/*
 * timer.c
 *
 *  Created on: 2019��6��10��
 *      Author: luozhiyong
 */
#include "ctimer.h"

void timer_set_en(int id, boolean en)
{
	struct sTitem *it = NULL;
	it = &(getSwItem(id)->timer);
	it->en = en;
	it->id = id;
	it->openExec = 1;
	it->closeExec = 1;
}

void timer_set_time(int id, boolean en, int open, int close)
{
	struct sTitem *it = NULL;
	it = &(getSwItem(id)->timer);
	timer_set_en(id, en);

	it->open = open;
	it->close = close;
}


// ѭ����ʱ����
boolean timer_cycle_task(struct sTitem *it)
{
	boolean ret = false;
	if( it->openExec <= it->open) {
		if(it->openExec++ == 1) {
			sw_pin_write(it->id, SW_OPRN);
		}
	} else if(it->closeExec <= it->close) {
		if(it->closeExec++ == 1) {
			sw_pin_write(it->id, SW_CLOSE);
		}
	} else {
		it->openExec = it->closeExec = 1;
		ret = true;
	}

	return ret;
}

// ���ζ�ʱ����
void timer_once_task(struct sTitem *it)
{
	int ret = 0;

	if (it->openExec == 1) {
		ret = dt_cmpTimestamp(it->open);
		if(ret < 0) {
			it->openExec = 2;
			sw_pin_write(it->id, SW_OPRN);
		}
	} else if (it->closeExec == 1) {
		ret = dt_cmpTimestamp(it->close);
		if(ret < 0) {
			it->closeExec = 2;
			sw_pin_write(it->id, SW_CLOSE);
		}
	} else {
		it->en = false;
	}
}


// ÿ�춨ʱ����
void timer_daily_task(struct sTitem *it)
{
	int ret = 0;

	if (it->openExec == 1) {
		ret = dt_cmpSec(it->open);
		if(ret < 0) {
			it->openExec = 2;
			sw_pin_write(it->id, SW_OPRN);
		}
	} else  if (it->closeExec == 1) {
		ret = dt_cmpSec(it->close);
		if(ret < 0) {
			it->closeExec = 2;
			sw_pin_write(it->id, SW_CLOSE);
		}
	} else { // ��һ��ִ����׼��
		it->openExec = it->closeExec = 1;
	}
}

// ATS˫��Դ��ʱ����
void timer_ats_task(struct sTitem *it)
{
	if( it->openExec <= it->open) {
		if(it->openExec++ == 1) {
			sw_pin_write(it->id, SW_OPRN);
			sw_pin_write(it->id+1, SW_CLOSE);
		}
	} else if(it->closeExec <= it->close) {
		if(it->closeExec++ == 1) {
			sw_pin_write(it->id, SW_CLOSE);
			sw_pin_write(it->id+1, SW_OPRN);
		}
	} else {
		it->openExec = it->closeExec = 1;
	}
}

void timer_outputs_task(uchar num)
{
	uchar i = 0;
	struct sTitem *it = NULL;

	for(i=0; i<num; ++i) {
		it = &(getSwItem(i)->timer);
		switch(it->en) {
		case Daily: timer_daily_task(it); break;
		case Cycle: timer_cycle_task(it); break;
		case Once: timer_once_task(it); break;
		case Ats: timer_ats_task(it); i++; break;
		}
	}
}



void timer_seq_setEn(boolean en)
{
	struct sTitem *it = getSequence();
	it->en = en;
	it->id = 0;
	it->openExec = 1;
	it->closeExec = 1;
}


void timer_seq_setTime(boolean en, int open, int close, uchar delay)
{
	struct sTitem *it = getSequence();
	timer_seq_setEn(en);

	it->open = open;
	it->close = close;
	setDelaytm(delay);
}

// ѭ��˳��λ
void timer_seqReset_task(struct sTitem *it)
{
	boolean ret = timer_cycle_task(it);
	if(ret) { // ��λ���
		it->id++; // ��һ������
	}
}


// ѭ��˳����\�µ�
void timer_seqCycle_task(uchar num, struct sTitem *it)
{
	if( it->openExec <= it->open) {
		if(it->openExec++ == 1) {
			sw_pin_write(it->id++, SW_OPRN);
			if(it->id < num) it->openExec = 1;
		}
	} else if(it->closeExec <= it->close) {
		if(it->closeExec++ == 1) {
			sw_pin_write(it->id++, SW_CLOSE);
			if(it->id < num) it->closeExec = 1;
		}
	}else {
		it->openExec = it->closeExec = 0;
	}
}

// ÿ�춨ʱ��\�µ�
void timer_seqDaily_task(uchar num, struct sTitem *it)
{
	int ret = 0;

	if (it->openExec <= 1) {
		ret = dt_cmpSec(it->open);
		if(ret < 0) {
			sw_pin_write(it->id++, SW_OPRN);
			if(it->id >= num) it->openExec = 2;
		}
	} else  if (it->closeExec == 1) {
		ret = dt_cmpSec(it->close);
		if(ret < 0) {
			sw_pin_write(it->id, SW_CLOSE);
			if(it->id >= num) it->closeExec = 2;
		}
	} else { // ��һ��ִ����׼��
		it->openExec = it->closeExec = 1;
	}
}

// ���ζ�ʱ����
void timer_seqOnce_task(uchar num, struct sTitem *it)
{
	int ret = 0;

	if (it->openExec == 1) {
		ret = dt_cmpTimestamp(it->open);
		if(ret < 0) {
			sw_pin_write(it->id++, SW_OPRN);
			if(it->id >= num) it->openExec = 2;
		}
	} else if (it->closeExec == 1) {
		ret = dt_cmpTimestamp(it->close);
		if(ret < 0) {
			sw_pin_write(it->id++, SW_CLOSE);
			if(it->id >= num) it->closeExec = 2;
		}
	} else {
		it->en = false;
	}
}

boolean timer_seq_task(uchar num)
{
	static uchar count = 0;
	struct sTitem *it = getSequence();
	uchar tm = getDelaytm();
	if(count++ > tm) {
		switch(it->en) {
		case Daily: timer_seqDaily_task(num, it); break; //
		case Cycle: timer_seqCycle_task(num, it); break;
		case Once: timer_seqOnce_task(num, it); break; //
		case Ats: timer_seqReset_task(it); break;
		}
		if(it->id >= num) it->id = 0;
		count = 0;
	}

	return it->en;
}


void timer_task(void *arg)
{
	uchar num, ret;

	while(1) {
		num = getOutputNum();
		ret = timer_seq_task(num); // �����ȼ�
		if(!ret) {
			timer_outputs_task(num);
		}

		ret = 1000 + rand()%550;
		msleep(ret);
	}
}

void timer_thread(void)
{
	rt_thread_t tid = rt_thread_create("timer",timer_task, NULL, 2*512, 23, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
