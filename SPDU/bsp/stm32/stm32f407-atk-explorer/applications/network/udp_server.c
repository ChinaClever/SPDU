�} 
 �Ik
�lt����u
��~�b�ϋ��O�}&D�e��<�	2�iM�4Q�d�Ų�6���JC,��nf�L �5�ܝ��a`������`Y��o��U h�S��n����(��=�t��-�&X��Uq�'����B�v
�gq&�u.�b�����4p�����q��h�[��e���y .ɵ�{���Bklq�^C;�L_�X4��e��S�,z�˽ef���G�#:�����@�=.��!)�휁@�>��������#��-����Q����wĚ���C�F5IE�ѳA
Gl��÷�ITb6/b���8��:�kMF�������A�[.�a��Mó�T�y�h��IUi#ʭ�0�)��w���
���[gM��4�E��~Tҽ<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�*����K�m�%W�����p-G:1'ij"�"�<:\@[M�kt
���d��L�'��V��ܺm�� Y�A~̅�Qմ��+	�/��=��ش~����@8k5�M��N�T����»����"�yq1N��
�Xy�1�SE���)�&x/��8pȽ�ܣ�̜��]�!���W2���/P|'���Z�ڐd�S�fE!�eE���ԋ�J@SpT8��>�{"y����B��Bh��K�����=������b�lM/����k9��W[S��p�DM�>��@:*jKsk/�{ z�2e����0�'�!<�@��@�(�
е([h��/U0����̂n]^E��I�:A/9���PA)��ۯ��ڟŸ���R����C�ꃋmަ��o~'qaI5����+��N!_w�c�~%�����A?�+��(���6[�!ea�OS�`Ȓ:|;��L�� ,��(hc���(�`��X���x�R�u4aq����U1�����l(ʹ�О�6r��Z3O�l#�@:0�ִZ��\�G�ڕGz�G��_W�ܞ����W��@��.���A�lCO����Tixa�oQbwtly���~1=H�ON�y�"���cr��s��@�_�I��e >��(��=M��I��m6�`?^Xr��� !�5��8���$�����<��B3��0�<byɋ>mmF:�O��{�^%d�3�邧������_��d{�J^���BRjxD��Y1��4g��[e�	�`r��=.�/�%xV��M����i�����@����`)�c�r(�\Ͷ j�L���lyQ�|�0;ш���r�C�m���W�%U��@�P�tF��}\41��v�~t%ٱ<~K�=-ǐx�ߧu�C�z����8��E�@ٻ��L����{��~)Z�d�F��_IPJ|N����6h�1KL�N@�5V�^iM�HI�ђU�x� ������#�h��|rb��CV/�9���y��8*�I��?N4���)<
	return bytes_read;
}


void udp_serv_task(void *arg)
{
	int port = 2707;
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
	rt_thread_t tid = rt_thread_create("net_serv",udp_serv_task, NULL,2*512,21, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
