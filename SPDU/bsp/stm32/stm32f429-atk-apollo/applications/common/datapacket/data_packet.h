/*
 * data_packet.h
 *
 *  Created on: 2019年6月6日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_PACKET_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_PACKET_H_
#include "data_opt.h"

#define LINE_NUM  3
#define LOOP_NUM  6
#define OUTPUT_NUM 42
#define SENOR_NUM 1
#define NAME_SIZE RT_NAME_MAX
#define DEV_NUM 42
#define ARRAY_SIZE 255 //一包数据最长
#define PACK_ARRAY_SIZE LINE_NUM


// 倍率定义
#define COM_RATE_VOL	10.0    // 电压
#define COM_RATE_CUR	10.0    // 电流
#define COM_RATE_POW	1000.0  // 功率
#define COM_RATE_ELE	10.0    // 电能
#define COM_RATE_PF     100.0   // 功率因素
#define COM_RATE_TEM	10.0    // 温度
#define COM_RATE_HUM	10.0    // 湿度

#define PDU_TYPE_SI_PDU     0x01000101
#define PDU_TYPE_IP_PDU     0x01010101
#define PDU_TYPE_M_PDU      0x01020101
#define PDU_TYPE_NPM_PDU    0x01030101
#define PDU_TYPE_RPDU       0x01040101
#define PDU_TYPE_ZPDU       0x01050101

/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
typedef struct sDataUnit
{
    ushort size;
    ushort value[PACK_ARRAY_SIZE]; // 值
    ushort min[PACK_ARRAY_SIZE]; // 最小值
    ushort max[PACK_ARRAY_SIZE]; // 最大值
    ushort alarm[PACK_ARRAY_SIZE];
}sDataUnit;

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
typedef struct sObjData
{
	ushort size;
    sDataUnit vol; // 电压
    sDataUnit cur; // 电流

    uint pow[PACK_ARRAY_SIZE]; // 功率
    uint ele[PACK_ARRAY_SIZE]; // 电能

    ushort pf[PACK_ARRAY_SIZE]; // 功率因素
    uchar sw[PACK_ARRAY_SIZE]; // 开关状态  01 表示断路器闭合，00 表示打开

    uchar hz[PACK_ARRAY_SIZE]; // 电压频率
    ushort apPow[PACK_ARRAY_SIZE]; // 视在功率值
    uchar pl[PACK_ARRAY_SIZE]; // 负载百分比

#if 0
    char name[PACK_ARRAY_SIZE][NAME_SIZE];
    uint ratedCur[PACK_ARRAY_SIZE]; // 额定电流
    uint wave[PACK_ARRAY_SIZE]; // 谐波值
    uint tem[PACK_ARRAY_SIZE];
    uchar delay[PACK_ARRAY_SIZE];

    uint curThd[PACK_ARRAY_SIZE]; // 电流谐波含量
    uint volThd[PACK_ARRAY_SIZE]; // 电压谐波含量
#endif
}sObjData;


typedef struct sTgObjData
{
    uint vol; // 电压
    uint cur;  // 电流
    uint pow; // 功率

    uint ele; // 电能
    uint pf; // 功率因素
    uint activePow; // 袖在功率
    uint tem;
}sTgObjData;

/**
 * 环境数据结构体
 */
typedef struct sEnvData
{
    uchar size;

    sDataUnit tem; // 温度
    sDataUnit hum; // 湿度
#if 0
    char name[SENOR_NUM];
    uchar door[SENOR_NUM]; // 门禁
    uchar water[SENOR_NUM]; // 水浸
    uchar smoke[SENOR_NUM]; // 烟雾
#endif
}sEnvData;

/**
 * 设备数据结构体：
 */
typedef struct sDevData
{
    sObjData line; // 相数据
    sEnvData env; // 环境数据
#if 0
    sObjData loop; // 回路数据
    sObjData output; //位数据
    sTgObjData tg; // 回路数据
#endif
}sDevData;

/**
 * RTU传输统计结构体
 */
typedef struct sRtuCount
{
    uint count;
    uint okCount;
    uint errCount;

    uint longCount; // 连续丢命令
    uint longFlag;
}sRtuCount;

/**
 * 数据包
 */
typedef struct sDataPacket
{
    uchar id, en;  // 设备号
    uint devType; //设备类型
    uchar devSpec; // 设备规格 A\B\C\D
    uchar txType; // 通讯类型 1 UDP  3:SNMP  4：Zebra

    uchar alarm; // 工作状态 ==0 正常
    ushort offLine; //离线标志 > 0在线

    sDevData data; //设备数据
    sRtuCount rtuCount; // 传输情况

    uchar lps; // 防雷开关
    uchar dc; // 交直流标志位
    uchar hz; // 电压频率
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort version;
    ushort reserve;
    uint count;
#if 0
    QString name; // 设备名称
    QString user, pwd;
    QString dev_num, dev_type;
    QString room,modular,cab, road;
    QString versionStr;
    sIpAddr ip; //设备IP

    uint room_id;
    uint cab_id;
    uint pdu_id;
#endif
}sDataPacket;

typedef struct sPackets {
	sDataPacket packet[DEV_NUM+1];
}sPackets;

sDataPacket *data_packet_get(int id);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_PACKET_H_ */
