�}= ~  ��;�ћ��g��u
���b9��N~{n�$ח7�H�wbw0H�t�٣����+\�k &e�AE�;.�Y�{��ð�?�`J����6��F�*2�r3[O�����(`kuhB.�J�1+����1�j�hdڄy��ȷP(GAV	��n�0�G�o���-��|�5�jMv:���>J�3�@w ����E9���=�X�B����W�<rt���Z)��z��U������{��?R-�'�m2:N���Ѵ��f0)*1:ϟ)�"�\���XY��Bz�,(qnB�U�B��J�ꠏH=Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l'��a�A7�*3/�x�j8������[7+�Ӱ�<Q��y�[��Х��S(E�i �9+FD7k@��������\��G{w�DP���O��ͯ���+�����5���Yeŵ���W9H�\���Ch��/����~^��{~����?��؎�;�n��{���3�C�L噫
f��gWnC��� P�M��
�ٞUi�I�,d�"�vV�k�4��F�BE�L����^Y��g�*�6���Z�8%36p����gۯX�;��w����~�����s�̞
�dP�����W������}zFm�Ljۏ?:�o��ȒӃ
�pn���Ȑ�*�8��>]C��!�@�ֵ ���(���@����ήf�,������#�!��&��o�ɐ�q5��|2�I+��&�1;Y�Kac�_�����Q���;�u�)��6'vv1뛟s�Z��K� HĎV��{0�+-��GD1\;��$+]�v��$Oe�8��+����p�v�C		cfg = malloc(sizeof(sMqtt));
		memset(cfg, 0, sizeof(sMqtt));
		mqtt_cfg_init(cfg);
	}

	return cfg;
}

int mqtt_cfg_mdelay(void)
{
	sMqtt *cfg = mqtt_cfg_get();
	if(cfg->mdelay < 15) {
		cfg->mdelay = 15;
	}
	return cfg->mdelay;
}

void mqtt_cfg_set(void)
{

}
