
#include "devDataSent.h"

int manager_main(void)
{
	udp_hb_thread(); // �����������߳�
	udp_recv_thread();
	dev_sent_thread();

	return 0;
}


INIT_ENV_EXPORT(manager_main);
                                                  