�}   Ԗ�� =D    ���b)��GN�on�l#G���x��a�Q	����� ��fT,��ɳ�(^1锒�j�񜎆Y'Y��F��Rly&�d/m�?�p:���	����*2bK��4Cl��*#��`�S+���ɜ�[4f>��j߼2>{ˏV���Av?-%���%�%Œs.�"��������>�נ)��͉�E5�z������oi��}ق R��B�=����y������]�5|��~nJOm���=&�;���MZ��z�%�8��Ǿ�j[^�l�3@�'�}��܎��i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���ime");

	ntp_datetime_set(time);
	static const char* status = "time=%s";
	webnet_session_printf(session, status, time);
}


void web_ntp_time(void)
{
	webnet_cgi_register("getNtpTime", web_ntptime_get);
	webnet_cgi_register("setNtpTime", web_ntptime_set);
}

