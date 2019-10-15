/*
 * web_outputsw.c
 *
 *  Created on: 2019年6月20日
 *      Author: luozhiyong
 */
#include "web_outputsw.h"

char pWebQuest[256]={0};

void web_op_setSw(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *sw_value = webnet_request_get_query(request, "sw");

	// id为0时，表示全开全关，从1开始
	int id = atoi(id_value);
	int sw = atoi(sw_value);
	if(id) {
		 sw_pin_write(id-1, sw);
	} else {
		 sw_all_write(sw);
	}

	static const char* status = "id=%d&sw=%d";
	webnet_session_printf(session, status, id, sw);
}


void web_op_outputNum(struct webnet_session* session)
{
	char num = getOutputNum();
	static const char* status = "num=%d";
	webnet_session_printf(session, status, num);
}

void web_op_status(struct webnet_session* session)
{
	static char qure[128] = {0};
	char num, i,v, *ptr=qure;

	num = getOutputNum();
	sprintf(ptr, "num=%d", num);
	for(i=0; i<num; ++i) {
		ptr += strlen(ptr);
		v = getSwStatus(i);
		sprintf(ptr, "&sw_%d=%d",i+1, v);
	}

	webnet_session_printf(session, "%s", qure);
}

void web_op_setInitial(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *sel_value = webnet_request_get_query(request, "sel");

	// id为0时，表示全开全关，从1开始
	int id = atoi(id_value);
	int sel = atoi(sel_value);
	if(id) {
		setInitialStatus(id-1, sel);
	} else {
		setAllInitialStatus(sel);
	}

	static const char* status = "id=%d&sel=%d";
	webnet_session_printf(session, status, id, sel);
}


void web_op_initial(struct webnet_session* session)
{
	char num, i,v, *ptr=pWebQuest;

	num = getOutputNum();
	sprintf(ptr, "num=%d", num);
	for(i=0; i<num; ++i) {
		ptr += strlen(ptr);
		v = getInitialStatus(i);
		sprintf(ptr, "&sel_%d=%d",i+1, v);
	}

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_op_setSeqSw(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *sw_value = webnet_request_get_query(request, "sw");
	const char *sec_value = webnet_request_get_query(request, "sec");

	int sw = atoi(sw_value);
	int sec = atoi(sec_value);
	sw_seq_thread(sw, sec);

	static const char* status = "sw=%d&sec=%d";
	webnet_session_printf(session, status, sw, sec);
}

void web_op_setResetSw(struct webnet_session* session)
{
	struct webnet_request* request = session->request;
	const char *id_value = webnet_request_get_query(request, "id");
	const char *sec_value = webnet_request_get_query(request, "sec");

	int id = atoi(id_value);
	int sec = atoi(sec_value);
	sw_reset_thread(id, sec);

	static const char* status = "id=%d&sec=%d";
	webnet_session_printf(session, status, id, sec);
}

void web_output_sw(void)
{
	webnet_cgi_register("setSw", web_op_setSw);
	webnet_cgi_register("getOutputNum", web_op_outputNum);
	webnet_cgi_register("getOutputStatus", web_op_status);

	webnet_cgi_register("getInitial", web_op_initial);
	webnet_cgi_register("setInitial", web_op_setInitial);
	webnet_cgi_register("setSeqSw", web_op_setSeqSw);
	webnet_cgi_register("setSwReset", web_op_setResetSw);
}
