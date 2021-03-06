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

char pWebQuest[256]={0};

void web_dev_reset(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *sel = webnet_request_get_query(request, "sel");

	int id = atoi(sel);
	if(id) { // 恢复出厂设置

	} else { // 设备复位

	}

	static const char* status = "sel=%s";
	webnet_session_printf(session, status, sel);
}


void web_dev_version(struct webnet_session* session)
{
	char *ptr=pWebQuest;

	ptr[0] = 0;
	sprintf(ptr, "version=0.0.1");
	ptr += strlen(ptr);

	webnet_session_printf(session, "%s", pWebQuest);
}


// AUTH 基本认证功能
void web_auth_init(void)
{
	char auth[20] = {0};
	struct sUser *user = user_cfg_get();
	sprintf(auth, "%s:%s", user->name, user->pass);
	webnet_auth_set("/", auth); // 设置认证信息：用户名及密码为 admin:admin
}




void web_main_entry(void *p)
{
    msleep(2100);
	web_auth_init();
	web_devstatus();
	web_thresholds();
	web_envs();

	web_modbus();
	web_network();

#ifdef PKG_USING_MYMQTT
	web_mqtt();
#endif

#ifdef PKG_USING_ALI_IOTKIT
	web_aliiot();
#endif

	web_user();
	web_ip_addr();
	web_ntp_time();

	webnet_cgi_register("getVersion", web_dev_version);
	webnet_cgi_register("reset", web_dev_reset);

	webnet_init();
}

static int web_init_thread(void)
{
    rt_thread_t thread = rt_thread_create("web_init", web_main_entry, NULL, 2*1024, 3, 5);
    if (thread != RT_NULL)  rt_thread_startup(thread);
    return 0;
}

INIT_ENV_EXPORT(web_init_thread);
