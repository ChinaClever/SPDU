/*
 * dt_cfg.h
 *
 *  Created on: 2019Äê11ÔÂ20ÈÕ
 *      Author: luozhiyong
 */

#ifndef SPDU_BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_DINGTALK_DT_CFG_H_
#define SPDU_BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_DINGTALK_DT_CFG_H_
#include "http_client.h"

typedef struct Dt_sCfg
{
    boolean en;
    boolean isAtAll;
    char webhook[192];
    char key[16];
    char *content;
    char mobile[16];
}sDtCfg;

sDtCfg *dt_cfg_get(void);

#endif /* SPDU_BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_DINGTALK_DT_CFG_H_ */
