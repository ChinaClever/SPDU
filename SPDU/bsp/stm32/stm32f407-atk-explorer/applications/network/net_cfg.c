/*
 * net_cfg.c
 *
 *  Created on: 2019年6月27日
 *      Author: luozhiyong
 */
#include "net_cfg.h"

static struct sNetPush gNetPush;
extern void net_updata_init(void);

struct sNetPush *net_cfg_get(void)
{
	struct sNetPush *cfg =  &gNetPush;
	cfg->en = 0;
	strcpy(cfg->url, "192.168.100.215");
	strcpy(cfg->path, "/");
	cfg->port = 8080;
	cfg->mdelay = 15;

	return cfg;
}


void net_cfg_set(void)
{
	net_updata_init();

}

// 数据推送至少为15秒
int net_dalay_get(void)
{
	int ret = gNetPush.mdelay;
	if(ret < 15) {
		ret = 15;
	}

	return ret;
}
