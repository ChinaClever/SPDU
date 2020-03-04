/*
 * mqtt_thread.c
 *
 *  Created on: 2019年10月31日
 *      Author: luozhiyong
 */
#include "mqtt_thread.h"

// 动态延时，当延时时间变化时立即做出响应
void mqtt_delay()
{
    ushort i, d=mqtt_cfg_mdelay();

    for(i=0; i<d; ++i) {
        sleep(1);
        d=mqtt_cfg_mdelay();
    }
}


// 一个设备分开来传输数据 因为这里用到的mqtt传输最大长度为512
static void mqtt_done_work(MQTTClient *client, sMqtt *ci, ushort id)
{
    char *msg = json_build(id);
    if(msg){
        ci->pub_payload = msg;
        mqtt_publish(client, ci);
        msleep(25);
        free(msg);
    }
}


static void mqtt_task(void *p)
{
    int i, res;
    sleep(4);
    MQTTClient client;
    sMqtt *ci = mqtt_cfg_get();

    client.isconnected = 0;
    client.is_quit = 0;
    client.buf_size = 0;
    while(1)
    {
        res = mqtt_connect(&client, ci);
        if(res > 0) {
            for(i=1; i<=DEV_NUM; ++i) {
                mqtt_done_work(&client,ci,i);
            }
            mqtt_delay();
        } else {
            sleep(5);
        }
    }
}

static int mqtt_init_thread(void)
{
    rt_thread_t tid = rt_thread_create("mqttc",mqtt_task, NULL,3*512,24, 25);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

INIT_ENV_EXPORT(mqtt_init_thread);
