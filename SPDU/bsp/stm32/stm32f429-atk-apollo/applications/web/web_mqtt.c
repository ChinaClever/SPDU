�}�   �N�=�-    ���b)�w�GN��S��VxP�ZʁS��{����}�Eo%7��J<�JK�,����U�M/{�w�ϧ��D�~�&jb��z[H	?PѺ��A��	"���M3b�^�W�U%\=�>���l����[4	�r4�������y�F��G-�ʍ�������D�I9'D����:��`�㱩��BD2����Ot�~�<�z!�����p5f��W��L�	RfI����x�X�Nף�A|�E����:����
�Klq�^&9q�*�{�������8�>�n�k�	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�Qڳnj�ޠ�a?b��{��Җ������N&i��)Hv�7%�=h���y[��B�D�m������f��{ǽ�v��)�ϧ^no�._�����Z,o�%�.��(2F��w�5���
�h�K�C���|N���j�����������"���w�f?d�V�}��/�w�c���i{~7��N$vynKі�j�m���^H,D�ak�����W��r�&�1W�@���?�����)�P"�m�<����뮎���g�'�La
�w�Qe}��c>�Γ4=B�궽|����5�I��gm�/D��U�vm<�����A #��^AG2ͷ+1�:�Z�ҝ(�wku�Lb���� � ��^��/~�p�@�|��JXlɥ�xY������{�Z��FU�a-C�����=���!R���Z8��YZվ!"�«5�dTO�^�v����(�z1�V��%���|;�.h���+�=Z�3t�%d!.�e���N9��lD*|`�2���2�o����.��Ѕ�ӯ�њYg,�	�˷5�k�[�-o
��ie�� ����ң���E��-۶^�P:$�e�K����t0����VZ��1CE�>�0x���";p��82�Z�*
O�IS4~��~���yΙ��,�^�c������xw��oxh�߇�,f��i�1��9 ,�ڳ�饽]��h���q�<]h�C�U47�K)��ِ�S�l�m:$+���MyQn�>�n������<]?s���3QJ�Ķ4P��:B�e0[{++=[��)_�(h%"�f)��"��rk
�f�\wFvu����;�Q��Ǜ ��<A��U ��7S3M� zK|�z�;���&2����9�=M>e$ZEO��u�m����*#:��\�@o)3�^�1� �<��0�U'0GJ�6QOs��7�T`{+��&PAV�Ouԫ;_��!��o(�HX��)�����X���`v<��`�@�a�<��p2���ӹ'��l��?���!�Ҽ��
AMA����!|*�����u���6��@^]^����N
��]	�ۈ�H�h{�<���	>nY!����D��vo�vU�	P��Zs�$F&d<���p�Ԅ����,��V¬��:Xt���gqXe��?�Er���6P'f#�����B�e�4HL��cyY��Ű.�/���R��
xH��J�^">��TE�v��8��3�>�*�M�;����8OW8�8f�G �X�IP�L<�@Α;� ؗp�~��
KECq,{��9��(�䯯��8g�61�ʱe
���d>�]mZٵH���W�&�YsDk�3��Tv�� j�4#�E���K7pCrN���]����)p�h*/���N�w�HE�+Z��g���⺡�΂�Z��ߛ�į��V��]�r�Xndp� ͂��Ǘ��_���*��*��c>���;���T����a��vl�H�S:C�΂��F�t}�jX��X�ݺ�Hw���ƺwaGΫ��e HlD$9���ő������ReW*є��A�\\��j][�'��S�6�K^���2�r,0p��.S���������6t}�1ǰ#�%1�O�WMx\\&�\9��/{�_Z�V�����[�H ���pVaVC=����Uڏ��l������p�C���E�VY����4�����➭�H
��������
	K��X�:�Ұe]�,��'k
8�^[�
��{�=�a߿�/� v���ߗ�[��޹獥��H�QqI��i��ru��)�Μ�j{�_�>`!-�O}S����������f3-��
��#i��Fd�[fX[���a�_PՒ{5����*N)�Bͪ�����R'��`�z�_1>���[��&f�1N3��siYK��{u��/a�a�m���g�e�9�����ŕ�PU����0�ӣ{@���a��O:�g|��hȌ���p��3�]�UTl>pR^&��fi"��hW����TP\��g�κ�슋C{*��IX���in = atoi(retain);
	sprintf(t->sub_topic, sub_topic);
	t->sub_qos = atoi(sub_qos);
	t->mdelay = atoi(mdelay_str);
	mqtt_cfg_set();

	static const char* status = "en=%d";
	webnet_session_printf(session, status, t->en);
}


void web_mqtt(void)
{
	webnet_cgi_register("getMqtts", web_mqtt_get);
	webnet_cgi_register("setMqtts", web_mqtt_set);
}
