�} 3  ��, �����u
��w�b���Oʅ=�yڽ
'�t/��P[��|A�lR��9�8*�U`�G�1����j��/hp��רo{RyJ0±Ysc �f��a`�rb�����t�ǽ����/�u�@Q@�&R���"� mpv8j��&��*,�~o���4���[����G����.�(�<�UWZSb���|�[��g�=A�wF5g���4��nc����H*�5��[�ʴ��a��8۵�ӑ�7!l��w�0ǐ��y���nY���\��3�@W��/47;AN�N1|%D�X�/����Z�<���jEcJ\��Q楊�-���%&���xx�Ӿ��3�z4��`��t��Y�� 5A��x{�K33��6���y�\A#C!,V���k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���� <% %> ����а����ı������滻�ɴ�����ע���ִ�к���
void web_asp_var(void)
{
	webnet_asp_add_var("version", asp_var_version);
}

// AUTH ������֤����
void web_auth_init(void)
{
	char auth[20] = {0};
	sprintf(auth, "%s:%s", "admin", "admin");
	webnet_auth_set("/", auth); // ������֤��Ϣ���û���������Ϊ admin:admin
}

void web_main(void)
{
	web_auth_init();
	web_asp_var();

	web_output_sw();
	web_timer_sw();
	web_seq_timer();

	webnet_init();
}


