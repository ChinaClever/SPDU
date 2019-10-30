/*
 * tcp_server.h
 *
 *  Created on: 2019年10月25日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_NETWORK_TCP_SERVER_H_
#define BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_NETWORK_TCP_SERVER_H_
#include <rtthread.h>
#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */
#include <netdb.h>
#include <string.h>
#include <finsh.h>
#include "udp_server.h"

int tcp_server_listen(int port);
int tcp_server_accept(int sock);

int tcp_server_connected(void);
int tcp_server_push(char *send_data);
void tcp_server_thread(void);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_NETWORK_TCP_SERVER_H_ */
