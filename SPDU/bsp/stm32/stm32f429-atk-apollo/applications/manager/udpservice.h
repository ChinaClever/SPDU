/*
 * udpservice.h
 *
 *  Created on: 2016��7��29��
 *      Author: Lzy
 */

#ifndef UDP_UDPSERVICE_H_
#define UDP_UDPSERVICE_H_
#include "udpdebug.h"
#include "netDataSegment.h"

#define UDP_BUF_SIZE	256 /*���ݻ�������С�� IP�豸ʹ��256�� ARM9ϵ���豸ʹ��512*/

int udp_serviceSocket(int port);
int udp_serviceRecvData(int sockfd,struct sockaddr_in *client_addr,uchar *recv_data);
void udp_recv_thread(void);


#endif /* UDP_UDPSERVICE_H_ */
