�}�   ���� �\���u
���b�ϛ�G>�;�l�e����9����"gw�W|�`�ĸ�~V�8�Nb7�I�����q4�P�i� �t��<�Vj�p̦�ߍh�l�)�y���xn�8t�2 �SNR�/ {�l�w�{���}U4�i���̱v���^ �5�`�g�<_;%�(>W���B&�����!7?��#�X�r�d�,O���� (M-84���usK�.r�6`��ؔZ�dN��wr}��M�G��.�H2������D��{���v���w�~H +���aM�3}��|&��5v$n�Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���oid_arr, &pdu_mib_root.node);

static const struct snmp_mib *dev_snmp_mibs[] = { &mib2, &pdu_mib };
static u8_t snmp_num_mibs    = LWIP_ARRAYSIZE(dev_snmp_mibs);


void snmp_main(void)
{
	snmp_set_mibs(dev_snmp_mibs, snmp_num_mibs);
	snmp_init();
}

