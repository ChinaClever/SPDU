�}k � �-��Z�|���u
��>�b���GN���on"
�q�*�1�HYo ���K�w�`i�kƱ�n
$���t�Y�����,#V��W��vG�����<�!�Z1Wh��n۶Q��!O��O�G� 
���.�h�xݦB��U���&�?�:��(�&m!�l �A(Y�`��Y�۾z��ۿ�v�!K>���Iv���n��P�P�c��[��067(I8�"om�&jV��$�\�z���x����қ����	�)Z��f\�侅���($
��d�2-q����_b�j��p�e��(����.��IF�^��᭹8�C�6,��zG���c��2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l����Md�k���+�5l���\Mb�T���MM�E��Yqz�TW:������/��t8�S-QQ�q���l�?�?e?��X�����ǬV#C����ߤ��
�����T��Ո��v����W�l�}��B[�>��̑�%,U9D:�2(����
�.�+=�ZɭgG2#9o\B�Eۥ*`SB�D��F�ط,��XI�)����Jd��1�^wCښ�b�(�����(8ʮ�\Dh�_B�7/Aǋ��I�x���_�)h�R�C|�>xZ�����v��Z�S�*��,8��O2)�9*��I��Ҍ3Р�+��U�D�r]�?����9oӚ�.�J���1��'`޴��|⭄�uB�WT�X^ƏX6����E��+ jK:�����Gf���#�ݫ��RC Sp�13n%GX8�ќ��*M�Ǝ�[a���*�����U=
b����k,�a2qպ|r���x��&�$�fv1'C��L��?(��)ٝ�g�()q�E�l(���\U����!0-� �k>�9e��d31~-|�`G�V�k�&��Q��	A ��f6����L{��Bu��ru)vU���%sa�Q�8@G�������I�����r�(�̣�c�K����TeOV����uX�Uϱ]N�9�L���� /�)�:̯S�Ȍ���WP��yA����ћ~G�jÌ-#gL�1�k��U�vn"Y�Q<�|�֩�k��7 �r�6�NI|�Ee#�Ν��z�4�X^mVއ�$m����鴮�*n�[�-�:O"
 ����ŉ������^0#9��!�*M�&� *zo���[�W��FQ� �x�2+��[�١#�W�S���M��"&ȿ�CeJ��
Ӿ`�z�<�5t3��8���Q�Ev���˫�Me��%O�u,#<��&<�u�D^tZ�}�!�&�&B�N��Hn?THls��!Mh}p�uc����dz��|v/�c���������67���,������ {&��I�1Dk�����/�U@~;
	sprintf(t->pro_secret, secret_str);
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

#endif
