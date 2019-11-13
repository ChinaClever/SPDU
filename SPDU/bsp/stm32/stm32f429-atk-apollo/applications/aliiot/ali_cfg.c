/*
 * ali_cfg.c
 *
 *  Created on: 2019Äê7ÔÂ2ÈÕ
 *      Author: luozhiyong
 */
#include "ali_cfg.h"

#define PRODUCT_KEY             PKG_USING_ALI_IOTKIT_PRODUCT_KEY
#define DEVICE_NAME             PKG_USING_ALI_IOTKIT_DEVICE_NAME
#define DEVICE_SECRET           PKG_USING_ALI_IOTKIT_DEVICE_SECRET


void ali_env_write(sAli *ali)
{
	char key[32] = {0};
	uchar id = ali->id;

	sprintf(key, "ali_en_%d", id);
	ef_set_env_blob(key, &(ali->en), sizeof(ali->en));

	sprintf(key, "ali_name_%d", id);
	ef_set_env_blob(key, ali->name, strlen(ali->name));

	sprintf(key, "ali_key_%d", id);
	ef_set_env_blob(key, ali->key, strlen(ali->key));

	sprintf(key, "ali_dev_secret_%d", id);
	ef_set_env_blob(key, ali->dev_secret, strlen(ali->dev_secret));

	sprintf(key, "ali_pro_secret_%d", id);
	ef_set_env_blob(key, ali->pro_secret, strlen(ali->pro_secret));
}


void ali_env_default(struct sAli *ali)
{
//	ali->en = 1;
//	sprintf(ali->key, PRODUCT_KEY);
//	sprintf(ali->name, DEVICE_NAME);
//	sprintf(ali->secret, DEVICE_SECRET);
//	ali_env_write(ali);
}

void ali_env_read(struct sAli *ali)
{
	char key[32] = {0};
	uchar id = ali->id;

	sprintf(key, "ali_name_%d", id);
	ef_get_env_blob(key, ali->name, sizeof(ali->name), NULL);
	sprintf(key, "ali_en_%d", id);
	ef_get_env_blob(key, &(ali->en), sizeof(ali->en), NULL);

	sprintf(key, "ali_key_%d", id);
	ef_get_env_blob(key, ali->key, sizeof(ali->key), NULL);

	sprintf(key, "ali_dev_secret_%d", id);
	ef_get_env_blob(key, ali->dev_secret, sizeof(ali->dev_secret), NULL);

	sprintf(key, "ali_pro_secret_%d", id);
	ef_get_env_blob(key, ali->pro_secret, sizeof(ali->pro_secret), NULL);
}


sAli *ali_cfg_get(int id)
{
	static sAlis *cfg = nullptr;
	if(!cfg) {
		cfg = malloc(sizeof(sAlis));
		memset(cfg, 0, sizeof(sAlis));
		int i;
		for(i=0; i<=DEV_NUM; ++i) {
			sAli *ali = &(cfg->ali[i]);
			ali->id = i;
			ali->iot_devid = -1;
			ali_env_read(ali);
			ali->en = 1;   ////////===========
		}
	}

	return &(cfg->ali[id]);
}

int ali_cfg_getByIot(const int id)
{
	int i;
	sAli *ali = nullptr;
	for(i=0; i<=DEV_NUM; ++i) {
		if(ali->iot_devid == id) {
			return i;
		}
	}
	return -1;
}
