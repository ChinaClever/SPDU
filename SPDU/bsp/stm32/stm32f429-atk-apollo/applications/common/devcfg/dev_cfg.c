/*
 * dev_cfg.c
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */
#include "dev_cfg.h"


// ����ʱ�䣬ÿдһ�ξ�������1����, ��ÿһ���ӵ���һ��
void run_times_env(void)
{
    uint i_run_times = 0;
    char *res = ef_get_env("run_times");
    if(res) i_run_times = atol(res);

    rt_kprintf("===============================================\n");
    rt_kprintf("The system now run %d times\n", ++i_run_times);
    rt_kprintf("===============================================\n");

    char c_new_run_times[11] = {0};
    sprintf(c_new_run_times, "%d", i_run_times);
    ef_set_env("run_times", c_new_run_times);
}


                                                  
