�}K B  �Z��OH�2
    ���b)�@N�o.�_@N?�P2��HOWAW�k�a�&J�y��߫��z�8��+i� `�7�:��MD73�K���/��i� ����s�>��3�6�87��I��=J������6b��a �r�[��,��4�?Bj������xw>�bĻ�'�띜�n������د�ӞAx.���׆���2E��׸/}4:���nc�_�S�ٻJ���W��J�'��l�����5���=���߫ye��A��q\�Թ*E	m�ER�2O�}=�[&B���]/Ͳ|$E�7c�$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���ttime");

	ntp_datetime_set(time);
	static const char* status = "time=%s";
	webnet_session_printf(session, status, time);
}


void web_ntp_time(void)
{
	webnet_cgi_register("getNtpTime", web_ntptime_get);
	webnet_cgi_register("setNtpTime", web_ntptime_set);
}

