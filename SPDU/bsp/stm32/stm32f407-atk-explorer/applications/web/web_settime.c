�}e �  ���KG�ܐ�u
���b)��@>�on�d#����S�I�˔�r�)���d�R����U�%|���8&k�]�ik\C3��lM��Ϛka�/��u� ���!�2�tQtz���֟M�v��5CgZe:�Ȫ��^ev�[��,��4�?A
�+��o$�⮩����)�E���Aa��j��6���5Ns���5��,ؼ�)b��DG�[Mq�}���8-�<rR3]m����2k�=:r�����i~�Ɵ�L>�Zw�A���qN1�i�4&lq�h&�c���5���^�����%G[�>u��3��Ǟm8Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
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

