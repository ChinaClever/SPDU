/*
 * rtu_set.c
 *
 *  Created on: 2019年10月23日
 *      Author: luozhiyong
 */
#include "rtu_setcmd.h"

int rtu_setCmd(sRtuSetCmd *cmd)
{
	sDataPacket *packet = data_packet_get(cmd->addr);
	if(packet->offLine > 0) {
		uchar *buf = malloc(RTU_CMD_LEN+2);
		int ret = rtu_sentCmd(cmd, buf);

		sRtu *rtu= rtu_cfg_addr(cmd->addr);
		list_t *list = rtu->cmds;
		list_rpush(list, list_node_new(buf)); // 从尾部增加节点
	}

	return packet->offLine;
}


int rtu_getCmd(sRtu *rtu)
{
	int ret = RTU_CMD_LEN;
	list_t *list = rtu->cmds;
	list_node_t *node = list_at(list, 0);
	if(node) {
		memcpy(rtu->sentBuf, node->val, ret);
		list_remove(list, node);
	} else {
		ret = 0;
	}
	rtu->sentLen = ret;

	return ret;
}


int rtu_setReg(uchar addr, ushort reg, ushort value)
{
	sRtuSetCmd cmd;
	cmd.addr = addr;
	cmd.reg = reg;
	cmd.value = value;
	return rtu_setCmd(&cmd);
}

int rtu_clean_ele(uchar addr)
{
	return rtu_setReg(addr, SI_ELE_CMD, 0xf0);
}
