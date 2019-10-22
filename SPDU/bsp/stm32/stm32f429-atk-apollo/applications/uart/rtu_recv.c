/*
 * rtu_recv.c
 *
 *  Created on: 2019年10月22日
 *      Author: luozhiyong
 */
#include "rtu_recv.h"

/**
 * 功　能：长度 校验
 * 入口参数：buf -> 缓冲区  len -> 长度
 * 返回值：0 正确
 */
static int rtu_recv_len(uchar *buf, int len)
{
	int ret = 0;

	if(len < SI_RTU_DC_LEN) {
		ret = -1;
		rt_kprintf("rtu recv Err: len too short!! len=%d\n", len);
	} else if(len > SI_RTU_AC_LEN + 7) {
		ret = -2;
		rt_kprintf("rtu recv Err: len too long!! len=%d\n", len);
	} else {
		len = buf[2]*256 + buf[3];
		if(len == SI_RTU_AC_LEN) {
			ret = 3;
		} else if (len == SI_RTU_DC_LEN) {
			ret = 1;
		} else  {
			ret = -3;
			rt_kprintf("rtu recv len Err!! len=%d\n", len);
			len = 0;
		}
	}

	return ret;
}



/**
 * 功　能：读取数据包头部
 * 入口参数：ptr -> 缓冲区
 * 出口参数：pkt -> 结构体
 * 返回值：0 正确
 */
static int rtu_recv_head(uchar *ptr,  sRtuRecv *pkt)
{
	pkt->addr = *(ptr++);// 从机地址码
	pkt->fn = *(ptr++);  /*功能码*/
	pkt->len = (*ptr) * 256 + *(ptr+1); /*数据长度*/
	if(pkt->len > UART_RECV_SIZE) pkt->len = 0;

	return 4;
}


static uchar *rtu_recv_intData(uchar *ptr, int line, uint *value)
{
	int i;
	for(i=0; i<line; ++i) {
		value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
		value[i] <<= 8; // 左移8位
		value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
	}

	return ptr;
}

static uchar *rtu_recv_shortData(uchar *ptr, int line, ushort *value)
{
	int i;
	for(i=0; i<line; ++i) {
		value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
	}

	return ptr;
}


static uchar *rtu_recv_unit(uchar *ptr, int line, sDataUnit *unit)
{
	int i;
	for(i=0; i<line; ++i) {
		ptr = rtu_recv_shortData(ptr, 1, &(unit->min[i]));
		ptr = rtu_recv_shortData(ptr, 1, &(unit->max[i]));
	}

	return ptr;
}


static uchar *rtu_recv_charData(uchar *ptr, int line, uchar *value)
{
	int i;
	for(i=0; i<line; ++i) {
		value[i] =  *(ptr++);; // 读取电压
	}

	return ptr;
}

static void rtu_recv_alarm(sDataUnit *unit, int line)
{
	int i;
	for(i=0; i<line; ++i)
	{
		if((unit->value[i] > unit->max[i]) || (unit->value[i] < unit->min[i])) {
			if(unit->alarm[i] == 0)
				unit->alarm[i] = 1;
		} else {
			unit->alarm[i] = 0;
		}
	}
}

static uchar *rtu_recv_powData(uchar *ptr, int line, uint *value)
{
	int i;
	for(i=0; i<line; ++i) {
		value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
	}

	return ptr;
}

// 表示单相输入(00 表示直流，01 表示单相，02,表示两路，03 表示三相)（第 65 字节）
static void rtu_recv_lineNum(sDataPacket *packet)
{
	uchar lineNum = 1;
	if(packet->devSpec > 1) {
		lineNum = 3;
	}

	if(packet->devSpec) {
		packet->dc = 1;
	} else {
		packet->dc = 0;
	}

	sObjData *lineObj  = &(packet->data.line);
	lineObj->size = lineNum;
	lineObj->vol.size = lineNum;
	lineObj->cur.size = lineNum;

	sEnvData *env  = &(packet->data.env);
	if(env->tem.value[0] && env->hum.value[0]) {
		env->size = 1;
		env->tem.size = 1;
		env->hum.size = 1;
	}
}


/**
 * 功　能：读取电参数 数据
 * 入口参数：ptr -> 缓冲区
 * 出口参数：pkt -> 结构体
 * 返回值：12 正确
 */
static void rtu_recv_data(uchar *ptr, int line, sDataPacket *packet)
{
	sObjData *lineObj  = &(packet->data.line); // 相数据
	ptr =  rtu_recv_shortData(ptr, line, lineObj->vol.value);
	ptr =  rtu_recv_shortData(ptr, line, lineObj->cur.value);
	ptr =  rtu_recv_shortData(ptr, line, lineObj->apPow);
	ptr =  rtu_recv_intData(ptr, line, lineObj->ele);

	sDataUnit *unit = &(lineObj->vol);
	ptr =  rtu_recv_unit(ptr, line, unit);
	rtu_recv_alarm(unit, line);

	unit = &(lineObj->cur);
	ptr =  rtu_recv_unit(ptr, line, &(lineObj->cur));
	rtu_recv_alarm(unit, line);

	sEnvData *env  = &(packet->data.env);
	env->tem.value[0] =  *(ptr++);// 温度
	env->hum.value[0] =  *(ptr++);// 湿度
	if(line > 1) {
		env->tem.max[0] =  *(ptr++);
		env->tem.min[0] =  *(ptr++);
		rtu_recv_alarm(&(env->tem), line);

		env->hum.max[0] =  *(ptr++);
		env->hum.min[0] =  *(ptr++);
		rtu_recv_alarm(&(env->hum), line);

		// 表示单相输入(00 表示直流，01 表示单相，02,表示两路，03 表示三相)（第 65 字节）
		packet->devSpec =  *(ptr++);
	}
	packet->br =  *(ptr++); // 波特率

	ptr =  rtu_recv_powData(ptr, line, lineObj->pow);
	ptr =  rtu_recv_shortData(ptr, line, lineObj->pf); // 功率因素
	ptr =  rtu_recv_charData(ptr, line, lineObj->sw); // 开关状态

	if(line > 1) {
		packet->hz =  *(ptr++); // 频率
	} else {
		packet->devSpec =  *(ptr++);
		lineObj->pl = *(ptr++); // 负载百分比
	}
	rtu_recv_lineNum(packet);
}


/**
 * 功　能：检验码 数据
 * 入口参数：buf -> 缓冲区
 * 出口参数：pkt -> 结构体
 * 返回值：true
 */
static bool rtu_recv_crc(uchar *buf, int len, sRtuRecv *msg)
{
	bool ret = true;
	int rtn = len-2; uchar *ptr = buf+rtn;

	msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
	ushort crc = rtu_crc(buf, rtn);
	if(crc != msg->crc) {
		ret = false;
		rt_kprintf("rtu recv crc Err!\n");
	}

	return ret;
}


/**
 * 功　能：还原数据包 交直流通用
 * 入口参数：buf -> 缓冲区   len -> 数据长度
 * 出口参数：pkt -> 结构体
 * 返回值：true
 */
static bool rtu_recv_packet(uchar *buf, int len, sRtuRecv *pkt)
{
	bool ret = false;

	int res = rtu_recv_len(buf, len);
	if(res > 0) {
		uchar *ptr=buf;
		ptr += rtu_recv_head(ptr, pkt);
		pkt->data = data_packet_get(pkt->addr);
		ptr += rtu_recv_data(ptr, res, pkt);
		ret = rtu_recv_crc(buf, len, pkt);
	}
	return ret;
}

bool rtu_recvPacket(uchar *buf, int len)
{
	static sRtuRecv pkt;

    bool ret = false;
    if((len > 2) && (len < UART_RECV_SIZE))
        ret = rtu_recv_packet(buf, len, &pkt);
    else
    	rt_kprintf( "SI_RtuRecv recvPacket err\n");

    return ret;
}
