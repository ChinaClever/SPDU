�}: �  ��mE�0ܐ�u
���b)ω�GN�}&����)�17w/A������x����H�Jd�ߤl��43�K���-���+�s2���	^%��fX��;K�B_6���7t�1}�.S�]�zKʷ�D8*/K��S��b[�xt���w�����7_I��q�>�P��p�lM���k	h���[}��Į�߂ùokr�]�2���_h�,��}��\�B�?��2�X����!��p����^e���&h����צ��QT�:}A[����>���TKD�v���MA:��B�x@ڈ�Gw��na$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���->request;
	const char *en_str = webnet_request_get_query(request, "en");
	const char *port_str = webnet_request_get_query(request, "port");

	struct sMdCfg t;
	t.en = atoi(en_str);
	t.port = atoi(port_str);
	mb_cfg_set(&t);

	static const char* status = "en=%d&port=%d";
	webnet_session_printf(session, status, t.en, t.port);
}


void web_modbus(void)
{
	webnet_cgi_register("getModbus", web_modbus_get);
	webnet_cgi_register("setModbus", web_modbus_set);
}
