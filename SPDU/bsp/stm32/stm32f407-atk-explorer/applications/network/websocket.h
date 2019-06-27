/*
 * websocket.h
 *
 *  Created on: 2019Äê6ÔÂ12ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_
#include "json_iot.h"

// url -> ws://192.168.1.99:80/
int ws_rws_connect_url(char *url, ushort port, char *path);
int ws_rws_connected(void);

int ws_rws_send_text(char *str);
int ws_rws_disconnect(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_ */
