/*
 * rtu_sent.c
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */
#include "rtu_sentcmd.h"

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
  * 功　能：CRC校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：CRC
  */
ushort rtu_crc(uchar *buf, ushort len)
{
    ushort i, crc = 0xffff;
    for(i=0; i<len; i++)
        crc = calccrc(crc, buf[i]);
    return crc;
}

/**
  * 功　能：XOR和校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：XOR
  */
uchar rtu_xorsum(uchar *buf, int len)
{
    uchar xorsum = 0x00;
    for(int i=0; i<len; i++)
        xorsum ^= buf[i];
    return xorsum;
}


/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
static int rtu_sent_packet(sRtuSent *pkt, uchar *ptr)
{
    uchar *buf = ptr;
    *(ptr++) = pkt->addr;  /*地址码*/
    *(ptr++) = pkt->fn; /*功能码*/

    /*填入寄存器首地址*/
    *(ptr++) = ((pkt->reg) >> 8); /*高8位*/
    *(ptr++) = (0xff)&(pkt->reg); /*低8位*/

    /*填入数据长度*/
    *(ptr++) = ((pkt->len) >> 8); /*长度高8位*/
    *(ptr++) = (0xff)&(pkt->len); /*低8位*/

     /*填入CRC*/
    pkt->crc = rtu_crc(buf, 6);
    *(ptr++) = (0xff)&(pkt->crc); /*低8位*/
    *(ptr++) = ((pkt->crc) >> 8); /*高8位*/

    return 8;
}



/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
static int rtu_sendCmd(uchar addr, uchar *buf, uchar len)
{
    static sRtuSent msg;

    msg.addr = addr;
    msg.fn = 0x03;
    msg.len = len;

    return rtu_sent_packet(&msg, buf);
}

int rtu_cmdAc(uchar addr, uchar *buf)
{
	return rtu_sendCmd(addr, buf, SI_RTU_AC_LEN);
}

int rtu_cmdDc(uchar addr, uchar *buf)
{
	return rtu_sendCmd(addr, buf, SI_RTU_DC_LEN);
}

/**
  * 功　能：发送命令数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
static int rtu_cmd(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static sRtuSent msg;

    msg.addr = addr;
    msg.fn = 0x10;
    msg.reg = reg;
    msg.len = value;

    return rtu_sent_packet(&msg, buf);
}

int rtu_sentCmd(sRtuSetCmd *cmd, uchar *buf)
{
	return rtu_cmd(cmd->addr, cmd->reg, cmd->value, buf);
}
