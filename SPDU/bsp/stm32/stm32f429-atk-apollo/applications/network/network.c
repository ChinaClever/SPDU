/*
 * network.c
 *
 *  Created on: 2019��6��27��
 *      Author: luozhiyong
 */
#include "network.h"

enum eNets { Udp=1, WebSocket};

// ��̬��ʱ������ʱʱ��仯ʱ����������Ӧ
void net_delay()
{
    ushort i, d=net_dalay_get();

    for(i=0; i<d; ++i) {
        sleep(1);
        d=net_dalay_get();
    }
}

// ��������������
void net_updata_init(void)
{
    sNetPush *net = net_cfg_get();
    switch(net->en) {
    case Udp: udp_client_init(net->url, net->port); break;
    case WebSocket: ws_rws_connect_url(net->url, net->port, net->path); break;
    }
}

int net_connect_err(struct sNetPush *net)
{
    net->connects++;
    int ret = net->connects * 2;
    if(ret > 60) ret = 60;
    sleep(ret); // ��ʱ�䳤

    return ret;
}

// ����Ƿ������ӣ�
int net_check_connect(void)
{
    sNetPush *net = net_cfg_get();
    int ret = net->en;

//    net->en = 1;
//    sprintf(net->url, "192.168.1.215");
//    net->port = 8080;

    if(ret > 0) {
        switch(net->en) {
        case Udp: ret = udp_client_connected(); break;
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

void net_updata_task(void *arg)
{
    char i, ret, *json=NULL;
    rt_thread_mdelay(3500);
    udp_serv_thread();

    while(1) {
        ret = net_check_connect();
        if(ret) {
            for(i=1; i<=DEV_NUM; ++i) {
                json = json_build(i);
                if(!json){msleep(1);continue;}
                switch(ret) {
                case Udp:  ret = udp_client_sent(json); break;
                case WebSocket:  ret = ws_rws_send_text(json); break;
                }

                free(json);
                if(ret) msleep(15); else break;
            }
            net_delay();
        } else {
            msleep(100+rand()%150);
        }
    }
}

int net_work_thread(void)
{
    rt_thread_t tid = rt_thread_create("net_work",net_updata_task, NULL, 4*512,25, 25);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

INIT_ENV_EXPORT(net_work_thread);
