�}� �  ���1�seR��u
���b)χ�@>�=&���Bt03�m�u[R`^6��p�¬��,:��c��\�-��(�8_x�k�w,�Pu\���������UF�����nW��-��֑aFz_�ʢ떳�K	�|��t��ΜKs{#�����r����,��C�W̕�;^D���ǋ{f5��"n����%�Hɍ)j[�G!hzBj�W�~|X�=<�D���BA���[I�.Q׍�H⛃q�O�.�4�ة&��f�A�yC�l����<�����&��樀��U0������@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l"�z�X�lEY2X	s�jm�):o!�\PsB;��V����=%s��� �k����Ki@3�U��"\W-Y�QN�������i���y�9W��>�x��c#�+�m�jk�.);F�J�.-j&���l�1��0���^��a�c�����^��4<'۸�U�]?`�r�?,a�Z�h+Q��[֗g�Ez��Q�d�W[$t��xκ|-�$O
�����R��r��_���73\.yoJaF�Ҥ6���e�����4[Uh"C���[F)%��MO���œ��s�:�p:Ő:9������u��CD�����Q���	o�V�&I��d}U.��\���Ng��H�Z�?���H;P����Zf�u����Lnl�{�E~��a�5m�f��$Ȑ��co�h��£�a�kI��b*oay�L����ّm+�Ζ���Ş��\Z��б;~�~8ܪa�V&�������3�y[�N�P�n:���[���;���M�H�Q/�K�	static const char* status = "ip=%s&mask=%s&gw=%s&dns=%s";
	webnet_session_printf(session, status, t->ip, t->mask, t->gw, t->dns);
}


void web_ip_addr(void)
{
	webnet_cgi_register("getIpAddr", web_ipaddr_get);
	webnet_cgi_register("setIpAddr", web_ipaddr_set);
}

