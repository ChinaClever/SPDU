/*
 * udpHbPacket.c
 * UDP������
 * 	1�������߳̽���������
 * 	2����ȡ����ȷ��������ʱ���Զ���ȡ����˵�ַ�������ñ�־λ
 *
 *  Created on: 2016��7��29��
 *      Author: Lzy
 */
#include "udpHbPacket.h"

#define UDP_HBPORT_NUM    18725 // �����˿�
#define UDP_HEARTBEAT_MSG   "Clever-Manager PDU PC Server OK!"
#define UDP_SERVER_OK	20 /*���������*/
#define UDP_SERVER_ERR	0 /*����˴���*/

uchar gUdpCount = UDP_SERVER_OK; /* 20 ��ʾ����������״̬  0Ϊ�Ͽ�*/
static char server_ip[20] = {"192.168.1.215"}; /*������IP��ַ*/

/**
 * ���ܣ���ʼ��UDP
 * ���� ���׽���
 */
static int udp_initSocket(void)
{
	int ret =  udp_serviceSocket(UDP_HBPORT_NUM); // �����׽� ��
	if(ret< 0) {
		udp_printf("UDP init heart beat Packet Socket Err!\n");
	}

	return ret;
}



/**
 * ��  �ܣ�������������ж�
 * ��ڲ�����*send_data -> ���ݻ�����
 * ����: true  ��ʾ��������
 */
static int udp_heartbeatPacket(uchar *recv_data)
{
	int ret = strncmp((char *)recv_data,UDP_HEARTBEAT_MSG,strlen(UDP_HEARTBEAT_MSG));
	if(ret == 0) {
		gUdpCount = UDP_SERVER_OK;
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}


/**
 * ���ܣ��������� IP��ַ�����Ϣ
 */
static int udp_serverIP(struct sockaddr_in *client_addr)
{
	memset(server_ip, 0, sizeof(server_ip));
	sprintf(server_ip,"%s", inet_ntoa(client_addr->sin_addr)); /*��ȡ�����IP*/
	//rt_kprintf("Server:(%s , %d)\n", server_ip,ntohs(client_addr->sin_port));

	return 0;
}


/**
 * ��  �ܣ�UDP ���ݽ���
 * ���ڲ�����*recv_data -> �������ݻ�����
 * ��  ��: ���ݳ���
 */
static void udp_hbRecvData(int sockfd, uchar *recv_data)
{
	struct sockaddr_in client_addr;/* �ͻ���IP��ַ�Ͷ˿ں� */
	int ret = udp_serviceRecvData(sockfd, &client_addr, recv_data);
	if(ret > 0)
	{
		ret = udp_heartbeatPacket(recv_data); /*���������*/
		if(ret == true) {
			udp_serverIP(&client_addr);
			// udp_printf("UDP heart beat Packet OK\n");
		}
	}
}

/**
 * ��  �ܣ���ȡ�����IP
 * ��  ��:
 */
char* udp_getServerIP(void)
{
	return server_ip;
}

/**
 * �߳���ں���
 */
static void udp_thread_entry(void *p)
{
	udp_delay(2);
	uchar recv_data[UDP_BUF_SIZE/4]={0};
	int sock_fd  = udp_initSocket();
	while(1) {
	    udp_udelay(1);
		udp_hbRecvData(sock_fd, recv_data);
	}
}


/**
 * �̼߳�ʱ��ں���
 */
static void udp_thread_count(void *p)
{
	while(1) {
		udp_delay(1);
		if(gUdpCount>0) gUdpCount--; /*����һ�μ���һ�� */
	}
}

/**
 * ������������ʱ�߳�
 */
static void udp_count_thread(void)
{
	rt_thread_t tid = rt_thread_create("m_count",udp_thread_count, NULL, 256, 27, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}


/**
 * �����������������߳�
 */
void udp_hb_thread(void)
{
	rt_thread_t tid = rt_thread_create("m_hb",udp_thread_entry, NULL, 1024, 27, 10);
	if (tid != RT_NULL) {
		rt_thread_startup(tid);
		udp_count_thread();
	}
}



