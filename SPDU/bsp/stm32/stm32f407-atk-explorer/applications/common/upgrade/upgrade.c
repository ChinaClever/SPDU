�}� �  �`T�&�T��u
��F�b��G>έ�*ds8�L��VX#!si,{*п��W{x���<>z�H>���G��.�TB�K�Y�=���=*WzONP�xGq6���}��>Hb����H��6
Y	���Y��ه!a�+З��˽D�r��*�U�W��LI���T���9N��8͆���B��|��|��>�i�7�3�V�	��y�MA�c@�R��[ty-�!f�l]F�3�H9�����	0��=x�y(�Erg��e����1��� C ��HH��|B��A������[����?L�<3�-�ߐ8�~�d�BD4������8�����{��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�4��s=p��ziO4���B��_�$Ęi�>�.�l�5:~"�u� �� ��H�b��e`K�/
��������#���2:�{nGVrW��<�e�s~(QG2C�`]�(�(X�Q�Y�-\b�% <r��	h��+ՔVi�?�n��Ĉ��^h�:3�����}���ٗ�G��{��f�;���q�E�:i|��ET}c�tT*7�2�0D��w�ՠ�F��l����R��W�d6px�����%�Fb`�H's��[185Ց#Q�p�}e|�n�[?h�Q�E�D�~ �����@�6gl�TQ�A����K�i�h���^�����`<�9ӧ��㖴����h􁰋z��T��7��w��>�+���A<���K���ì=H�j���G�:���߷-;��i�hx�1l�9Sٝ@.00���~_�2��|[Y�>��ۏ�a��q��A���אM6��۾�e/�y��ף�@.�-�i��k|���{R!H�?��rH�����U 
�L��read.rbl:1180", ip);
			http_ota_fw_download(url);
		}
		msleep(1);
	}
}

int up_serv_thread(void)
{
	rt_thread_t tid = rt_thread_create("upgrade",up_serv_task, NULL,1024,2, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);

	return 0;
}

INIT_ENV_EXPORT(up_serv_thread);
