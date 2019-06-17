/*
 * websocket.h
 *
 *  Created on: 2019Äê6ÔÂ12ÈÕ
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_
#include "../json/json_iot.h"

// url -> ws://192.168.1.99:80/
int ws_rws_connect_url(char *url);

int ws_rws_send_text(char *str);
int ws_rws_disconnect(void);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_NETWORK_WEBSOCKET_H_ */
