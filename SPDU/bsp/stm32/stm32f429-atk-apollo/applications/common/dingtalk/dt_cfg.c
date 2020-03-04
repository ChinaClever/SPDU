/*
 * dt_cfg.c
 *
 *  Created on: 2019Äê11ÔÂ20ÈÕ
 *      Author: luozhiyong
 */
#include "dt_cfg.h"

#define DT_Webhook "https://oapi.dingtalk.com/robot/send?access_token=56ff0885f3b0c5182bd59f402d702ce778addb3acc3060fcf3a0110d6bb7a880"
#define DT_KEY	"alarm"
#define DT_MOBILE	"18576689472"

void dt_cfg_init(sDtCfg *cfg)
{
	cfg->en = 1;
	cfg->isAtAll = 0;
	sprintf(cfg->webhook, DT_Webhook);
	sprintf(cfg->key, DT_KEY);
	sprintf(cfg->mobile, DT_MOBILE);
}

sDtCfg *dt_cfg_get(void)
{
	static sDtCfg *cfg = nullptr;
	if(!cfg) {
		cfg = malloc(sizeof(sDtCfg));
		memset(cfg, 0, sizeof(sDtCfg));
		dt_cfg_init(cfg);
	}

	return cfg;
}
