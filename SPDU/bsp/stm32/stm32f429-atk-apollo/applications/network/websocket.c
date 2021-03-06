/*
 * websocket.c
 *
 *  Created on: 2019��6��12��
 *      Author: luozhiyong
 */
#include "librws.h"
#include <rtdbg.h>
#include <rtthread.h>
#include "websocket.h"

#if (RTTHREAD_VERSION < 30100)
#define DBG_SECTION_NAME "[LIBRWS.Test] "
#else
#define DBG_SECTION_NAME "LIBRWS.Test"
#endif
#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_COLOR

struct librws_app
{
	rt_bool_t init;
	rws_socket *socket;
};
typedef struct librws_app *librws_app_t;
static librws_app_t ws_app = RT_NULL;

static void ws_onopen(rws_socket socket)
{
	LOG_D("websocket connected. ");
	ws_app->init = RT_TRUE;
}

static void ws_onclose(rws_socket socket)
{
	rws_error error = rws_socket_get_error(socket);
	if (error) {
		LOG_E("websocket disconnect, error: %i, %s ", rws_error_get_code(error), rws_error_get_description(error));
	} else {
		LOG_D("websocket disconnect! ");
	}

	rws_socket_disconnect_and_release(ws_app->socket);
	ws_app->init = RT_FALSE;
}

static void ws_onmessage_text(rws_socket socket, const char *text, const unsigned int len)
{
	static char *buff = RT_NULL;
	if(!buff) buff = (char *)rt_malloc(384);

	rt_memset(buff, 0x00, 384);
	rt_memcpy(buff, text, len);
	LOG_D("websocket message(txt), %d(byte): %s ", len, buff);

	json_analysis(buff);
}

static void ws_onmessage_bin(rws_socket socket, const void *data, const unsigned int len)
{
	char *buff = RT_NULL;

	buff = (char *)rt_malloc(2048);

	rt_memset(buff, 0x00, 2048);
	rt_memcpy(buff, data, len);

	LOG_D("message(bin), %d(byte): %s ", len, buff);

	if (buff != RT_NULL)
	{
		rt_free(buff);
	}
}

int ws_rws_disconnect(void)
{
	if (ws_app->init) {
		rws_socket_disconnect_and_release(ws_app->socket);
		LOG_I("try disconnect websocket connection. ");
	}

	return RT_EOK;
}


/**
 * scheme -> ws / wss
 * host -> url
 * port -> 80 / 433
 * path -> ·��
 *
 */
int ws_rws_connect(char *scheme, char *host, int port, char *path)
{
	rws_bool ret = rws_false;

	if (ws_app == RT_NULL) {
		ws_app = (librws_app_t)rt_malloc_align(sizeof(struct librws_app), 4);
		rt_memset(ws_app, 0x00, sizeof(struct librws_app));
	} else if (ws_app->init) {
		ws_rws_disconnect();
	}

	ws_app->socket = rws_socket_create();
	if (ws_app->socket == RT_NULL) {
		LOG_E("librws socket create failed. ");
		return (-RT_ERROR);
	}

	rws_socket_set_url(ws_app->socket, scheme, host, port, path);
	rws_socket_set_on_connected(ws_app->socket, &ws_onopen);
	rws_socket_set_on_disconnected(ws_app->socket, &ws_onclose);
	rws_socket_set_on_received_text(ws_app->socket, &ws_onmessage_text);
	rws_socket_set_on_received_bin(ws_app->socket, &ws_onmessage_bin);

	rws_socket_set_custom_mode(ws_app->socket);  /* set custom mode */
	ret = rws_socket_connect(ws_app->socket);
	if (ret)  {
		LOG_D("try connect %s://%s:%d/%s ", scheme, host, port, path);
	} else {
		LOG_E("websocket connect %s://%s:%d/%s failed. ", scheme, host, port, path);
	}

	return ret;
}

// url -> ws://192.168.1.99:80/
int ws_rws_connect_url(char *url, ushort port, char *path)
{
	char scheme[8]={0}, host[20]={0};
	if(strlen(path) == 0) sprintf(path, "/");
	sscanf(url,"%s://%s",scheme, host);

	return ws_rws_connect(scheme, host, port, path);
}

int ws_rws_send_text(char *str)
{
	int ret = false;
	if (ws_app->init) {
		ret = rws_socket_send_text(ws_app->socket, str);
	}

	return ret;
}

int ws_rws_connected(void)
{
	return ws_app->init;
}
