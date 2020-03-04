/*
 * modbus_cfg.c
 *
 *  Created on: 2019年6月25日
 *      Author: luozhiyong
 */
#include "modbus_cfg.h"


void mb_env_write(sMdCfg *mb)
{
	ef_set_env_blob("mb_en", &(mb->en), sizeof(mb->en));
	ef_set_env_blob("mb_port", &(mb->port), sizeof(mb->port));
}

void mb_env_default(sMdCfg *mb)
{
	mb->en = 1;
	mb->port = 502;
	mb_env_write(mb);
}

void mb_env_read(sMdCfg *mb)
{
	int len = ef_get_env_blob("mb_en", &(mb->en), sizeof(mb->en), NULL);
	if(len) {
		ef_get_env_blob("mb_port", &(mb->port), sizeof(mb->port), NULL);
	} else { // 读取失败，恢复默认值
		mb_env_default(mb);
	}
}


sMdCfg *mb_cfg_get(void)
{
	static sMdCfg *mb = nullptr;
	if(!mb) {
		mb = malloc(sizeof(sMdCfg));
		memset(mb, 0, sizeof(sMdCfg));
		mb_env_read(mb);
	}
	return mb;
}


void mb_cfg_set(sMdCfg *t)
{
	struct sMdCfg *mb = mb_cfg_get();
	mb->en = t->en;
	mb->port = t->port;
	mb_env_write(mb);
}

