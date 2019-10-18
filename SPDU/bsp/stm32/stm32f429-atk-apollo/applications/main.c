/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */
#include <board.h>
#include <fal.h>
#include <easyflash.h>
#include "iwdg.h"

/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(B, 1)
#define FS_PARTITION_NAME  "filesystem"
extern void app_thread(void);


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

void init_flash()
{	
	/* Create a block device on the file system partition of spi flash */
    struct rt_device *flash_dev = fal_blk_device_create(FS_PARTITION_NAME);
    if (flash_dev == NULL) {
        rt_kprintf("Can't create a block device on '%s' partition.\n", FS_PARTITION_NAME);
    } else {
        rt_kprintf("Create a block device on the %s partition of flash successful.\n", FS_PARTITION_NAME);
    }

    /* mount the file system from "filesystem" partition of spi flash. */
    if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == 0) {
        rt_kprintf("Filesystem initialized!\n");
    } else {
        rt_kprintf("Failed to initialize filesystem!\n");
        rt_kprintf("You should create a filesystem on the block device first!\n");
    }
	
	// 创建文件系统命令：mkfs -t elm filesystem	
	if (easyflash_init() == 0){
		boot_times_env();
    }
}

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

	fal_init();
	init_flash();
	
	app_thread();
    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}

/**
 * Function    ota_app_vtor_reconfig
 * Description Set Vector Table base location to the start addr of app(RT_APP_PART_ADDR).
*/
static int ota_app_vtor_reconfig(void)
{
    #define NVIC_VTOR_MASK   0x3FFFFF80
    /* Set the Vector Table base location by user application firmware definition */
    SCB->VTOR = RT_APP_PART_ADDR & NVIC_VTOR_MASK;

    return 0;
}
INIT_BOARD_EXPORT(ota_app_vtor_reconfig);
