�}L k �����8v
��u
��(�b��G>��>m�jW�,x���͂'�� �Kz� 5� �����H�f�m��w��{"6���=>Q��!�[�yqx#�|��k5�M�.��ܸ%|m��qI�=d��{I%y7UӖ^��a9'nX\���L�?��pd��F2d�+�$9�}p�sΔO꡽,� %F�Π`�1\X�r2A�Ce�;s|Kre���w�H�ǒ��0M&=&�7�u6pa4�p��^�}1q�,4�V^k���n��UJa���J����'�9�r��X��I����kSbu����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD4,�M	W&�� @���.tBn
�d�^Lw?h��d���F�_�K%v�޻��
j��W1�(��s����}z�gu��́S�o���[�Y��k���Cz��H����O��W�A.��꺱��]<�9��Ʊ|�f��'�]\��c�֫AȢ��ý���5��� ���8��W.�A�����$�@:�J[��BI��'�Y�n�-��	�6�o�TJ'�%�L͞�~@�4m�
��%�P���ULO��A[1eL�&����_j��$DI����7u�������.TK�6���@{��k<;i��6Fa���5������q�1�%h� !f���d�I���NLa&z�UȄ�+��N�۹��ѠC(���G�E��z�N��N&K���6�G�)�����"2Ý�`�L=�m�`��f)7�
<�F�$PqP@.d�ˌ%����WF��չ^e>>��H�N�%0�7���6o{e��/�Bv��9�	o�	��0�Ď�	�<�_NAME_MAX];
	rt_strncpy(uart_name, name, RT_NAME_MAX);

	rt_device_t  serial = rt_device_find(uart_name);  /* ���Ҵ����豸 */
	if (serial) {
		rt_device_open(serial, RT_DEVICE_FLAG_DMA_RX); /* �� DMA ���ռ���ѯ���ͷ�ʽ�򿪴����豸 */
		//rt_device_set_rx_indicate(serial, uart_input); /* ���ý��ջص����� */
		uart_control(serial);
	} else {
		rt_kprintf("find %s failed!\n", uart_name);
		return RT_ERROR;
	}

	return serial;
}





