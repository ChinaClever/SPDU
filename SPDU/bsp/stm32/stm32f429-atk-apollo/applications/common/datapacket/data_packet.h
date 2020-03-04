/*
 * data_packet.h
 *
 *  Created on: 2019��6��6��
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
#define ARRAY_SIZE 255 //һ�������
#define PACK_ARRAY_SIZE LINE_NUM


// ���ʶ���
#define COM_RATE_VOL	10.0    // ��ѹ
#define COM_RATE_CUR	10.0    // ����
#define COM_RATE_POW	1000.0  // ����
#define COM_RATE_ELE	10.0    // ����
#define COM_RATE_PF     100.0   // ��������
#define COM_RATE_TEM	10.0    // �¶�
#define COM_RATE_HUM	10.0    // ʪ��

#define PDU_TYPE_SI_PDU     0x01000101
#define PDU_TYPE_IP_PDU     0x01010101
#define PDU_TYPE_M_PDU      0x01020101
#define PDU_TYPE_NPM_PDU    0x01030101
#define PDU_TYPE_RPDU       0x01040101
#define PDU_TYPE_ZPDU       0x01050101

/**
 * ���ݵ�Ԫ��������ǰֵ����ֵ���ٽ�ֵ���澯״̬��
 */
typedef struct sDataUnit
{
    ushort size;
    ushort value[PACK_ARRAY_SIZE]; // ֵ
    ushort min[PACK_ARRAY_SIZE]; // ��Сֵ
    ushort max[PACK_ARRAY_SIZE]; // ���ֵ
    ushort alarm[PACK_ARRAY_SIZE];
}sDataUnit;

/**
 * ���ݶ��󣺰�����������ѹ�����ʣ����ܣ�����״̬�����λ����
 */
typedef struct sObjData
{
	ushort size;
    sDataUnit vol; // ��ѹ
    sDataUnit cur; // ����

    uint pow[PACK_ARRAY_SIZE]; // ����
    uint ele[PACK_ARRAY_SIZE]; // ����

    ushort pf[PACK_ARRAY_SIZE]; // ��������
    uchar sw[PACK_ARRAY_SIZE]; // ����״̬  01 ��ʾ��·���պϣ�00 ��ʾ��

    uchar hz[PACK_ARRAY_SIZE]; // ��ѹƵ��
    ushort apPow[PACK_ARRAY_SIZE]; // ���ڹ���ֵ
    uchar pl[PACK_ARRAY_SIZE]; // ���ذٷֱ�

#if 0
    char name[PACK_ARRAY_SIZE][NAME_SIZE];
    uint ratedCur[PACK_ARRAY_SIZE]; // �����
    uint wave[PACK_ARRAY_SIZE]; // г��ֵ
    uint tem[PACK_ARRAY_SIZE];
    uchar delay[PACK_ARRAY_SIZE];

    uint curThd[PACK_ARRAY_SIZE]; // ����г������
    uint volThd[PACK_ARRAY_SIZE]; // ��ѹг������
#endif
}sObjData;


typedef struct sTgObjData
{
    uint vol; // ��ѹ
    uint cur;  // ����
    uint pow; // ����

    uint ele; // ����
    uint pf; // ��������
    uint activePow; // ���ڹ���
    uint tem;
}sTgObjData;

/**
 * �������ݽṹ��
 */
typedef struct sEnvData
{
    uchar size;

    sDataUnit tem; // �¶�
    sDataUnit hum; // ʪ��
#if 0
    char name[SENOR_NUM];
    uchar door[SENOR_NUM]; // �Ž�
    uchar water[SENOR_NUM]; // ˮ��
    uchar smoke[SENOR_NUM]; // ����
#endif
}sEnvData;

/**
 * �豸���ݽṹ�壺
 */
typedef struct sDevData
{
    sObjData line; // ������
    sEnvData env; // ��������
#if 0
    sObjData loop; // ��·����
    sObjData output; //λ����
    sTgObjData tg; // ��·����
#endif
}sDevData;

/**
 * RTU����ͳ�ƽṹ��
 */
typedef struct sRtuCount
{
    uint count;
    uint okCount;
    uint errCount;

    uint longCount; // ����������
    uint longFlag;
}sRtuCount;

/**
 * ���ݰ�
 */
typedef struct sDataPacket
{
    uchar id, en;  // �豸��
    uint devType; //�豸����
    uchar devSpec; // �豸��� A\B\C\D
    uchar txType; // ͨѶ���� 1 UDP  3:SNMP  4��Zebra

    uchar alarm; // ����״̬ ==0 ����
    ushort offLine; //���߱�־ > 0����

    sDevData data; //�豸����
    sRtuCount rtuCount; // �������

    uchar lps; // ���׿���
    uchar dc; // ��ֱ����־λ
    uchar hz; // ��ѹƵ��
    ushort br;  // 00	��ʾ������9600(00Ĭ��9600��01Ϊ4800��02Ϊ9600��03Ϊ19200��04Ϊ38400)

    ushort version;
    ushort reserve;
    uint count;
#if 0
    QString name; // �豸����
    QString user, pwd;
    QString dev_num, dev_type;
    QString room,modular,cab, road;
    QString versionStr;
    sIpAddr ip; //�豸IP

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
