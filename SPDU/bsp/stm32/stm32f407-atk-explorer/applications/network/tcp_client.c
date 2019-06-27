/*
 * tcpclient.c
 *
 *  Created on: 2019年6月12日
 *      Author: luozhiyong
 */
#include "tcp_client.h"

int tcp_client_init(char *url, int port)
{
	int ret = false;
	struct sockaddr_in server_addr;

	struct hostent *host = gethostbyname(url); /* 通过函数入口参数url获得host地址（如果是域名，会做域名解析） */
	int sock = socket(AF_INET, SOCK_STREAM, 0); /* 创建一个socket，类型是SOCKET_STREAM，TCP类型 */
	if (sock == -1) { /* 创建socket失败 */
		rt_kprintf("tcp client Socket error\n");
		return false;
	}

	/* 初始化预连接的服务端地址 */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	/* 连接到服务端 */
	ret = connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if (ret == -1) { /* 连接失败 */
		rt_kprintf("tcp client  Connect fail!\n");
		closesocket(sock);
	} else { /* 连接成功 */
		ret = sock;
		rt_kprintf("tcp Connect successful %s:%d\n", url, port);
	}

	return ret;
}

/* 从sock连接中接收最大BUFSZ - 1字节数据 */
int tcp_client_recv(int sock, char *recv_data, int len)
{
	int ret = recv(sock, recv_data, len - 1, 0);
	if (ret > 0) {
		recv_data[ret] = '\0'; /* 有接收到数据，把末端清零 */
	} else {
		ret = false;
		closesocket(sock);
		rt_kprintf("\ntcp client received error,close the socket.\r\n");
	}

	return ret;
}

/* 发送数据到sock连接 */
int tcp_client_sent(int sock, char *send_data, int len)
{
	int ret = send(sock, send_data, len, 0);
	if (ret <= 0)
	{
		ret = false;
		closesocket(sock);
		rt_kprintf("\ntcp client send error,close the socket.\r\n");
	}

	return ret;
}


static int gTcpSocket=-1;
int tcp_push_init(char *url, int port)
{
	int socket = gTcpSocket;
	if(socket > 0) {
		closesocket(socket);
	}
	socket = tcp_client_init(url, port);
	gTcpSocket = socket;
	return socket;
}

int tcp_push_connected(void)
{
	return gTcpSocket;
}

int tcp_push_data(char *send_data)
{
	int ret = true;
	int socket = gTcpSocket;
	if(socket > 0) {
		int len = strlen(send_data);
		ret = tcp_client_sent(socket, send_data, len);
	} else {
		ret = false;
	}

	return ret;
}

int tcp_recv_rask(void *arg)
{
	int ret, sock;
	char buf[256] = {0};

	while(1) {
		sock = gTcpSocket;
		if(sock > 0) {
			ret = tcp_client_recv(sock, buf, sizeof(buf));
			if(ret > 0) {
				json_analysis(buf);
			} else {
				gTcpSocket = -1;
			}
		}
		msleep(5);
	}
}

void tcp_serv_thread(void)
{
	rt_thread_t tid = rt_thread_create("tcpserv",tcp_recv_rask, NULL,1*512,23, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
