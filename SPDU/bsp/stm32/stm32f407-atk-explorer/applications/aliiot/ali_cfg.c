�}�   �%1/BA�`��u
���b)��GNRO���A�ʡ�K)�����Y�������$���t2�/WW�z��3tj��y��վ����A
]vf�w���x��W����e;/G�pQ �o7��<��7�Ot�� ���Y��AZ�O�gg0������,���QO�<�a�^�(Bt���Ly�J��L7�y��E���>�Tc���S)Qc��}@j����F�Oʺ��3�$������H\�w҄(��h�fSA2v���oTH�Y��1s&�\�?�B�wK<�4��%������i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�*���%*i���>�����|{��Ze��>��!�KqQ�;p(h�$�����P�Q:Zݔ���A�;PP"?�E��������1����6�G��T����-6�;�N��T^���ʍ
�-����e�����xB� ��5+��{,ZZ}"b����=�E*	ܻ�*��fB:R;1�B�za�_\�'c���|0!	V�4f�^�>tS�B$���R��}� -�S��ޥK�����̿5kc2Vr���+v/�*�f�k] ���7 �69�o"rT�M�i�+� N��Ruc�i�H}F���~f���,�"BjV1C{s���#��1�7ͭ�1��Y�p�8�Mw��,��`�\�{	�W��K*����5�)?�m��L9d+���|u��h^�}�3��Ze7Y��3T �!�pN�ʮ����9eS�<#�e�*�=~�Kr�r��{H_��{@8�òZ�c���f�k���&�����Q�s���hjdV�I����R�zi'����"Pf_get_env_blob("ali_key", ali->key, sizeof(ali->key), NULL);
		ef_get_env_blob("ali_secret", ali->secret, sizeof(ali->secret), NULL);
	} else { // ��ȡʧ�ܣ��ָ�Ĭ��ֵ
		ali_env_default(ali);
	}
}


struct sAli *ali_cfg_get(void)
{
	struct sAli *cfg = &gAliCfg;
	if(!strlen(cfg->name)) {
		ali_env_read(cfg);
	}

	return cfg;
}


void ali_cfg_set(void)
{
	struct sAli *cfg = &gAliCfg;
	ali_env_write(cfg);
}
