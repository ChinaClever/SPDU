�}� 
  $�Cf�ai�    ���b)χ�GN�=&����)��I|�A�+'��r,̤���܉���0E������K��n�H�`���v��~S����ፋ��L��ڲ2�	�;{�]��.�Yf�c�5L��^��6S�������ti�$�*G��1�����@��ط��L�.mT���;y��)Xǉ���#��H�e{��Z���&rof�ʑ%N��a�q30  N��u�G-2�l�"2�Q�k�y<3�����Q�Z=z���?��L� �	(�;K�>I��[=N���ԓ�9���	�,�@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD#�X���U��!�/Rҥe�����,�{F_d���a�*��hC� ۂ�Z�(�`�ł��������ߐ�Bg��^&x�pF'���lKdg����'��sFM񌞰ǌ	d9n�J��C�aJH����8l�n`0��=Ӳ�R�8Ԯ����S}vK��e��\��7�[�m��S�����y?�y�x&YE(J��*E���=��"�$Fki�}QfAe"�2�C	�1�e���|�k�O��ۺ����OR�&xľ%W�+{%��ʸk?b*bס'uQNͿ��dR�t^�s�^߈���iL��ɀ̍��Qn:�SX��P��-{pt���@`>���`�¢��H��D���Y+��t��zښ�x���^ECR��O[�; `UM<��2���y�߀y�@�m3ӄi�t'�����9��iy/�P���_T2�@�<�Ns�[�q2�N�"˴��F���N�Z�]��ef˙D�
��	�,��w���X�cszJ	sprintf(t->secret, secret_str);
	ali_cfg_set();

	static const char* status = "en=%d&name=%s&key=%s&secret=%s";
	webnet_session_printf(session, status, t->en, t->name, t->key, t->secret);
}


void web_aliiot(void)
{
	webnet_cgi_register("getAliIot", web_aliiot_get);
	webnet_cgi_register("setAliIot", web_aliiot_set);
}

