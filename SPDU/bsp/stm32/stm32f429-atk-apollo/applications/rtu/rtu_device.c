�}   �%1/BA�`    ��8�b���GNʇ�O�jN���x��,�Q�a�`O�BX=GB8�|�Ws�����F�t�# &S���V�%���8���K�7�1�%�?��@�^=��U�J$wZao�*�,�t��r1e�M�L�%-_�S�*_L2]�H��oTP���C��8�ĺ[�b,��b�kk7UAzVgq�f�!�cL�C[��=�J HR���ADf�p�0�d�~�e�b��o��v��gew����V�{*֪d���(Ph<+Z^� X �\#���͈�&w�_���A~(t)��S�d���o��5CL
�/��
�P"/)�X�v=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD0Y�j�G�/["��/7��j���HQ�R�������+=�|���m��#4i������J����B���v�YK.��X���ۓ��S��б��SG�b�p�d��j(����-=��;�$I�W���a!曜&���L@���R1����OV)7�"Vh�=v��Y�0���1���j��� .�9
�{S�����zo9a֜�es�!�!x��2h�9������C8�'~M�c$��%�UO�	V�skM�^��j;\uu<�9����F��ϵ��Y�9�m��}Q�b���c"�GO��XL
~\��|8�3���VY�챃F �BPOU��\ ��6�A�aHPXJ2��lw��d]y�A�wÎ��Z�K���Yb
��,�񓶂[��I������)����p_�,u��t9��T�ol{�?5WCI57�ﴏ��myr����ˋ��a�{��aB�>�Q���*�_ 0.L��Fl�&5��&����ۋ�#کV�iJ��݀�= �����������8 ��zg8�,ŕ���6q�[�Y�[�|ң�E��'M�G�B�|��6v�}���>6|}��l�&���U��e�dC:�%�xA.�L�.�ń.B�ŀ���g�	�ibRc���*Wz��P�\�M`�>����l|{��
�������='
��(yܖ����y�O�l����aP�FK����7F��0�{���.�x�"��A:uF�eNd��`B�OW2�����<8���SZAA��Z���]�Q��h�o���,��6j�A܈����6혱0���*�i�B���C�?��Pl�����ER4��+�$|�h;��L�W�V��4WN,4*	Fu���dq��߲���ۊG�6�(.��vN�,��v��jϒ+��hc:Fq�A?v�	�b�n~�� �u�.�(���O���:�yS8�����v�!��}��<'
;��v��fB���ڟ�H���l4G)��� wށTBT�h�<~ma�9���1/�t�h!+~t��ͳIX���CZg-����|>{d�����w��|��x����f�Ҁ���MY�^ٴ�pO�D+50u�h��i�FdL�0������D<⣹
�8�D��7�
���S|o�J�Ե�� '5�������z�I��\H��U�#��Q�e���by���@�P�z�s���&Y��[h'xS�X4V���;dv>2�:G�b��V8�M_�&�0���dŝp�J�l�_'�
U<TD��e��7�-'��|Ar�qiY剰��e\�[aR�+���x2lI���_u�IMY��.*�<w#m��7��+X���mM2�v�p2a���(ǎ�����S�3�?��_b�ۚ3R ��fXJ�����1r������*;[<~�1qM�(=d�����8�D��j蚊̈=r�����M�<J�ti�`�3�WV�G琀�9��)��f�@[���ت�Ι"z�;���h�(3�3�e��6�X); /* �� DMA ���ռ���ѯ���ͷ�ʽ�򿪴����豸 */
		//rt_device_set_rx_indicate(serial, rtu_input); /* ���ý��ջص����� */
		rtu_control(serial);
	} else {
		rt_kprintf("find %s failed!\n", rtu_name);
		return NULL;
	}

	return serial;
}





