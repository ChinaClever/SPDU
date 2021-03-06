/*
 * udpclient.c
 *
 *  Created on: 2019年6月12日
 *      Author: luozhiyong
 */
#include "udp_client.h"

static int gUdpClientSock = -1;
static struct sockaddr_in gUdpClientserver_addr;

int udp_client_init(char *url, int port)
{
	struct sockaddr_in *server_addr = &gUdpClientserver_addr;

	/* 通过函数入口参数url获得host地址（如果是域名，会做域名解析） */
	struct hostent *host = (struct hostent *) gethostbyname(url);
	udp_client_close();

	/* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		rt_kprintf("Socket error\n");
		return false;
	}
	gUdpClientSock = sock;

	/* 初始化预连接的服务端地址 */
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(port);
	server_addr->sin_addr = *((struct in_addr *)host->h_addr);
	rt_memset(&(server_addr->sin_zero), 0, sizeof(server_addr->sin_zero));

	return sock;
}


int udp_client_sent(char *send_data)
{
	int ret = true;
	int sock = gUdpClientSock;
	struct sockaddr_in *server_addr = &gUdpClientserver_addr;

	if(sock >= 0) {
		/* 发送数据到服务远端 */
		ret = sendto(sock, send_data, strlen(send_data), 0, (struct sockaddr *)server_addr, sizeof(struct sockaddr));
		msleep(5); /* 线程休眠一段时间 */
	} else {
		ret = false;
	}

	return ret;
}

/* 关闭socket */
void udp_client_close(void)
{
	int sock = gUdpClientSock;
	if(sock >= 0) {
		closesocket(sock);
		gUdpClientSock = -1;
	}
}

int udp_client_connected(void)
{
	return gUdpClientSock;
}
