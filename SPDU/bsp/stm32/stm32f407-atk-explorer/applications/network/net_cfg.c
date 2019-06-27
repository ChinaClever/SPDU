/*
 * net_cfg.c
 *
 *  Created on: 2019��6��27��
 *      Author: luozhiyong
 */
#include "net_cfg.h"

static struct sNetPush gNetPush;
extern void net_updata_init(void);

struct sNetPush *get_net_cfg(void)
{
	struct sNetPush *cfg =  &gNetPush;
	cfg->en = 1;
	strcpy(cfg->url, "192.168.100.215");
	strcpy(cfg->path, "/");
	cfg->port = 8080;
	cfg->mdelay = 15;

	return cfg;
}


void set_net_cfg(void)
{
	net_updata_init();

}

// ������������Ϊ15��
int get_net_dalay(void)
{
	int ret = gNetPush.mdelay;
	if(ret < 15) {
		ret = 5;
	}

	return ret;
}
