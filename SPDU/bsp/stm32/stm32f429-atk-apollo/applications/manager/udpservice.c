�}� 5 �}���«    ����b�ύ��_�~>��e� N��IP��,5�eǣ�D,j�f`�2�
�4��W'�g\Gn��<@�WJ��������m
c������{{(=( ���ICy�@���j�n�5�i1�n����+�����/��������`V�-Bg��~�`C�c����&���m4�W�Vx#����B4���rIYy�E@�����3��ZP����hŪ�1I�s�� ���_��.���s����t�=m@@*�O^HFG�`6����3�H�0LN��{�=�I��#�pf���%��FN��;Y���PRr���((7�E�AﴣHqmc ����os�V�;�Ο.��U�ɹ�c:vx���AT`O���-`&Hf��[��7{��KL����f�	On�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD9ޣ�Ib�9&XE��B�E��gKH&�����c�	�Ό��Ɗh��@@c��!K&���b��병.�}X�T!�
b��bP Ľr3|��Qx�hl?Rw���(��Z�G����Y�Eޑc�q:F�o�0#�+��(؜ ��t[�Q��˥!]��NZ�K�%��@i9�#�Q2��L�=@u�B|5���,%5�E��p%��}�2PT\N��K��2�(��[���nJj�>q�2=-Je�Y�d4?�gv|=,�*Xf�wb׃N1��-��<EV���ɧ���>Ǳ�4���:���v�\��hc�rQ��N�Lr� ��/iN�.���%�:�JPТ��Sw�i���.���5��s�F�1�;�t�
���ᑺ,{E�H:��N(����M�
����GAȈf�(��b���K/�ed�~c�;WW��s��T]�p���u�� Ki1wO
1ld����%�p��-��e40�4+7B��k��298�Ar����ͪ
�����,�$l8�VS�ny�dM$�2a�����'�Q�i�H-�`��S;p��û��3��
mY�mF�v��v7)�ƥ1�="q#��e+X
�����\K�����"&�-y �C�];�bA�g�n���o	����|S�����;�Oყ�}�&�?�*A٩tH0��Iӓ���I�6�^��xo�����s�*����X*��J���,�J�E��
���^>{�^F�/��/h���3(�05]�Q�sz������x+��\�L���!�Z:����f��F���7'��M\�ٳ�����\��
�J[����@Q������x��xMyn���9�����<L�:(��¨��g �g @���5{C�ޣ�o w�!� ���4-���LqU��@����B@��������D����AՆW9�%T]�A���E�Q��4z_��zР��; ���1���&bZL�=e�6��9-�57�>��-�zC5�.�ߩ��ovl�;ҧD�0��.�O�X0qI�%�T��c%���梇n�n���|��Y��wW���F�-=4>���kz�d8�6,~>��F�3���D%OQȚ!��NQ~A<Z��&A�LX�y�\IDjV:���?X���0�1y赸x��'C�b��z/,��������y9Y��F�`�K�R̟�V��\�A3��� �z���<=����i^m�ル� ^��;Lz�s�s���_��%ײ	]��8���<љ��ʸ��jF�,KBx��5 3���
�c��/\P�uk�.t��́n���Yi�?�|�m�|����8w�fA:7[g��>J�qd���[� �"S��|C7�����D��+�*�p=3�a�����v�դĦ���H�Ɗщ��>�f�A@�հX}�|j�+ʇn�a*">&i���7�m)����Q`H���̖�o&�T1S�a��LM��O�^sE'�m����@�ǛȰ�]�=?y����О��(F�I����ݬ���� TVr��{���:l�.��Bs9�͝����q�S�s7�+�Z�D���k`X���V�r&_ ��0��Ȯ�Tn=�ї�����K���=6����ē����J��'~:�� c�m4��xe'�����D�;���;����n~!
�[�Ah��>�MwS�N؄`~��[б8�hHMpۗ��w1�qj�,$n�F�_���;��ӞJk3�$�Mc����]:N�-e�: ?,�G�[%�b�YZ��5��J�b{z�9��+�|����e�����+��t�┾��nk���]wP����_<���추y��Qk����t��9���F��Kl'I'�33]U!���#s�;��΢���9u�zQ��OI���b�PA������I^�V�_����;�cY�o�Z��JߤؙR��4���������$���*�eM�s�h���V�mD����!{,o\��)p�TjV�j�+5�xq��0�5�u�0,��8��w�b���|����"7�����_PORT);

	while(1) {
		memset(buf, 0, sizeof(buf));
		rtn = udp_serviceRecvData(sock_fd, &clientAddr, buf);
		if(rtn > 0) {
			udp_recv_data(buf, rtn);
		}
	}
}



/**
 * �����������������߳�
 */
void udp_server_thread(void)
{
	rt_thread_t tid = rt_thread_create("udp_server",udps_thread_entry, NULL, 2*512, 22, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
