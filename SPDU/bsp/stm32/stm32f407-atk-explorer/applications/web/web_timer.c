�}. :  �p9s�� i&��u
���b��G>έ�*d�s��2ܸ0뗞������h�9��<��#�W�iX�$��~��cJ�q`	�'k?�W�y�j0O �y�Ы?>R+ö����i�:�f��WX�9mG�
�gʴ���E������!��F�̡ʱu���	�)�5u���7�񤥮��D�u����#��E!��X�R\��~�6�|�w��g~D�V�-��7��Ð�:W�ô~6�8��n{q����q1�$5�I����	�������D�ڂ��W��1��}j)-F<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�%�� ���dh�9+0��� 8���=�K�@�6���K��M��S|=[��7�Oa�pO?v"͏���x5U$/P!;�L����q'B�����hU
����@w��vc`g��,4i2��N�bp��dC,�+��[��^��# �Υ%�4��Q%888��F��&W\�;溭��d�ǡ.�o�;KK����:)Uz��Ơ���I~|�bOJ�0f%Dʲ&0�R8���5�䧸Z���%�z_8�"�@��O�"r��U�����5�f�\o���&�����"A��	 ���Jٞ����B
--��a��R�lF�-t�����>v��p�uR�`8��i�����H��#��C���rJúy�'����bT�|2
x���($6ͣ�ؾ�<���y�ȢdS��?�����p��?A)�lr��o$�bS%:(�2��ϓ�}�
 ��)}Z4�bNK��V��4�{��l��bKɿk��yX!��o��������וSKSLl-�K=0l�*�7(�1_c���,Λ����7�������1Z&���K�,7X�:b:�F��9H��vy%cuH;T�Лi���;Q��7���-�	&�R��O�8�ڣf�����'�*�O��u}r�U�Ū�}WHT�Ӳ��䅋$�^�J����D��r��ȍQ��y>��<`;T���76�Af.Rv�j��P��?������mHz��SJ����}�}��#�	��m�e��wd-"ϵ�T�c��,?�!;�'����-T���0\F��֎�o�;�iMYE<��I�S��6�X�X��M@SL�X�Sd_��Q:��X���w2K6.���ۅ�;�*�h,h-xX���m1͚'@����) �D���uKW涑�Xfi��zNhXÓE��;[���u��<�ljJ���̜�CP\YEm�Z:����#bSز�:]k��YK	Yx�J�((���\q[P5Ԇ�B)�L6p����Ȏ���I��s�2aB%<��*O5g�$A�i��%�l�!�JAch*����,ke3݁�&�L�LI@{cl����G�Z����v��rg������~�a��H��&�8N���`cZ�-�����~0n��k �)�G9�x�KW��dm������ʣC/,�9f��0�>�;��!��.@�����'Ai<+�xߦ�N�
,gnq��	Wb'3�&?i��`�d��?c�|t�?>$����Q�zG�C:���9"�×� k� [�b�����޻r��M9������͸�j0�(����;��h������@	�{ѭ�ܚ`��	c��,rc�Z�&��;_���I-�B�8@�g�p�K�r6\$�@-{��h�A���D��}?J�r�6�3|�ځ2DԀ�/���o�֜�u�(qN	i�H���"�m?��x]3�rU#F�>�Y��t��nA��hn�\:�T�BS	XvJ2��Nl��u��+h�@j�i�H`B�8h�DD�b�v+�B,@k�*)=+�R[�*�����Z��pnet_session* session)
{
	char num, i,v, *ptr=pWebQuest;

	num = getOutputNum();
	sprintf(ptr, "num=%d", num);
	ptr += strlen(ptr);

	for(i=0; i<num; ++i) {
		ptr = web_timer_getStr(i, ptr);
	}

	webnet_session_printf(session, "%s", pWebQuest);
}

void web_timer_sw(void)
{
	webnet_cgi_register("setTimer", web_timer_set);
	webnet_cgi_register("getTimers", web_timer_get);
}
