/*
 * data_packet.c
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */
#include "data_packet.h"


sDataPacket *data_packet_get(int id)
{
	static sPackets* packets = nullptr;
	if(!packets) {
		packets = malloc(sizeof(sPackets));
		memset(packets, 0, sizeof(sPackets));
	}

	return &(packets->packet[id]);
}

