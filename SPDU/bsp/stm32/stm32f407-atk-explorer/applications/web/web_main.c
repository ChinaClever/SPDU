�}0 "  �}���M&7���u
��R�b�χ�FN�=&���ֵ���q�CQ�������-� �ϼ�&X�e�㧑��Iq���:��c^��р�s����̀f�z?�&[�ٯ[G���U��_�a<������L; (��P�\�����|"b�x1#��ٵ����P���1�u�	�Ӂ$M��Ԣ-�cz��^���(~�%Z8��q��MLi����	EQ�u����o��d�ed$�Dߑ�B��x��n,A_����0����E!���OFX�-���v6L;�l����a�L�g��ɦS5�R�:˃���ț��`���Ȁ�$�M�*����@+s�"Aÿ�<"9��L�A�n���ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l+z�Ođ���;)�PІ�����ȓG�x�,�[̛�E��è7�8)�堧Tc�ֶ��� R).NzzL�%��d:@X�/]��n�`ըt�O�J���5B
�M`sM��������� �3c!����҄��`
6+A�y�p�~@�E��%�Ɏ��*Dso�I��d�q���H�E%Oa�&rG���.1B4��0�+>��̈́�&�;p7Z�e�
��}0����	w��ڗ_�=^��@h�'z��f%��(\O����bi�u�F�h�lJY�9`��Zm;�J�ԆB? ����.�Rg��m�J��/���q����
��)���<�[�^�M,�:�	�zTe�˅�{��1B�{.�i�1�#mA좹[����F�������HY�|OGYI3�eC��q)G����[=��2�\���h�0+z$�����T]p�W�����<x���ڵ2��,�8+�`������O��iQ~F�����d�רg\̔�admin:admin
}

void web_main(void)
{
	web_auth_init();
	web_output_sw();
	web_timer_sw();
	web_seq_timer();

	web_modbus();
	web_network();
	web_mqtt();
	web_aliiot();
	web_user();
	web_ip_addr();
	web_ntp_time();

	webnet_cgi_register("getVersion", web_dev_version);
	webnet_cgi_register("reset", web_dev_reset);

	webnet_init();
}


