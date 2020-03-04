/*
 * devDataSent.c
 *
 *  Created on: 2016��7��29��
 *      Author: Lzy
 */
#include "devDataSent.h"
#include <stdlib.h>

/**
 * ���͹���״̬
 */
void sent_devStatus(dev_data_packet *msg, uchar status)
{
	msg->len = 1;
	msg->data = &status;

	msg->fn[0] = 0;
	msg->fn[1] = 0;
	data_packet_sent(msg);
}


/**
 * �������ݰ�
 *  �������ݵ����������ݳ��ȴ���0 ��������ַ��Ч
 */
static void sent_packet(dev_data_packet *msg)
{
	if(msg) {
		if(msg->len > 0) // ����������
		{
			if(msg->data) // ����ָ����Ч
				data_packet_sent(msg);
		}
	}
}

/**
 * ��  �ܣ������α���ַ���������
 * ��ڲ�����from-> ������Դ��len-> ���ݳ���
 * ���ڲ�����to->���ݻ�����
 * ��  �أ����ݳ���
 */
static int shortToChar(ushort *form, int len, uchar *to)
{
	int i, offset=0;
	if(form)
	{
		memset(to,0, DATA_MSG_SIZE);
		for(i=0; i<len; ++i)
		{
			to[offset++] = form[i] >> 8; // ��λ
			to[offset++] = form[i] & 0xFF; // ��8λ
		}
	}

	return offset;
}

/**
 * ��  �ܣ����α���ַ���������
 * ��ڲ�����from-> ������Դ��len-> ���ݳ���
 * ���ڲ�����to->���ݻ�����
 * ��  �أ����ݳ���
 */
static int intToChar(uint *form, int len, uchar *to)
{
	int i, offset=0;

	if(form)
	{
		memset(to,0, DATA_MSG_SIZE);
		for(i=0; i<len; ++i)
		{
			to[offset++] = form[i] >> 24; // ��λ
			to[offset++] = (form[i] >> 16) & 0xFF;
			to[offset++] = (form[i] >> 8) & 0xFF;
			to[offset++] = form[i] & 0xFF; // ��8λ
		}
	}

	return offset;
}

/**
 * ��  �ܣ��������ݵ�Ԫ����
 * ��  ����unit->���ݵ�Ԫ�ṹ��
 * 		  buf->�������ݻ�����
 * 		  len-> ���ݳ���
 */
static void sent_unit(_devDataUnit *unit, int len, uchar *buf, dev_data_packet *msg)
{
	int fn=1, fc = msg->fn[1];
	if(!unit) return;

	/* ���͵�ǰֵ */
	msg->fn[1] = fc + fn++;
	msg->data = buf;
	msg->len = shortToChar(unit->value,len,buf);
	sent_packet(msg);

	/*������Сֵ*/
	msg->fn[1] = fc + fn++;
	msg->len = shortToChar(unit->min,len,buf);
	sent_packet(msg);

	/*�������ֵ*/
	msg->fn[1] = fc + fn++;
	msg->len = shortToChar(unit->max,len,buf);
	sent_packet(msg);

	/*���ͱ���*/
	msg->fn[1] = fc + fn++;
	msg->len = len;
	msg->data = unit->alrm;
	sent_packet(msg);

	/*�����ٽ���Сֵ*/
	msg->fn[1] = fc + fn++;
	msg->data = buf;
	msg->len = shortToChar(unit->crMin,len,buf);
	sent_packet(msg);

	/*�����ٽ����ֵ*/
	msg->fn[1] = fc + fn++;
	msg->data = buf;
	msg->len = shortToChar(unit->crMax,len,buf);
	sent_packet(msg);

	/*�����ٽ籨��*/
	msg->fn[1] = fc + fn++;
	msg->len = len;
	msg->data = unit->crAlrm;
	sent_packet(msg);
}

/**
 * �� �ܣ��������ݶ��� ������������ѹ�����ʡ����ܡ��������ص�
 */
static void sent_object(_devDataObj *obj, uchar *buf, dev_data_packet *msg)
{
	if(!obj) return;
	int fn=0, len = obj->len;

	/*����*/
	fn += 1;
	msg->fn[1] = fn << 4;
	sent_unit(&(obj->cur), len, buf, msg);

	/*��ѹ*/
	fn += 1;
	msg->fn[1] = fn << 4;
	sent_unit(&(obj->vol), len, buf, msg);

	/*����*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = buf;
	msg->len = intToChar(obj->pow,len,buf); // ����
	sent_packet(msg);

	/*����*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = buf;
	msg->len = intToChar(obj->ele,len,buf); // ����
	sent_packet(msg);

	/*��������*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = buf;
	msg->len = shortToChar(obj->pf,len,buf);
	sent_packet(msg);

	/*���ؿ���*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = obj->sw;
	msg->len = len;
	sent_packet(msg);

	/*��C��*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = buf;
	msg->len = shortToChar(obj->carbon,len,buf);
	sent_packet(msg);

	/*��ѹƵ��*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = buf;
	msg->len = shortToChar(obj->rate,len,buf); // ����
	sent_packet(msg);
}

/**
 * ��  �ܣ������¶ȡ�ʪ�ȡ��Ž���ˮ�����������
 */
static void sent_envObject(_envDataObjct *obj, uchar *buf, dev_data_packet *msg)
{
	if(!obj) return;
	int fn=0, len = obj->len;

	/*ʪ��*/
	fn += 1;
	msg->fn[1] = fn << 4;
	sent_unit(&(obj->tem), len, buf, msg);

	/*ʪ��*/
	fn += 1;
	msg->fn[1] = fn << 4;
	sent_unit(&(obj->hum), len, buf, msg);

	/*�Ž�*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = obj->door;
	msg->len = 2;
	sent_packet(msg);

	/*ˮ��*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = obj->water;
	msg->len = 1;
	sent_packet(msg);

	/*����*/
	fn += 1;
	msg->fn[1] = fn << 4;
	msg->data = obj->smoke;
	msg->len = 1;
	sent_packet(msg);
}

/**
 * ��  �ܣ��豸���ݷ���
 */
static void sent_devData(uchar id, pduDevData *devData)
{
	static dev_data_packet msg;
	static uchar buf[DATA_MSG_SIZE] = {0};
	int fn=2;

	msg.addr = id;
	msg.fn[0] = fn++;
	sent_object(&(devData->line),buf, &msg);

	msg.fn[0] = fn++;
	sent_object(&(devData->output),buf,&msg);

	msg.fn[0] = fn++;
	sent_envObject(&(devData->env), buf,&msg);

	//sent_devStatus(&msg, 1);
}


/**
 * ��ʼ������  �����ã�
 */
static void init_unit(sDataUnit *data, _devDataUnit *unit, int rate)
{
	int i;
	for(i=0; i< data->size; ++i) {
		unit->value[i] = data->value[i]*rate;
		unit->max[i] = data->max[i]*rate;
		unit->min[i] = data->min[i]*rate;
		//unit->alrm = alarmbuf;
	}
}

/**
 * ���ݳ�ʼ��  ������
 */
static void init_obj(sObjData *obj, _devDataObj *ptr)
{
	int i;
	ptr->len = obj->size;
	for(i=0; i< ptr->len; ++i) {
		init_unit(&(obj->cur), &(ptr->cur), 1);
		init_unit(&(obj->vol), &(ptr->vol), COM_RATE_VOL);

		ptr->sw[i] = obj->sw[i];
		ptr->pow[i] = obj->pow[i];
		ptr->ele[i] = obj->ele[i];
		ptr->pf[i] = obj->pf[i];
	}
}


static void init_env(sEnvData *env, _envDataObjct *ptr)
{
	int i;
	ptr->len = env->size;
	for(i=0; i< ptr->len; ++i) {
		init_unit(&(env->tem), &(ptr->tem), COM_RATE_TEM);
		init_unit(&(env->hum), &(ptr->hum), COM_RATE_HUM);
	}
}


static int init_data(uchar id, pduDevData *ptr)
{
	sDataPacket *packet = data_packet_get(id);
	if(packet->offLine) {
		sDevData *devData = &(packet->data);
		init_obj(&(devData->line), &(ptr->line));
		init_env(&(devData->env), &(ptr->env));
	}

	return packet->offLine;
}

static void sent_devName(int id)
{
	char *name = "SI-PDU";
	dev_data_packet msg;
	msg.addr = id;
	msg.len = strlen(name);
	msg.data = (uchar *)name;

	msg.fn[0] = 5;
	msg.fn[1] = 0x11;
	data_packet_sent(&msg);
}

void sent_str(int id, int fn1, int fn2, short len, char *str)
{
	dev_data_packet msg;
	msg.addr = id;
	msg.len = len;
	msg.data = (uchar *)str;

	msg.fn[0] = fn1;
	msg.fn[1] = fn2;
	data_packet_sent(&msg);
}

/**
 * ���Ͳ������ݣ� ������
 */
void dev_data_sent(pduDevData *ptr)
{
	int i=1;
	for(i=1; i<=DEV_NUM; ++i) {
		memset(ptr, 0, sizeof(pduDevData));
		int ret = init_data(i, ptr);
		if(ret>0) {
			sent_devData(i,ptr);
			sent_devName(i);
			udp_delay(1);
		}
	}
}

static void dev_thread_entry(void *p)
{
    udp_delay(1);
	pduDevData *devData = (pduDevData*)malloc(sizeof(pduDevData));
	while(1) {
	    udp_delay(3);
		if(udp_sentCheck()) { 	/*����˼��*/
			dev_data_sent(devData);
		}
	}
}


/**
 * �����������������߳�
 */
void dev_sent_thread(void)
{
	rt_thread_t tid = rt_thread_create("m_sent",dev_thread_entry, NULL, 3*512, 27, 25);
	if (tid != RT_NULL) rt_thread_startup(tid);
}


