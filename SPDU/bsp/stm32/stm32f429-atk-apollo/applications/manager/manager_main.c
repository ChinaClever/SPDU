
#include "devDataSent.h"
#include "tcpserver.h"

int manager_main()
{
	udp_hb_thread(); // 创建心跳包线程
	//tcp_server_thread();
	udp_server_thread();
	dev_sent_thread();

	return 0;
}


