/*
 * udpserver.c
 *
 *  Created on: 2019年6月12日
 *      Author: luozhiyong
 */
#include "udp_server.h"

#define UDP_SERV_BUFSZ   382
static char udp_ser_buf[UDP_SERV_BUFSZ];

int udp_serv_init(int port)
{
	int ret = false;
	struct sockaddr_in server_addr;

	/* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		rt_kprintf("udp server Socket error\n");
		return ret;
	}

	/* 初始化服务端地址 */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	/* 绑定socket到服务端地址 */
	ret = bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if (ret == -1) { /* 绑定地址失败 */
		rt_kprintf("udp server Bind error\n");
		closesocket(sock);
	} else {
		ret = sock;
		//rt_kprintf("UDP Server Waiting for client on port %d...\n", port);
	}

	return ret;
}

int udp_serv_recv(int sock, char *recv_data, int len)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(struct sockaddr);

	int bytes_read = false;
	if(sock >= 0) {
		bytes_read = recvfrom(sock, recv_data, len-1, 0, (struct sockaddr *)&client_addr, &addr_len);
		recv_data[bytes_read] = '\0'; /* 把末端清零 */ /* UDP不同于TCP，它基本不会出现收取的数据失败的情况，除非设置了超时等待 */
		// rt_kprintf("\n(%s , %d) said : ", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	}
	msleep(1);

	return bytes_read;
}


void udp_serv_task(void *arg)
{
	int port = 2707;
	int ret, sock = udp_serv_init(port);
	char *buf = udp_ser_buf;

	while(1) {
		ret = udp_serv_recv(sock, buf, UDP_SERV_BUFSZ);
		if(ret > 0) {
			json_analysis(buf);
		}
		msleep(5);
	}
}

void udp_serv_thread(void)
{
	rt_thread_t tid = rt_thread_create("net_serv",udp_serv_task, NULL,2*512,26, 15);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
