�}� �  ���N�9[x���u
���b9��N~{n�$ח7�H�wbw0H�t�٣����+\�k &e�AE�;.�Y�{��ð�?�`J����6��F�*2�r3[O�����(`kuhB.�J�1+����1�j�hdڄy��ȷP(GAV	��n�0�G�o���-��|�5�jMv:���>J�3�@w ����E9���=�X�B����W�<rt���Z)��z��U������{��?R-�'�m2:N���Ѵ��f0)*1:ϟ)�"�\���XY��Bz�,(qnB�U�B��J�ꠏH=Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�&5��`'�L���UT��/���ԅ��;�3$
�Cݷsr��������E�/W,@p�&�y  m�b�{�]<e7���H�d�:˥�(d����cVSA��*u 0�L��絋C�m.� �B*�����C0=W1����N�=�:�|R\��*Wz��V��u�u���n��T�����ð/A.��:Oۑ����k���k锤�Qz� 
�������P���/�,��h�=�ϋ>D	z�m 1���tZ3�fg�����!��ccR����WsP�zkN�X�Rr�]��}A��l���|��ՙ����!���`����n�V���C��qF��sWj����z�<lX��>�:ix�^+�l�BF�i
W�M��I3B_.}cf������z���̏����F��#�]?|ɋ����:�;�F�v] B\�Þg��?��R��N"EB��t`�@<���Z �Q;ާh�^���y�=w�s��jZn�.|��,��w�C�5l���X	cfg = malloc(sizeof(sMqtt));
		memset(cfg, 0, sizeof(sMqtt));
		mqtt_cfg_init(cfg);
	}

	return cfg;
}

int mqtt_cfg_mdelay(void)
{
	sMqtt *cfg = mqtt_cfg_get();
	if(cfg->mdelay < 5) {
		cfg->mdelay = 5;
	}
	return cfg->mdelay;
}

void mqtt_cfg_set(void)
{

}
