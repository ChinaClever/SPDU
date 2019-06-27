/*
 * modbus_cfg.c
 *
 *  Created on: 2019Äê6ÔÂ25ÈÕ
 *      Author: luozhiyong
 */
#include "modbus_cfg.h"

static struct sMdCfg gMdCfg;

struct sMdCfg *md_get_cfg(void)
{
	struct sMdCfg *md = &gMdCfg;

	if(0 == md->port) {
		md->port = 502;
	}

	if(0 == md->addr) {
		 md->addr = 1;
	}

	if(0 == md->baud) {
		md->baud = 9600;
	}

	return md;
}


void md_set_cfg(struct sMdCfg *t)
{
	struct sMdCfg *md = &gMdCfg;
	md->en = t->en;
	md->port = t->port;
	md->addr = t->addr;
	md->baud = t->baud;

}

