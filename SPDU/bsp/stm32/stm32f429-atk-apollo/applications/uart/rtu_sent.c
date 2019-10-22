/*
 * rtu_sent.c
 *
 *  Created on: 2019��10��22��
 *      Author: luozhiyong
 */
#include "rtu_sent.h"

static ushort calccrc (ushort crc, uchar crcbuf)
{
    uchar x, kkk=0;
    crc = crc^crcbuf;
    for(x=0;x<8;x++)
    {
        kkk = crc&1;
        crc >>= 1;
        crc &= 0x7FFF;
        if(kkk == 1)
            crc = crc^0xa001;
        crc=crc&0xffff;
    }
    return crc;
}

/**
  * �����ܣ�CRCУ��
  * ��ڲ�����buf -> ������  len -> ����
  * ����ֵ��CRC
  */
ushort rtu_crc(uchar *buf, ushort len)
{
    ushort i, crc = 0xffff;
    for(i=0; i<len; i++)
        crc = calccrc(crc, buf[i]);
    return crc;
}

/**
  * �����ܣ�XOR��У��
  * ��ڲ�����buf -> ������  len -> ����
  * ����ֵ��XOR
  */
uchar rtu_xorsum(uchar *buf, int len)
{
    uchar xorsum = 0x00;
    for(int i=0; i<len; i++)
        xorsum ^= buf[i];
    return xorsum;
}


/**
  * �����ܣ��������ݴ��
  * ��ڲ�����pkt -> ���ͽṹ��
  * ���ڲ�����ptr -> ������
  * ����ֵ�������ĳ���
  */
int rtu_sent_packet(sRtuSent *pkt, uchar *ptr)
{
    uchar *buf = ptr;
    *(ptr++) = pkt->addr;  /*��ַ��*/
    *(ptr++) = pkt->fn; /*������*/

    /*����Ĵ����׵�ַ*/
    *(ptr++) = ((pkt->reg) >> 8); /*��8λ*/
    *(ptr++) = (0xff)&(pkt->reg); /*��8λ*/

    /*�������ݳ���*/
    *(ptr++) = ((pkt->len) >> 8); /*���ȸ�8λ*/
    *(ptr++) = (0xff)&(pkt->len); /*��8λ*/

     /*����CRC*/
    pkt->crc = rtu_crc(buf, 6);
    *(ptr++) = (0xff)&(pkt->crc); /*��8λ*/
    *(ptr++) = ((pkt->crc) >> 8); /*��8λ*/

    return 8;
}



/**
  * �����ܣ��������ݴ��
  * ��ڲ�����pkt -> ���ͽṹ��
  * ���ڲ�����ptr -> ������
  * ����ֵ�������ĳ���
  */
int rtu_sent(uchar addr, uchar *buf, uchar len)
{
    static sRtuSent msg;

    msg.addr = addr;
    msg.len = len;

    return rtu_sent_packet(&msg, buf);
}

int rtu_sentAc(uchar addr, uchar *buf)
{
	return rtu_sent(addr, buf, SI_RTU_AC_LEN);
}

int rtu_sentDc(uchar addr, uchar *buf)
{
	return rtu_sent(addr, buf, SI_RTU_DC_LEN);
}

/**
  * �����ܣ������������ݴ��
  * ��ڲ�����pkt -> ���ͽṹ��
  * ���ڲ�����ptr -> ������
  * ����ֵ�������ĳ���
  */
int rtu_sentCmd(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static sRtuSent msg;

    msg.addr = addr;
    msg.fn = 0x10;
    msg.reg = reg;
    msg.len = value;

    return rtu_sent_packet(&msg, buf);
}