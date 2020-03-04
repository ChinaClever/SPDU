/*
 * devDataRecv.c
 *
 *  Created on: 2019年10月12日
 *      Author: luozhiyong
 */
#include "devDataSent.h"

static int charToShort(uchar *form, int len, int *to)
{
	int i, offset=0;
	for(i=0; i<len; i+=2)
		to[offset++] = form[i] *256 + form[i+1];
	return offset;
}

static void setUnit(sDataUnit *unit, dev_data_packet *pkt, double rate)
{
	int buf[24] = {0}, i;
	char setbuf[128];
	memset(setbuf,0,sizeof(setbuf));
	charToShort(pkt->data, pkt->len, buf);

	ushort id = pkt->addr;
	int fn = pkt->fn[1]; //输出位，
	if(fn) {
		unit->min[fn-1] = buf[0]/rate; // 最小值
		unit->max[fn-1] = buf[1]/rate; // 最大值
	} else {
		for( i=0; i<LINE_NUM; ++i) {
			unit->min[i] = buf[0]/rate; // 最小值
			unit->max[i] = buf[1]/rate; // 最大值
		}
	}
}


static void setLineVol(sDevData *dev, dev_data_packet *pkt)
{
//	int id = pkt->addr;
//	int fn = pkt->fn[1]; //输出位，
//	if(fn) {
//
//	}

	sDataUnit *unit = &(dev->line.vol);
	setUnit(unit, pkt, COM_RATE_VOL);
}



static void setLineCur(sDevData *dev,dev_data_packet *pkt)
{
//	int id = pkt->addr;
//	int fn = pkt->fn[1]; //输出位，
//	if(fn) {
//
//	}

	sDataUnit *unit = &(dev->line.cur);
	setUnit(unit, pkt, 1);
}


static void setEnvTem(sDevData *dev,dev_data_packet *pkt)
{
//	int id = pkt->addr;
//	int fn = pkt->fn[1]; //输出位，
//	if(fn) {
//
//	}

	sDataUnit *unit = &(dev->env.tem);
	setUnit(unit, pkt, COM_RATE_VOL);
}


static void setEnvHum(sDevData *dev, dev_data_packet *pkt)
{
	int id = pkt->addr;
	int fn = pkt->fn[1]; //输出位，
	if(fn) {

	}

	sDataUnit *unit = &(dev->env.hum);
	setUnit(unit, pkt, COM_RATE_VOL);
}



/**
 * 网络接收数据 进行解析
 */
void net_recv_dataPacket(dev_data_packet *pkt)
{
	int id = pkt->addr;
	sDataPacket *packet = data_packet_get(id);
    if(packet->offLine < 1) return;
	sDevData *dev = &(packet->data);
	switch(pkt->fn[0])
	{
	//	case 0:  setOutputCur(pkt);	break; // 设置输出位电流
	case 1:  setLineVol(dev, pkt); break;	// 设置相电压
	case 2:  setLineCur(dev, pkt); break; // 设置相电流
	case 3:  setEnvTem(dev, pkt); break; // 设置湿度
	case 4:  setEnvHum(dev, pkt); break; // 设置湿度
	//	case 5:  setDevName(pkt); break; // 设置输出位名称
	//	case 6:  setUserPwd(pkt); break; // 用户名和密码
	//	case 7:  setDevNet(pkt); break; // 设备网络信息
	//	case 10: setOutputName(pkt); break; // 设备输出位名称
	//	case 13: setSwicth(pkt); break; // 设置开关
	//	case 18: setAllSwicth(pkt); break; // 设置所有开关
	//	case 20: setSysCmd(pkt); break; // 系统命令
	}
}

