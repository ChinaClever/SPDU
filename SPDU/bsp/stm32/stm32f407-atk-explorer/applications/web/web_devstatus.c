�}� �  ��ր��Đ�u
��+�b)���?�>v≧'��]$�P�Z#�OW��Nz��M���+��z��{<��/e���G"�_fE��Sq���5��>b����fS#��T/a6��!V��U�=̜�~j��sȻ��Nl4���P�ے�.������$F��D(nk�������FOB��i�p����;�iՇ��Y��qK����P�ʎ�MoĺKlV��@w�bSd'�u�K|����������0ESR��	N��a��Yg�&[��^/�ړ��5��Y�������w���$�*t��}�9��*��q��>�ů��L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD��=�<���Q2l��d�RI�A�"A���7��&��p��Knc9Ep�%K�;ZH�K�C�/;�kg�����y
ȣŔg��?o�+m�����C7��؂�}p!zqU���}�^[㚟YG3�8yA��7��
��8�윶\��@vD� �����}�)�5����-vr�m�;���R��ǔ��u&!��m6`�ai�OOt��<��z�u�Rxҹye*un�����&��/&p4D{NIqP�n�n����[Y�ф��,����C4�H_�VU��=Q{[���w������а���@!p��IņxZ$�=�1`�3#��u[��Y���D�)��y�5��ȓ�����+��%��slP�j��m�}���d�P`|����W|����pD񐞧�Ui$�٨��W��W2��V&�0����EǜR���˦��Vr�(��-D�>m���;m���&�g���"o����.��a�9hT��Ip�G�,i�}��)�E�v�٭��
	sprintf(ptr, "&pf=%d", t->pf[line]); ptr += strlen(ptr);
	sprintf(ptr, "&ele=%d",t->ele[line]); ptr += strlen(ptr);

	webnet_session_printf(session, "%s", qure);
}


void web_devstatus(void)
{
	webnet_cgi_register("getDevStatus", web_dev_status);
}
