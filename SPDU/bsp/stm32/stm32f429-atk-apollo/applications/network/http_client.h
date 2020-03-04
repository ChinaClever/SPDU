/*
 * http_client.h
 *
 *  Created on: 2019Äê6ÔÂ12ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_HTTP_CLIENT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_HTTP_CLIENT_H_
#include "udp_server.h"

int http_get(char *uri);
int http_post(char *uri, char *post_data, char *head);


#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_HTTP_CLIENT_H_ */
