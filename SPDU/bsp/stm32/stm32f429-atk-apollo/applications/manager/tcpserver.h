/*
 * tcpserver.h
 *
 *  Created on: 2016��8��5��
 *      Author: lzy
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_
#include "udpdebug.h"
#include "netDataSegment.h"

int tcp_creatSocket(int port, int lisnum);
void tcp_server_thread(void);

#endif /* TCPSERVER_H_ */
