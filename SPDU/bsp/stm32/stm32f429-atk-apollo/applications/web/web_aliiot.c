�}� ;  � �fis@?    ��(�b)��GN�of�l+��*,0�HYO�?P1���ytnX�ƦϠD�t�E�#O>�m�[$O�u�r셙5SN��Nm��������w��+�)�bK�=�w?=�-�5�
����:u��n)B��v�I�r:���V�D�����y��r��I��y�`7z&LE.m��R�;mJy�MÁ�}��s��>�u:�O��=N����ȱyZ	qO�.��u!×��FJI�����8m�����F����ZP���ݶ�gv��k�9"��͛1~(b���D�����VN!�rd�ӣ���o�u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD��=N��y� �����֨�)��OZ!~d_��pŀ��!^��������YpL�w������߹]+�B����)CuD�]���R���O^�i���پ���b���\_g�"Q���^[��
 f�>zp��l,��I�S�?�����F��7?�>���MӚ �;�j����*:"�&�WƜ�M� �ֆ��uFew��}&\ �6�GPEUh��5��H�r��*� b,'0�����-���)1(B\=}O�m�j����YI�̵��?�銅Tb�hoh�LIބqKwr��-���΍�����m?p��N��$2ZZ�8�&<�~"���!U��_��k�T��g�6��ɜ������-��%��cnP���POm�}����v	`|����W|����pD񐞧�Ui$����W��Y2��V&�0���YG0{NT���˦X�Vr*ږ-D�Zm���;c���᠑yN�"oe�9�.��a�9hT�	��Gp��G�,i�}��j�9�٭��lD�$ɃWl��ؿ�e��qR�'b�ug[�9>�}�ǵ�ċ���D#Us^��/J���د+����.ֽ�ո ԓ,ef��Nb=ѯ��?��^�u��Q�n޷
 ڿ��T�H����m�+�.�"�t�<�r�#�=�V�=��ؒWs����=�bFN$_�"*�Th���`�X���2�P�Lx�3 ��J��a	F���S��,����b�D0z�0JK��_ˮ�*�ci�0U_sj�Cs�9��j�[���W$��+0�Wfl�ׂ'|��1�D^�ZDKɄ��+0A��ҿ�Z�:Y"Qr�ot]���w7#���_�@�k����}�^���⳪5�1A�D���-���Ǌ;��(�閒��DS٣�!����i��y ���Dȯ|Z�rK�Z��k˃�9BYH�j)�D��g������m+c�B��P�0 ��B��,�����$�ӆY�K�(a�|]G,�~[!o��'cS�s�C��鼤FJnj���O���k��m'5G�cret_str);
	sprintf(t->dev_secret, devsecret_str);
	//ali_cfg_set();

	static const char* status = "id=%d&en=%d&product_key=%s&product_secret=%s&device_name=%s&device_secret=%s";
	webnet_session_printf(session, status,t->id, t->en,t->key,t->pro_secret, t->name,t->dev_secret);
}


void web_aliiot(void)
{
	webnet_cgi_register("getAliIot", web_aliiot_get);
	webnet_cgi_register("setAliIot", web_aliiot_set);
}

