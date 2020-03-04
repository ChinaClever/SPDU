/*
 * udpserver.h
 *
 *  Created on: 2019Äê6ÔÂ12ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_SERVER_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_SERVER_H_
#include "udp_client.h"

int udp_serv_init(int port);
void udp_serv_thread(void);


#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_UDP_SERVER_H_ */
