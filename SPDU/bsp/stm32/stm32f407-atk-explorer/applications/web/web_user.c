�}� �  ���v��됐�u
���b)��GN�}v�ه���1�WE�[#ސ͍�xn�V��Y�8hi�e�+�f.ep�sCM�-�����:g=�	���
^Ŕ�oE�d�rw�q�jW,ඎ<i6�~N�4V� D�c9�ŵ��ٲo]-^��_���t��T|��-&�u�	�kI���q�!���!��/.2��#�|ݞ�TU]��Y+r�kCq��!��tՋ6�Ȯ�?�Yd��Z_������^\y��$��lv��	G*c��N��
P��r�|XD��OK%�v��㻷A #�̂$��$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���uest;
	const char *name = webnet_request_get_query(request, "name");
	const char *pass = webnet_request_get_query(request, "pass");
	user_cfg_set(name, pass);

	static const char* status = "name=%s&pass=%s";
	webnet_session_printf(session, status, name, pass);
}


void web_user(void)
{
	webnet_cgi_register("getUser", web_user_get);
	webnet_cgi_register("setUser", web_user_set);
}
