�}�   �(�#�2�K���u
��\�b���G>�>>r�����͑mq��9�%��ei�Qp�1<ߞcm�m�� }���c�5<���\��;5��<�ʤt�vʣ%���sm6-��,V>}�˶i'��R^ \Y�D�>e�z,�e\s*��O���3�l��S��%�P-ǚ�Ɠ]��q���t=��lH�s�#X~h����M !�Ӧ��\׉�Cn�F7�F,߆���{���0�
P��ǇZ�}ڝN��ȖJNGd�&�E�o6d7�I��7�󛉂�(�|o[�� j�M�]�_�7��h��5vO��x�����C��;���{�jp�n���hd!(�i?�i~
Z}M�B?6C�9@M�*u��X��y��ٽ���e�rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���All = "false";
		if(cfg->isAtAll) isAtAll = "true";
		sprintf(text, fmt, cfg->key, data, cfg->mobile, isAtAll);
		dt_post(cfg->webhook, text);
	}
}
