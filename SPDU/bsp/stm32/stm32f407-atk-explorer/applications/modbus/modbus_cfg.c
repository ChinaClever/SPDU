�}c �  ���$$�KU��u
���b1ϗ�G>�=F�١RK36F0Y�L�����]a�"��ζϰe|Pz}K1s��Ziu?{�s�̟];ȮsO� �`�3�����š�22Æ�H�n�2��?�6X��m��!��c�M��@�{:z������jw�Y�j����$ ꓡH�;k%�*V��S�ڸb�(�/����I�e7G=����7�'E�7b.��K_>4R�=�����]}�Ky�+5�����s&��2T#PXlWG������������B�����2��*[yn�k�	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���(mb->port), sizeof(mb->port), NULL);
	} else { // ��ȡʧ�ܣ��ָ�Ĭ��ֵ
		mb_env_default(mb);
	}
}


sMdCfg *mb_cfg_get(void)
{
	static sMdCfg *mb = nullptr;
	if(!mb) {
		mb = malloc(sizeof(sMdCfg));
		memset(mb, 0, sizeof(sMdCfg));
		mb_env_read(mb);
	}
	return mb;
}


void mb_cfg_set(sMdCfg *t)
{
	struct sMdCfg *mb = mb_cfg_get();
	mb->en = t->en;
	mb->port = t->port;
	mb_env_write(mb);
}

