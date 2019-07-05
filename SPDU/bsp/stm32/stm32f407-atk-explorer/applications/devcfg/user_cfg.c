/*
 * user_cfg.c
 *
 *  Created on: 2019年7月3日
 *      Author: luozhiyong
 */
#include "user_cfg.h"

static struct sUser gUser;


void user_env_write(struct sUser *user)
{
	ef_set_env_blob("user_name", user->name, strlen(user->name));
	ef_set_env_blob("user_pass", user->pass, strlen(user->pass));
}

void user_env_default(struct sUser *user)
{
	strcpy(user->name, "admin");
	strcpy(user->pass, "admin");
	user_env_write(user);
}

void user_env_read(struct sUser *user)
{
	int len = ef_get_env_blob("user_name", user->name, sizeof(user->name), NULL);
	if(len) {
		ef_get_env_blob("user_pass", user->pass, sizeof(user->pass), NULL);
	} else { // 读取失败，恢复默认值
		user_env_default(user);
	}
}

struct sUser *user_cfg_get(void)
{
	struct sUser *user = &gUser;
	user_env_read(user);

	return user;
}

void user_cfg_set(const char *name, const char *pass)
{
	struct sUser *user = &gUser;

	strcpy(user->name, name);
	strcpy(user->pass, pass);
	user_env_write(user);
}
