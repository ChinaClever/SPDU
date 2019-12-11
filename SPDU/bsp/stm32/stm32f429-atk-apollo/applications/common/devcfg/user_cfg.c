/*
 * user_cfg.c
 *
 *  Created on: 2019年7月3日
 *      Author: luozhiyong
 */
#include "user_cfg.h"

void user_env_write(sUser *user)
{
	ef_set_env("user_name", user->name);
	ef_set_env("user_pass", user->pass);
}

void user_env_default(sUser *user)
{
	strcpy(user->name, "admin");
	strcpy(user->pass, "admin");
	user_env_write(user);
}

void user_env_read(sUser *user)
{
	char *res = ef_get_env("user_name");
	if(res) {
		strcpy(user->name, res);
		ef_get_env("user_pass");strcpy(user->pass, res);
	} else { // 读取失败，恢复默认值
		user_env_default(user);
	}
}

sUser *user_cfg_get(void)
{
	static sUser *user = nullptr;
	if(!user) {
		user = malloc(sizeof(sUser));
		memset(user, 0, sizeof(sUser));
		user_env_read(user);
	}

	return user;
}

void user_cfg_set(const char *name, const char *pass)
{
	sUser *user = user_cfg_get();

	strcpy(user->name, name);
	strcpy(user->pass, pass);
	user_env_write(user);
}
