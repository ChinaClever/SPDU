
#include "devDataSent.h"

int manager_main(void)
{
	udp_hb_thread(); // 创建心跳包线程
	udp_recv_thread();
	dev_sent_thread();

	return 0;
}


INIT_ENV_EXPORT(manager_main);
                                                  