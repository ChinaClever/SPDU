/*
 * ali_cfg.c
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */
#include "ali_cfg.h"

static struct sAli gAliCfg;

#define PRODUCT_KEY             PKG_USING_ALI_IOTKIT_PRODUCT_KEY
#define DEVICE_NAME             PKG_USING_ALI_IOTKIT_DEVICE_NAME
#define DEVICE_SECRET           PKG_USING_ALI_IOTKIT_DEVICE_SECRET

struct sAli *ali_cfg_get(void)
{
	struct sAli *cfg = &gAliCfg;

//	cfg->en = 1;
	sprintf(cfg->key, PRODUCT_KEY);
	sprintf(cfg->name, DEVICE_NAME);
	sprintf(cfg->secret, DEVICE_SECRET);

	return cfg;
}


void ali_cfg_set(void)
{

}
