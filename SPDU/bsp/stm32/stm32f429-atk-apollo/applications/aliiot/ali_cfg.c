�}r   �(�#�2�K�    ��/�b)��GN��v䉧C{6w���#C ��1༪I&�d���ͷ垵��d�Kf�����X8���1d�c�ޛ��l�7p�h�Rm�I�_#��?a��#��ʑ�1:Z��"����"l��s?�b7�oYh2�4�r��;h�ܜP�f�:��#W��W�aN���R��3�4(Y���k>��`��&�!g�}_cq��8���������Jl[`;Φ��&�<�����.�v�Ǻ�;�y����Ȇ�)%�_,AM�0�Y*�&Ч��W���Ƌ�i�/��A��(��4p"�SW�T�yL�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�Qڳnj�ޠ����a�6�9Oa�X����Zw�-,H��e���7AA+�8˚�!��js6�e��m������I�ONb&Hn
4 ����i26~,�j(qhZP�HO1��)��(2F��p�n꘰lQ��	R�
��� ���z���۷������5�דUc�<a0�G�+��c�a�d���9n`N!��58PwucM�ʾ>�5��E�]!D�b>�֑VF����V�{�O~}*��\���;��Џ�v�9M��"���������B�-�r�r8n�1�(h~��1$���.rO����#�mR��V��!Z�K��-t�meбt�@Q�$���D�l(*��qBA/��gr�'�Z�ƒ�8\�%/9Oyh׈��_�J�1�^��.~E�p�	��>1��Y`���[��>��){�Z?�FU��aش �Ί��
���Ur��O3�_���*b���d�7=�{�w�Db�$:<���7�����c1|;-,h�96a�7<f�3t��e-��h���u l1_R:�XH��ק=N���ć�t�ap#J�t�>bV�b���$\�$���B���x�}�Y�>Nc�}�R��FL*�\��=}<��w/�����oD�	�����uz�E�M�g����!j7;CN<e9�8kB�=����u���
*&\��Ő�L�ۼʼ�� %k�C�z`�9) �F2�9_ٯ��n��-� �'�-��ި]�6J!X%VaS�W�[Di�\�(�{���nX]U����!3Z���2D8�Տ5}� O� ��E��2|Ϧ�b9�V����6�,M{я?�����[�<B@ͻ�/y i-'q�B<LG�Ԩ;�=Z����|<U����L ��r����Μ���mn	��gA���LNT�(�:�c҂T�U���dq�$v ���?�Fn������C�O*�ȱ��$�<�s�g�Z3 ��qm�VjZC\�	Ѝ�-��,9�m@'�Ƹ��p�K���uH��B��	A�+.��!����g+�I�p�r,��izeof(ali->dev_secret), NULL);

	sprintf(key, "ali_pro_secret_%d", id);
	ef_get_env_blob(key, ali->pro_secret, sizeof(ali->pro_secret), NULL);
}


sAli *ali_cfg_get(int id)
{
	static sAlis *cfg = nullptr;
	if(!cfg) {
		cfg = malloc(sizeof(sAlis));
		memset(cfg, 0, sizeof(sAlis));

		int i;
		for(i=0; i<=DEV_NUM; ++i) {
			sAli *ali = &(cfg->ali[i]);
			ali->id = i;
			ali->iot_devid = -1;
			ali_env_read(ali);
		}
	}

	return &(cfg->ali[id]);
}

