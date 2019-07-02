/*
 * web_main.c
 *
 *	在wn_request.c文件 60行中加入：
 *		if(0 == request->content_length) request->content_length = strlen(request->query);
 *
 *  Created on: 2019年6月6日
 *      Author: luozhiyong
 */

#include "web_main.h"



static void asp_var_version(struct webnet_session* session)
{
	RT_ASSERT(session != RT_NULL);

	static const char *version = "0.0.1";
	webnet_session_printf(session, version, RT_VERSION, RT_SUBVERSION, RT_REVISION);
}


// ASP 变量替换功能，可以匹配网页代码中 <% %> 标记中包含的变量，替换成代码中注册的执行函数
void web_asp_var(void)
{
	webnet_asp_add_var("version", asp_var_version);
}

// AUTH 基本认证功能
void web_auth_init(void)
{
	char auth[20] = {0};
	sprintf(auth, "%s:%s", "admin", "admin");
	webnet_auth_set("/", auth); // 设置认证信息：用户名及密码为 admin:admin
}

void web_main(void)
{
	web_auth_init();
	web_asp_var();

	web_output_sw();
	web_timer_sw();
	web_seq_timer();

	web_modbus();
	web_network();
	web_mqtt();
	web_aliiot();

	webnet_init();
}


