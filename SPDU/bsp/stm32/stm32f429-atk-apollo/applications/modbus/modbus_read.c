/*
 * modbus_read.c
 *
 *  Created on: 2019年10月24日
 *      Author: luozhiyong
 */
#include "modbus_read.h"


ushort *mb_read_dataUnit(ushort *reg, sDataUnit *unit, uchar i)
{
	*reg++ = unit->value[i];
	*reg++ = unit->min[i];
	*reg++ = unit->max[i];

	return reg;
}

ushort *mb_read_objData(ushort *reg, sObjData *obj)
{
	ushort i;

	for(i=0; i<obj->size; ++i) {
		reg = mb_read_dataUnit(reg, &(obj->vol), i);
		reg = mb_read_dataUnit(reg, &(obj->cur), i);

		*reg++ = obj->sw[i];
		*reg++ = obj->pow[i];
		*reg++ = obj->pf[i];
		*reg++ = (obj->ele[i] >> 16);
		*reg++ = (obj->ele[i]&0xffff);
	}

	return reg;
}

ushort *mb_read_envData(ushort *reg, sEnvData *env)
{
	ushort i;

	for(i=0; i<env->size; ++i) {
		reg = mb_read_dataUnit(reg, &(env->tem), i);
		reg = mb_read_dataUnit(reg, &(env->hum), i);
	}

	return reg;
}


int mb_read_packet(uchar addr, modbus_mapping_t *mb)
{
	ushort *ptr = &(mb->tab_registers[2]);
	sDataPacket *packet = data_packet_get(addr);

	if(packet->offLine) {
		sObjData *line = &(packet->data.line); // 相数据
		sEnvData *env =  &(packet->data.env);
		ptr = mb_read_objData(ptr, line);
		ptr = mb_read_envData(ptr, env);

		*ptr++ = packet->devSpec;
		if(packet->dc) {
			*ptr = packet->hz;
		} else {
			*ptr = line->pl[0];
		}
	}

	return packet->offLine;
}


