/*
 * ip_cfg.c
 *
 *  Created on: 2019年7月4日
 *      Author: luozhiyong
 */
#include "ip_cfg.h"

static struct sNetAddr gIpAddr;


void ip_env_write(struct sNetAddr *ip)
{
	ef_set_env_blob("ip_v4", ip->ip, strlen(ip->ip));
	ef_set_env_blob("ip_mask", ip->mask, strlen(ip->mask));
	ef_set_env_blob("ip_gw", ip->gw, strlen(ip->gw));
	ef_set_env_blob("ip_dns", ip->dns, strlen(ip->dns));
}

void ip_env_default(struct sNetAddr *ip)
{
	strcpy(ip->ip, "192.168.1.163");
	strcpy(ip->mask, "255.255.255.0");
	strcpy(ip->gw, "192.168.1.1");
	strcpy(ip->dns, "202.96.128.86");
	ip_env_write(ip);
}

void ip_env_read(struct sNetAddr *ip)
{
	int len = ef_get_env_blob("ip_v4", ip->ip, sizeof(ip->ip), NULL);
	if(len) {
		ef_get_env_blob("ip_mask", ip->mask, sizeof(ip->mask), NULL);
		ef_get_env_blob("ip_gw", ip->gw, sizeof(ip->gw), NULL);
		ef_get_env_blob("ip_dns", ip->dns, sizeof(ip->dns), NULL);
	} else { // 读取失败，恢复默认值
		ip_env_default(ip);
	}
}


struct sNetAddr *ip_cfg_get(void)
{
	struct sNetAddr *ip = &gIpAddr;
	if(!strlen(ip->ip)) {
		ip_env_read(ip);
	}

	return ip;
}

void ip_cfg_set(void)
{
	struct sNetAddr *ip = &gIpAddr;
	ip_env_write(ip);
}
