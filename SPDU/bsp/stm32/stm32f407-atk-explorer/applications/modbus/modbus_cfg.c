/*
 * modbus_cfg.c
 *
 *  Created on: 2019年6月25日
 *      Author: luozhiyong
 */
#include "modbus_cfg.h"

static struct sMdCfg gMdCfg;


void mb_env_write(struct sMdCfg *mb)
{
	ef_set_env_blob("mb_port", &(mb->port), sizeof(mb->port));
	ef_set_env_blob("mb_addr", &(mb->addr), sizeof(mb->addr));
	ef_set_env_blob("mb_baud", &(mb->baud), sizeof(mb->baud));
	ef_set_env_blob("mb_en", &(mb->en), sizeof(mb->en));
}

void mb_env_default(struct sMdCfg *mb)
{
	mb->en = 0;
	mb->port = 502;
	mb->addr = 1;
	mb->baud = 9600;
	mb_env_write(mb);
}

void mb_env_read(struct sMdCfg *mb)
{
	int len = ef_get_env_blob("mb_en", &(mb->en), sizeof(mb->en), NULL);
	if(len) {
		ef_get_env_blob("mb_port", &(mb->port), sizeof(mb->port), NULL);
		ef_get_env_blob("mb_addr", &(mb->addr), sizeof(mb->addr), NULL);
		ef_get_env_blob("mb_baud", &(mb->baud), sizeof(mb->baud), NULL);
	} else { // 读取失败，恢复默认值
		mb_env_default(mb);
	}
}


struct sMdCfg *mb_cfg_get(void)
{
	struct sMdCfg *mb = &gMdCfg;
	if(0 == mb->port) {
		mb_env_read(mb);
	}
	return mb;
}


void mb_cfg_set(struct sMdCfg *t)
{
	struct sMdCfg *mb = &gMdCfg;
	mb->en = t->en;
	mb->port = t->port;
	mb->addr = t->addr;
	mb->baud = t->baud;
	mb_env_write(mb);
}

