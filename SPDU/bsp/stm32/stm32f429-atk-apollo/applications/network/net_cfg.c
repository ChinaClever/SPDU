/*
 * net_cfg.c
 *
 *  Created on: 2019年6月27日
 *      Author: luozhiyong
 */
#include "net_cfg.h"

static sNetPush gNetPush;
extern void net_updata_init(void);


void net_env_write(sNetPush *net)
{
	ef_set_env_blob("net_url", net->url, strlen(net->url));
	ef_set_env_blob("net_path", net->path, strlen(net->path));
	ef_set_env_blob("net_en", &(net->en), sizeof(net->en));
	ef_set_env_blob("net_port", &(net->port), sizeof(net->port));
	ef_set_env_blob("net_mdelay", &(net->mdelay), sizeof(net->mdelay));
	ef_set_env_blob("net_connects", &(net->connects), sizeof(net->connects));
}

void net_env_default(sNetPush *cfg)
{
	cfg->en = 0;
	strcpy(cfg->url, "192.168.1.215");
	strcpy(cfg->path, "/");
	cfg->port = 8080;
	cfg->mdelay = 15;
	net_env_write(cfg);
}

void net_env_read(struct sNetPush *net)
{
	int len = ef_get_env_blob("net_url", net->url, sizeof(net->url), NULL);
	if(len) {
		ef_get_env_blob("net_en", &(net->en), sizeof(net->en), NULL);
		ef_get_env_blob("net_port", &(net->port), sizeof(net->port), NULL);
		ef_get_env_blob("net_path", net->path, sizeof(net->path), NULL);
		ef_get_env_blob("net_mdelay", &(net->mdelay), sizeof(net->mdelay), NULL);
		ef_get_env_blob("net_connects", &(net->connects), sizeof(net->connects), NULL);
	} else { // 读取失败，恢复默认值
		net_env_default(net);
	}
}


sNetPush *net_cfg_get(void)
{
	sNetPush *cfg =  &gNetPush;
	if(!strlen(cfg->url)) {
		net_env_read(cfg);
	}

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
	if(ret < 5) {
		ret = 5;
	}

	return ret;
}
