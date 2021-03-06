/*
 * udpclient.h
 *
 *  Created on: 2019年6月12日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_CLIENT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_CLIENT_H_

#include <sys/socket.h> /* 使用BSD socket，需要包含sockets.h头文件 */
#include <netdb.h>
#include <string.h>
#include "websocket.h"

int udp_client_init(char *url, int port);
int udp_client_sent(char *send_data);
int udp_client_connected(void);
void udp_client_close(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_CLIENT_H_ */
