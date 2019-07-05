/*
 * dev_cfg.c
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */
#include "dev_cfg.h"


// ��������
void boot_times_env(void)
{
    uint32_t i_boot_times = NULL;
    char c_new_boot_times[11] = {0};

    ef_get_env_blob("boot_times", c_new_boot_times, 11, NULL);
    i_boot_times = atol(c_new_boot_times);

    i_boot_times++;
    rt_kprintf("===============================================\n");
    rt_kprintf("The system now boot %d times\n", i_boot_times);
    rt_kprintf("===============================================\n");

    sprintf(c_new_boot_times, "%d", i_boot_times);
    ef_set_env_blob("boot_times", c_new_boot_times, strlen(c_new_boot_times));
}

// ����ʱ�䣬ÿдһ�ξ�������1����, ��ÿһ���ӵ���һ��
void run_times_env(void)
{
    uint32_t i_run_times = NULL;
    char c_new_run_times[11] = {0};

    ef_get_env_blob("run_times", c_new_run_times, 11, NULL);
    i_run_times = atol(c_new_run_times);

    i_run_times++;
    rt_kprintf("===============================================\n");
    rt_kprintf("The system now run %d times\n", i_run_times);
    rt_kprintf("===============================================\n");
    sprintf(c_new_run_times, "%d", i_run_times);
    ef_set_env_blob("run_times", c_new_run_times, strlen(c_new_run_times));
}


                                                  
