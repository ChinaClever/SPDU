/*
 * snmp_mib_pdu.c
 *
 *  Created on: 2019��7��3��
 *      Author: luozhiyong
 */
#include "lwip/snmp.h"
#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "lwip/apps/snmp_mib2.h"
#include "lwip/apps/snmp_scalar.h"

static s16_t snmp_get_value(const struct snmp_scalar_array_node_def *node, void *value)
{
  u32_t *uint_ptr = (u32_t *)value;
  u32_t id = node->oid;

  //*uint_ptr = getSwStatus(id-1);

  return sizeof(*uint_ptr);
}

static snmp_err_t snmp_set_test(const struct snmp_scalar_array_node_def *node, u16_t len, void *value)
{
  snmp_err_t ret = SNMP_ERR_WRONGVALUE;
  LWIP_UNUSED_ARG(len);

  if (node->oid < 30) {
      ret = SNMP_ERR_NOERROR;
  }

  return ret;
}

static snmp_err_t snmp_set_value(const struct snmp_scalar_array_node_def *node, u16_t len, void *value)
{
  LWIP_UNUSED_ARG(len);

  u32_t id = node->oid;
  s32_t *sint_ptr = (s32_t *)value;
  //sw_pin_write(id-1, *sint_ptr);

  return SNMP_ERR_NOERROR;
}


static const struct snmp_scalar_array_node_def pdu_nodes[] = {
  { 1, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 2, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 3, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 4, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 5, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 6, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 8, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  { 9, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
  {10, SNMP_ASN1_TYPE_INTEGER, SNMP_NODE_INSTANCE_READ_WRITE},
};

const struct snmp_scalar_array_node pdu_mib_snmp_root = SNMP_SCALAR_CREATE_ARRAY_NODE(1, pdu_nodes, snmp_get_value, snmp_set_test, snmp_set_value);


