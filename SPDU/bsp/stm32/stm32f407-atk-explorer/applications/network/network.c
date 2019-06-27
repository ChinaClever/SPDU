/*
 * network.c
 *
 *  Created on: 2019年6月27日
 *      Author: luozhiyong
 */
#include "network.h"

enum eNets { Udp=1, Tcp, WebSocket, Http};


// 动态延时，当延时时间变化时立即做出响应
void net_delay()
{
	ushort i, d=get_net_dalay();

	for(i=0; i<d; ++i) {
		sleep(1);
		d=get_net_dalay();
	}
}

// 根据条件来连接
void net_updata_init(void)
{
	struct sNetPush *net = get_net_cfg();
	switch(net->en) {
	case Udp: udp_client_init(net->url, net->port); break;
	case Tcp: tcp_push_init(net->url, net->port); break;
	case WebSocket: ws_rws_connect_url(net->url, net->port, net->path); break;
	}
}

int net_connect_err(struct sNetPush *net)
{
	net->connects++;
	int ret = net->connects * 2;
	if(ret > 60) ret = 60;
	sleep(ret); // 延时变长

	return ret;
}

// 检查是否已连接，
int net_check_connect(void)
{
	struct sNetPush *net = get_net_cfg();
	int ret = net->en;

	if(ret > 0) {
		switch(net->en) {
		case Udp: ret = udp_client_connected(); break;
		case Tcp: ret = tcp_push_connected(); break;
		case WebSocket: ret = ws_rws_connected(); break;
		}

		if(ret > 0) {
			net->connects = 0;
		} else {
			net_connect_err(net);
			net_updata_init();
		}
	}

	return net->en;
}

void net_push_http(char *json)
{
	struct sNetPush *net = get_net_cfg();
	int ret = http_post(net->url, json);
	if(ret <= 0) {
		net_connect_err(net);
	}
}

void net_updata_task(void *arg)
{
	char ret, *json=NULL;
	udp_serv_thread();
	tcp_serv_thread();

	while(1) {
		ret = net_check_connect();
		if(ret) {
			json = json_build();
			switch(ret) {
			case Udp:  udp_client_sent(json); break;
			case Tcp:  tcp_push_data(json); break;
			case WebSocket:  ws_rws_send_text(json); break;
			case Http:  net_push_http(json); break;
			}
			net_delay();
			free(json);
		}
		sleep(1+rand()%3);
	}
}


void net_work_thread(void)
{
	rt_thread_t tid = rt_thread_create("network",net_updata_task, NULL,4*512,28, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

