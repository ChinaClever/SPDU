�}R �  ��I3�(�6���u
��a�b��F^��}d��-�L����-�ݪ� 5&Ǚ#��v-�6DG��v,���xDM�����Jz�����ے���'��.:�p��=��a�+�7��,�'3��<[%e�m*��D���ѕ�N���E�L���m[@:�ރIF܃���UH- e�	Ya) ��t�JL	�G�ĔX�]�@	/� ������#X��-�s�c�7b<"f>z�kz��{T�~�x�c���&�1>�J5'���۳� #�E�C3�+(�	����m�ncz=8=��k���F8!vz�I�#�Y�O������5<�6��T��·�c;C沁�􈢜���V�J��Gu|���,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l9��y��+����}'
��=�)�nql����X'�I�����h��Zw{���������yn)�Zzy�����R"��0&_���mXQxs�.w�o�6��g(���<��Ma�]@/���)��h�Dg��!g�$sJ"o��G^)��t�]]������6�CM:)�(����~g�u[���蓀��X%����t����@8�|���8_�H��;f*�ó�8��_$)�Vd����B��B�W���
~��F�Q�Ko�l*a�SH���$?ݰ*�.�w����<x�#ߑ�p�<�̴1C�Ǒ@ch�� �����eI3PZ�N<��R���tiȸԫ�hT�F����E;A��&&������킾{�G�c9�����'~�Y��0yG裂�D��^�F��/����SJE�d�oq��	�n!uߌG�krmZ\~�A�{�8l��9��>�����*�{4����E�l<��vD��R=0T-/$N���l�(O�q�����S�/�u ���ҝ��
-�4�{N�4�kni�Pg[{��~c��yД�(����$���t�!�J���g�*y�{3�R�e��ʸ82�F��V��sb#u�����oB�G��{��c���B��U��EO���g�ք(�K>��J�o��:�XA���ΰ�izj���L֩Z���s�U�ZcYi��R&�ə��!'���&�	t�����BMG�R߯���s<؛���.�3�� ʞ5;6��lB��ޑ���>�UV"G>R�4�~
����Va�)�i�N�����]$_L��T��IUM;7:x�)	i���Ԡ+��Ux����<4Tw4�T�2��F%άڶ�  R� 9:M(Z��#4P{L?K��=��Q[�0��ǡ}ey���P��~)��!�b�v�)��I�!���k�	Z˾j'�Ԁǥ:�u�v$��$΂(�j;b�Z���C�l�	zax��`���a�O�c+'��8[\�z� J1�QU�SUt err)
{
	printf("mail (%p) sent with results: 0x%02x, 0x%04x, 0x%08x\n", arg,
			smtp_result, srv_err, err);
}

static void email_smtp_send(void)
{
	smtp_set_server_addr("mymailserver.org");
	// set both username and password as NULL if no auth needed
	smtp_set_auth("username", "password");
	smtp_send_mail("sender", "recipient", "subject", "body", email_smtp_result_fn, NULL);
}
