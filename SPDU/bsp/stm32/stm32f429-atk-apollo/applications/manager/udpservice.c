/*
 * udpservice.c
 * UDP 服务端  实现UDP接收功能
 *  1、提供创建套接字接口
 *  2、提供数据接收接口
 *
 *  Created on: 2016年7月29日
 *      Author: Lzy
 */
#include "udpservice.h"
#define UDP_PORT	18750 // 端口号
extern void net_recv_dataPacket(dev_data_packet *pkt);

/**
 * 功能：创建UDP服务端套接字
 * 返回 ：套接字
 */
int udp_serviceSocket(int port)
{
	int sockfd;
	struct sockaddr_in server_addr;/* 主机IP地址和端口号 */

	/* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		udp_printf("Socket error\n");
		return -1;
	}

	/* 初始化服务端地址 */
	server_addr.sin_family = AF_INET;		/*IPv4因特网域*/
	server_addr.sin_port = htons(port);    /*端口号，这里进行网络字节序的转换 */
	server_addr.sin_addr.s_addr = INADDR_ANY;
	//server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	/* 绑定socket到服务端地址 */
	if (bind(sockfd, (struct sockaddr *)&server_addr,
			sizeof(struct sockaddr)) == -1)
	{
		/* 绑定地址失败 */
		udp_printf("Bind error\n");
		return -1;
	}
	//udp_printf("UDP Server Waiting for client on port %d...\n", port);

	return sockfd;
}



/**
 * 功  能：UDP 数据接收
 * 出口参数：*recv_data -> 接收数据缓冲区
 * 返  回: 数据长度
 */
int udp_serviceRecvData(int sockfd,struct sockaddr_in *client_addr,uchar *recv_data)
{
	int ret=0;
	uint addr_len = sizeof(struct sockaddr);

	/*超时设置*/
	//	struct timeval timeout={3,0};//3S
	//	ret=setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
	//	if(ret<0)
	//		udp_printf("UDP setsockopt Err\n");

	/* 从sock中收取最大BUF_SIZE - 1字节数据 */
	/* UDP不同于TCP，它基本不会出现收取的数据失败的情况，除非设置了超时等待 */
	ret = recvfrom(sockfd, recv_data, UDP_BUF_SIZE - 1, 0,
			(struct sockaddr *)client_addr, &addr_len);
	//	udp_printf("UDP Recv Data len:%d %s\n",ret, recv_data);

	return ret;
}


static void udp_recv_data(uchar *buf, int len)
{
	dev_data_packet pkt;
	int rtn = data_packet_analytic(buf, len, &pkt);
	if(rtn > 0) {
		if(pkt.addr == 0xff) {
			int addr;
			for(addr=1; addr<=DEV_NUM; ++addr) { // 设备所有副机
				pkt.addr = addr;
				net_recv_dataPacket(&pkt);
			}
		} else {
			net_recv_dataPacket(&pkt);
		}
	} else
		udp_printf("recv err %d\n", rtn);
}


static void udps_thread_entry(void *p)
{
	int rtn=0;
	udp_delay(4);
	uchar buf[UDP_BUF_SIZE/2] = {0};
	struct sockaddr_in clientAddr;
	int sock_fd = udp_serviceSocket(UDP_PORT);

	while(1) {
		memset(buf, 0, sizeof(buf));
		rtn = udp_serviceRecvData(sock_fd, &clientAddr, buf);
		if(rtn > 0) {
			udp_recv_data(buf, rtn);
		}
	}
}



/**
 * 创建并启动心跳包线程
 */
void udp_recv_thread(void)
{
	rt_thread_t tid = rt_thread_create("m_recv",udps_thread_entry, NULL, 2*512, 27, 15);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
