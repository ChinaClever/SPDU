/*
 * ip_cfg.c
 *
 *  Created on: 2019年7月4日
 *      Author: luozhiyong
 */
#include "ip_cfg.h"

void ip_env_write(sNetAddr *ip)
{
	ef_set_env("ip_v4", ip->ip);
	ef_set_env("ip_mask", ip->mask);
	ef_set_env("ip_gw", ip->gw);
	ef_set_env("ip_dns", ip->dns);
}

void ip_env_default(sNetAddr *ip)
{
	strcpy(ip->ip, "192.168.1.163");
	strcpy(ip->mask, "255.255.255.0");
	strcpy(ip->gw, "192.168.1.1");
	strcpy(ip->dns, "202.96.128.86");
	ip_env_write(ip);
}

void ip_env_read(sNetAddr *ip)
{
	char *res = ef_get_env("ip_v4");
	if(res) {
		strcpy(ip->ip, res);
		ef_get_env("ip_mask"); strcpy(ip->mask, res);
		ef_get_env("ip_gw");strcpy(ip->gw, res);
		ef_get_env("ip_dns");strcpy(ip->dns, res);
	} else { // 读取失败，恢复默认值
		ip_env_default(ip);
	}
}


sNetAddr *ip_cfg_get(void)
{
	static sNetAddr *ip =  nullptr;
	if(!ip) {
		ip = malloc(sizeof(sNetAddr));
		memset(ip, 0, sizeof(sNetAddr));
		ip_env_read(ip);
	}

	return ip;
}

void ip_cfg_set(void)
{
	struct sNetAddr *ip = ip_cfg_get();
	ip_env_write(ip);
}
