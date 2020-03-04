/*
 * snmp_main.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: luozhiyong
 */
#include "lwip/snmp.h"
#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "lwip/apps/snmp_mib2.h"
#include "lwip/apps/snmp_scalar.h"

extern const struct snmp_scalar_array_node pdu_mib_snmp_root;

static const struct snmp_node *const pdu_mib_nodes[] = {
  &pdu_mib_snmp_root.node.node
};

static const struct snmp_tree_node pdu_mib_root = SNMP_CREATE_TREE_NODE(1, pdu_mib_nodes);

static const u32_t  pdu_mib_base_oid_arr[] = { 1, 3, 6, 1, 4, 1,30966,20};
static const struct snmp_mib pdu_mib = SNMP_MIB_CREATE(pdu_mib_base_oid_arr, &pdu_mib_root.node);

static const struct snmp_mib *dev_snmp_mibs[] = { &mib2, &pdu_mib };
static u8_t snmp_num_mibs    = LWIP_ARRAYSIZE(dev_snmp_mibs);


void snmp_main(void)
{
	snmp_set_mibs(dev_snmp_mibs, snmp_num_mibs);
	snmp_init();
}

//INIT_ENV_EXPORT(net_work_thread);
