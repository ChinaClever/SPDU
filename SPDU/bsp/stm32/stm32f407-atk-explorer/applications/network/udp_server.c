�}�   �I��Y���    ��~�b�ϋ��O�}&D�e��<�	2�iM�4Q�d�Ų�6���JC,��nf�L �5�ܝ��a`������`Y��o��U h�S��n����(��=�t��-�&X��Uq�'����B�v
�gq&�u.�b�����4p�����q��h�[��e���y .ɵ�{���Bklq�^C;�L_�X4��e��S�,z�˽ef���G�#:�����@�=.��!)�휁@�>��������#��-����Q����wĚ���C�F5IE�ѳA
Gl��÷�ITb6/b���8��:�kMF�������A�[.�a��Mó�T�y�h��IUi#ʭ�0�)��w���
���[gM��4�E��~Tҽ<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�*����K�m�%W�����p-G:1'ij"�"�<:\@[M�kt
���d��L�'��V��ܺm�� Y�A~̅�Qմ��+	�/��=��ش~����@8k5�M��N�T����»����"�yq1N��
�Xy�1�SE���)�&x/��8pȽ�ܣ�̜��]�!���W2���/P|'���Z�ڐd�S�fE!�eE���ԋ�J@SpT8��>�{"y����B��Bh��K�����=������b�lM/����k9��W[S��p�DM�>��@:*jKsk/�{ z�2e����0�'�!a�m�<�Y�5@�pǀz~h�T�<����Ċ<R[��K�@59���9�ۑ�䈪�B�겣�+ۙ��@���}ٱ���dX7OMa92���0�O�Y4;ZM�p�3/��iq4A?�+��1���X�eaOS�`Ȓ�=|�\&� ��	hc���(�y��X2��Y�R�u�f!��촕�����l�'X���Ozt�?TN XI��T1��bW�x�5���vj��8���H�K|�\3��c2CC&@��0�S�VNSHꅾ�c�E��\���b���l�fd��W���fy��B�p�1׸E��s?q�y��m%��M�	Q��V��o��9s���u`����57Q����fD@�k�DJ���Yt�A}�	PZzY蓿BJ����R��k�<;�p����5������>4��!t�@������6�p@GH�HU�l�ZE#���;��uMct%�qR��<J!ic,���0{)VjyJ�/ɟJ��R(��z)(J�;p����h� h?dj��m״�U�RVQ�K���?�1B[��a�&-P�@�6�GV/ k���2L�
��xχ�0Յ��١T��6�3�������Fv�>Za��d �S����>7����9ԫ����pm6��>�����W0$�H�z�M���
�·	�8.P���W�)�f8l",�ōJ��Keturn bytes_read;
}


int udp_serv_task(void *arg)
{
	int port = 12707;
	int ret, sock = udp_serv_init(port);
	char *buf = udp_ser_buf;

	while(1) {
		ret = udp_serv_recv(sock, buf, UDP_SERV_BUFSZ);
		if(ret > 0) {
			json_analysis(buf);
		}
		msleep(5);
	}
}

void udp_serv_thread(void)
{
	rt_thread_t tid = rt_thread_create("udpserv",udp_serv_task, NULL,2*512,23, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
