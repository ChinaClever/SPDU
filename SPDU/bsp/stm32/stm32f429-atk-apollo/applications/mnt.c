#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <fal.h>
#include <easyflash.h>

#define FS_PARTITION_NAME  "filesystem"

#if 1
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
#endif

// 重启次数
void boot_times_env(void)
{
    int i_boot_times = 0;
    char *res = ef_get_env("boot_times");
    if(res) i_boot_times = atol(res);

    rt_kprintf("===============================================\n");
    rt_kprintf("The system now boot %d times\n", i_boot_times++);
    rt_kprintf("===============================================\n");

    char c_new_boot_times[11] = {0};
    sprintf(c_new_boot_times, "%d", i_boot_times);
    ef_set_env("boot_times", c_new_boot_times);
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
        rt_kprintf("W25Q  mount successful! Filesystem initialized!\n");
    } else {
        rt_kprintf("Failed to initialize filesystem!\n");
        rt_kprintf("You should create a filesystem on the block device first!\n");
    }
}

int mnt_init(void)
{
    fal_init();
    init_flash();

    // 创建文件系统命令：mkfs -t elm filesystem
    if (easyflash_init() == 0){
        boot_times_env();
    }

    return 0;
}


INIT_ENV_EXPORT(mnt_init);
#endif
