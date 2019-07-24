/*
 * ali_cfg.c
 *
 *  Created on: 2019年7月2日
 *      Author: luozhiyong
 */
#include "ali_cfg.h"

static struct sAli gAliCfg;

#define PRODUCT_KEY             PKG_USING_ALI_IOTKIT_PRODUCT_KEY
#define DEVICE_NAME             PKG_USING_ALI_IOTKIT_DEVICE_NAME
#define DEVICE_SECRET           PKG_USING_ALI_IOTKIT_DEVICE_SECRET


void ali_env_write(struct sAli *ali)
{
	ef_set_env_blob("ali_en", &(ali->en), sizeof(ali->en));
	ef_set_env_blob("ali_name", ali->name, strlen(ali->name));
	ef_set_env_blob("ali_key", ali->key, strlen(ali->key));
	ef_set_env_blob("ali_secret", ali->secret, strlen(ali->secret));
}

void ali_env_default(struct sAli *ali)
{
	ali->en = 1;
	sprintf(ali->key, PRODUCT_KEY);
	sprintf(ali->name, DEVICE_NAME);
	sprintf(ali->secret, DEVICE_SECRET);
	ali_env_write(ali);
}

void ali_env_read(struct sAli *ali)
{
	int len = ef_get_env_blob("ali_name", ali->name, sizeof(ali->name), NULL);
	if(len) {
		ef_get_env_blob("ali_en", &(ali->en), sizeof(ali->en), NULL);
		ef_get_env_blob("ali_key", ali->key, sizeof(ali->key), NULL);
		ef_get_env_blob("ali_secret", ali->secret, sizeof(ali->secret), NULL);
	} else { // 读取失败，恢复默认值
		ali_env_default(ali);
	}
}


struct sAli *ali_cfg_get(void)
{
	struct sAli *cfg = &gAliCfg;
	if(!strlen(cfg->name)) {
		ali_env_read(cfg);
	}

	return cfg;
}


void ali_cfg_set(void)
{
	struct sAli *cfg = &gAliCfg;
	ali_env_write(cfg);
}
