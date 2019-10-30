/*
 * tcp_server.c
 *
 *  Created on: 2019年10月25日
 *      Author: luozhiyong
 */
#include "tcp_server.h"

int tcp_server_listen(int port)
{
	struct sockaddr_in server_addr;

	/* 一个socket在使用前，需要预先创建出来，指定SOCK_STREAM为TCP的socket */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		/* 创建失败的错误处理 */
		rt_kprintf("tcp server Socket error\n");
		return -1;
	}

	/* 初始化服务端地址 */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port); /* 服务端工作的端口 */
	server_addr.sin_addr.s_addr = INADDR_ANY;
	rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	/* 绑定socket到服务端地址 */
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		/* 绑定失败 */
		rt_kprintf("tcp server Unable to bind\n");
		return -1;
	}

	/* 在socket上进行监听 */
	if (listen(sock, 5) == -1)
	{
		rt_kprintf("tcp server Listen error\n");
		return -1;
	}

	return sock;
}

int tcp_server_accept(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t sin_size = sizeof(struct sockaddr_in);

	/* 接受一个客户端连接socket的请求，这个函数调用是阻塞式的 */
	int connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
	if (connected >= 0) /* 返回的是连接成功的socket */
	{
		/* 接受返回的client_addr指向了客户端的地址信息 */
		rt_kprintf("I got a connection from (%s , %d)\n",
				inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	} else {
		rt_kprintf("accept connection failed! errno = %d\n", errno);
	}

	return connected;
}


/* 从sock连接中接收最大BUFSZ - 1字节数据 */
int tcp_server_recv(int sock, char *recv_data, int len)
{
	int ret = recv(sock, recv_data, len - 1, 0);
	if (ret > 0) {
		recv_data[ret] = '\0'; /* 有接收到数据，把末端清零 */
	} else {
		ret = false;
		closesocket(sock);
		rt_kprintf("\ntcp server received error,close the socket.\r\n");
	}

	return ret;
}

/* 发送数据到sock连接 */
int tcp_server_sent(int sock, char *send_data, int len)
{
	int ret = send(sock, send_data, len, 0);
	if (ret <= 0) {
		ret = false;
		closesocket(sock);
		rt_kprintf("\ntcp server send error,close the socket.\r\n");
	}

	return ret;
}

int tcp_server_connected(void)
{
	return 1;
}

static int gTcpSerSocket=-1;
int tcp_server_push(char *send_data)
{
	int ret = true;
	int socket = gTcpSerSocket;

	if(socket > 0) {
		int len = strlen(send_data);
		ret = tcp_server_sent(socket, send_data, len);
	} else {
		ret = false;
	}

	return ret;
}

static void tcp_server_rask(void *arg)
{
	int ret;
	char buf[256] = {0};
	int sock = tcp_server_listen(2708);

	while(1) {
		gTcpSerSocket = tcp_server_accept(sock);
		if(gTcpSerSocket > 0) {
			while(1) {
				ret = tcp_server_recv(gTcpSerSocket, buf, sizeof(buf));
				if(ret > 0) {
					ret = json_analysis(buf);
					if(ret) {
						tcp_server_push("OK");
					} else {
						tcp_server_push("err");
					}
				} else {
					gTcpSerSocket = -1;
					break;
				}
			}
		}
		msleep(5);
	}
}

void tcp_serv_thread(void)
{
	rt_thread_t tid = rt_thread_create("tcp_ser",tcp_server_rask, NULL,3*512,19, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
