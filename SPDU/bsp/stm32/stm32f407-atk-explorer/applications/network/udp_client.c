�}� u  ��͞t�Y�    ��m�b�ω��O�|&��e�Qݵ9�/Q�w03
��|�������͸;��#2��7C��dK1c�`����{2�i}�a��5��w��y�[Z-c�eRg�=�v%
 ��I�yƭO�8�*���X1o�̕x��;?{=�;�����{g��[r���M
���m ��)ٳ��%���D���Z�!�f\lYq��n�d'�lb�/�'��ƪ�
�+/�n��A1d$CU;��hp=̉���jc�lO����a��og�^�Co|�Q�/S�nd��vY��S��e(�R�=���
�x��@]� #
�L�mpN�N����})�
���,[�͐�хʆ�t+#j=/������Z��K�V����E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�38���j���������=���Y��F�+|;B��8� ~�J��P�o�v?7Dh=�G���g�W��m���׳J�m��u͇�	��G��̯�W�aE�l$ﳩ�D�?jI��	�b=�L�{�D�u_P��x�׫7����Qx���4d�VAG�*��@��(9r�p��Ò�א|��ؾTf��(�ֿ e��Z��'�9=�)��rO��]�a�-H9�EOK�!�R�`	�d � Dt��z�~ޡ]��/��NR.6����6���1�K��\�l1����<E��JkcO�X�2��qy#}��S(~م�q!�[��F}���=M�������+,��Tf��xj�ƽa��
*&S`%��Hu®�C��r/'Ƣ�}�k@\0���t[�6��P�jg_���}����ߚϡ)�Jꄈi<�8���_Ts8i.`����>o�j�BB����.:��X�H�lC���~QΟ��]�CT��](q�Ur,b+g)�(,���Tv�t sockaddr_in *server_addr = &gUdpClientserver_addr;

	if(sock >= 0) {
		/* �������ݵ�����Զ�� */
		ret = sendto(sock, send_data, strlen(send_data), 0, (struct sockaddr *)server_addr, sizeof(struct sockaddr));
		msleep(5); /* �߳�����һ��ʱ�� */
	} else {
		ret = false;
	}

	return ret;
}

/* �ر�socket */
void udp_client_close(void)
{
	int sock = gUdpClientSock;
	if(sock >= 0) {
		closesocket(sock);
		gUdpClientSock = -1;
	}
}
