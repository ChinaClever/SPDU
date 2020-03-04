/*
 * rtu_thread.c
 *
 *  Created on: 2019年10月21日
 *      Author: luozhiyong
 */
#include "rtu_thread.h"



static void rtu_task(int id, sRtu *rtu, sRtuRecv *rtuRecv)
{
    rtuRecv->data = data_packet_get(id);
    rtu->sentLen = rtu_cmdBuf(id, rtu->sentBuf);
    if(rtuRecv->data->offLine > 0) rtuRecv->data->offLine--;

    short rtn = rtu_trans(rtu);
    if(rtn > 0) {
        boolean ret = rtu_recv_packet(rtu->recvBuf, rtn, rtuRecv);
        if(ret) {
            rtuRecv->data->offLine = 3;
            //rt_kprintf("rtu recv packet OK %d\n", id);
        } else {
            // rt_kprintf("rtu recv packet err %d\n", id);
        }
    } else {
       // rt_kprintf("rtu recv no len err %d\n", id);
    }
}


static int rtu_set_task(sRtu *rtu)
{
    int res, ret;

    do {
        ret = rtu_getCmd(rtu);
        if(ret > 0) {
            res = rtu_sent(rtu);
            if(memcmp(rtu->sentBuf, rtu->recvBuf,res)) {
                sleep(1); res = rtu_trans(rtu);  // 命令发送失败，再发一次
                rt_kprintf("rtu set cmd err %d\n", res);
            } else {
                rt_kprintf("rtu set cmd OK %d\n", res);
            }
            msleep(650);
        }
    } while(ret > 0);

    return ret;
}


static void rtu_thread_entry(void *arg)
{
    sRtuRecv rtuRecv;
    int i, id = (uint)arg;
    msleep((id+1)*100);
    sRtu *rtu = rtu_cfg_get(id);
    rtu->dev = rtu_open(rtu->name);

    ///// 测试用
    if(id == 0)	rtu->start = rtu->end = 1;

    while (1)
    {
        //if(id == 0) rtu_clean_ele(1);
        for(i=rtu->start; i<=rtu->end; ++i) {
            rtu_set_task(rtu); // 先发设置命令
            rtu_task(i, rtu, &rtuRecv);
            msleep(450);
        }
        msleep(50);
    }
}


void rtu_thread_pool(void *p)
{
    char name[8]={0};
    uint i=0, num=UARTS_NUM;

    msleep(350);
    rtus_cfg_get();
    for(i=0; i<num; ++i) {
        sprintf(name, "rtu_%d", i+1);
        rt_thread_t thread = rt_thread_create(name, rtu_thread_entry, (void *)(i), 512, 14, 20);   //// 13+i
        if (thread != RT_NULL)  rt_thread_startup(thread);
    }
}

static int rtu_thread_init(void)
{
    rt_thread_t thread = rt_thread_create("rtu_init", rtu_thread_pool, NULL, 3*512, 14, 5);
    if (thread != RT_NULL)  rt_thread_startup(thread);
    return 0;
}

INIT_ENV_EXPORT(rtu_thread_init);
