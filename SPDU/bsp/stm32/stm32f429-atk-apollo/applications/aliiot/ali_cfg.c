�}� [  ��� ���VM��u
��/�b)��GN��v䉧C{6w���#C ��1༪I&�d���ͷ垵��d�Kf�����X8���1d�c�ޛ��l�7p�h�Rm�I�_#��?a��#��ʑ�1:Z��"����"l��s?�b7�oYh2�4�r��;h�ܜP�f�:��#W��W�aN���R��3�4(Y���k>��`��&�!g�}_cq��8���������Jl[`;Φ��&�<�����.�v�Ǻ�;�y����Ȇ�)%�_,AM�0�Y*�&Ч��W���Ƌ�i�/��A��(��4p"�SW�T�yL�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�Qڳnj�ޠ����a�6�9Oa�X����Zw�-,H��e���7AA+�8˚�!��js6�e��m������I�ONb&Hn
4 ����i26~,�j(qhZP�HO1��)��(2F��p�n꘰lQ��	R�
��� ���z���۷������5�דUc�<a0�G�+��c�a�d���9n`N!��58PwucM�ʾ>�5��E�]!D�b>�֑VF����V�{�O~}*��\���;��Џ�v�9M��"���������B�-�r�r8n�1�(N0�ps���}rT�Ʉ�|�O����._�L��??�F��e�[O�R���d�Pl�)QD(ݬ!r�+�D��>�]G�!)U+:#����;���E��.~E�p�V	��B��g`���[��>��){�Z?�FU��aش>�Ί��
���Uݘ?-|O3�_���*b/�(�d�7$�{�w�Db�$:��������R�'|;-,h�9oa�7z�3t��[-���@i��u l02&kč�M*j�;����S:������mv������rO7J�؈�Z�e�y��uL'	��sf�[&X�%j�s��V��k@��4�5�[�_"�F���(�/8x^'Ǳ!�Jz:���	�f�
���]�M�8]e�m.���@����9c�fWU�k&X�����|<���k`�j�L>mH]�� ��b���}B�3>�]��ǁL���ݥ��ĵao+m���*B!�����[��8���{�3W���a�/$��S� ��in���;-]����=�r��'���<$?�O��b�I�m 5!�����!-��b��$�d��� -&k�
����D�I�V�'y� ��V#0�χ��SQ�����'p�0@�k�g&/�;���2�R�RP|H�԰��,��X�j�.�.A�eL����R�}�C�z�n�i-'"�� ��U3#DQ����O�ʫ�\>ɝ{(����!">f�C��H[�#���]*�XBuxGd�X��d�Bq�.���>dev_secret), NULL);

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


void ali_cfg_set(int id)
{

}
