/*
 * dev_cfg.c
 *
 *  Created on: 2019年6月6日
 *      Author: luozhiyong
 */
#include "dev_cfg.h"


// 重启次数
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

// 运行时间，每写一次就是运行1分钟, 请每一分钟调用一次
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


                                                  
