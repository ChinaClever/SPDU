�}
   Ҭ��se+\    ���b)ω�GN�}&����)��I_�M�M6��NX؆֤?��z,��g+�𷐵�;��"�ҫ���v�z2ތ��dy��>=05F�䜧��s+��)���{o�hw�RP���7�:5put��l,�KP�2��!^�0������P��X(ʹ�5;���Xh-al��/���q�Ѽ�����d��ZIшU(��W�[h�p|V��X�Wi�dͲvƌ|�3�.�qZ���@z|��гAy�������>���a�I�O ګ���0͔�|2��������$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD#�X���U��!���ek����,�P}�Aq �$���q�`j �Ũ��ﲙ?8�����c5��k>��#[u4��}یE�.	�	�ŨgkR�M#-ǾSW/_�c5�aj֖"��Y�{<�5bl�n���0#.��=Ӳ�R�8Ԯ����S}vK�x6��Z���`�\�f�ɅD�����h+�i�)|NA8\̓&G���{��� /u�.F.CMz�L3�S�1�e���|�k�O��ۺ����OR�&xľ%W�+{%��ܮ,G&Fbץ^P _��ԱfX�t �^�w��,_��zF��^�ҵ��T^�V��M��c&|ko���8�ϳY�����_���D����L=�R���3���j���^Q ^��EK�*g3B��2���y�߀y�@�m3ӄi�t'�����9��iy/�P���_T2�@�<�Ns�[�q2�N�"˴��F���N�Z�]��ef˙D�
��	�,��w���X�mszJr);
	mb_cfg_set(&t);

	static const char* status = "en=%d&port=%d&addr=%d&baud=%d";
	webnet_session_printf(session, status, t.en, t.port, t.addr, t.baud);
}


void web_modbus(void)
{
	webnet_cgi_register("getModbus", web_modbus_get);
	webnet_cgi_register("setModbus", web_modbus_set);
}
