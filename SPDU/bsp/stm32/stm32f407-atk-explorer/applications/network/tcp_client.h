/*
 * tcpclient.h
 *
 *  Created on: 2019��6��12��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_TCP_CLIENT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_TCP_CLIENT_H_
#include "udp_server.h"

int tcp_client_init(char *url, int port);
int tcp_client_recv(int sock, char *recv_data, int len);
int tcp_client_sent(int sock, char *send_data, int len);

int tcp_push_init(char *url, int port);
int tcp_push_data(char *send_data);
int tcp_push_connected(void);
void tcp_serv_thread(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_TCP_CLIENT_H_ */