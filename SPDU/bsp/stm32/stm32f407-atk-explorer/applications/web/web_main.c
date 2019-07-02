/*
 * web_main.c
 *
 *	��wn_request.c�ļ� 60���м��룺
 *		if(0 == request->content_length) request->content_length = strlen(request->query);
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */

#include "web_main.h"



static void asp_var_version(struct webnet_session* session)
{
	RT_ASSERT(session != RT_NULL);

	static const char *version = "0.0.1";
	webnet_session_printf(session, version, RT_VERSION, RT_SUBVERSION, RT_REVISION);
}


// ASP �����滻���ܣ�����ƥ����ҳ������ <% %> ����а����ı������滻�ɴ�����ע���ִ�к���
void web_asp_var(void)
{
	webnet_asp_add_var("version", asp_var_version);
}

// AUTH ������֤����
void web_auth_init(void)
{
	char auth[20] = {0};
	sprintf(auth, "%s:%s", "admin", "admin");
	webnet_auth_set("/", auth); // ������֤��Ϣ���û���������Ϊ admin:admin
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


