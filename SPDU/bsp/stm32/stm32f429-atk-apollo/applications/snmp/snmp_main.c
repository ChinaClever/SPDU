�}# s  �ꍸ&W]���u
�� �b!χ��?�=��d�-�/���wۯ&B��v�i־չ=,�uy<��`J��B��s����� �}�w2�9q4ɇ5ߟ�d��\=������1s��݌/,���"57*T	-��
wF-�z-�M�>t������ݤ�����a���Hw�����F��J,Frm�����= ���>Bq�|��ڠ}���4��F�ͻ�GG�*U^=�[b��rJ1�mS��?D�'e!���%Dॼ_4��͐+�an���2�q�0�밞yn�k�	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���t u32_t  pdu_mib_base_oid_arr[] = { 1, 3, 6, 1, 4, 1,30966,20};
static const struct snmp_mib pdu_mib = SNMP_MIB_CREATE(pdu_mib_base_oid_arr, &pdu_mib_root.node);

static const struct snmp_mib *dev_snmp_mibs[] = { &mib2, &pdu_mib };
static u8_t snmp_num_mibs    = LWIP_ARRAYSIZE(dev_snmp_mibs);


void snmp_main(void)
{
	snmp_set_mibs(dev_snmp_mibs, snmp_num_mibs);
	snmp_init();
}

