�}) 
  �˩�[�KZ��u
���b�ϛ�>�=f���&�\�U�% �k������~Q�މYT��t�D�IM�x78Z3�)��S�����#�-~��U�u	XYX ���������#ac�fh�����Sc�  �:�XQFR����
&S�a�t�g�@�v壬��,�>o'�&��9;��� T(�9v3��;L��r���@4ؿŰDB������D|DO��C�B��s`]Aײ՛�0 _��m�N��!z�d�������ʦ����O�߱	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l/�����u�X"� `*�}�r�b���!Q�::�$|�VP��͚Vx,�L���O('2&�g?�A�7_��n�{����0�}� �W?\���M�4i���o�+<� `���U��٢��6q�_D�N�u�����D�������I�iP�}
�<3.7��>X�Ĵ���l#�qO�J@�r�� gU ���t���?P� $���bV��~������V�,N�t�
M�p��x��w9^_N%*�7���EL�9'5gI��9�>d�s:�lΒ�(�΃�Ygh��Ӫ�l<� n�S��AZf��rqⶒ��j �a���5hw��Vϛ�?�J��%Q;n%�O��(p�
<;U�J��k�#vR|����ܺ����.(��e�W����l��|��;�;���6���(�ҹ΁57sB�K%�h8ll��V6�໳xͫ�'/Bj-���ڄQ�����3z���DW��N�짫q�6*�]���t��Z����ˎ����`����F�(void)
{
	struct sNetAddr *ip = &gIpAddr;
	if(!strlen(ip->ip)) {
		ip_env_read(ip);
	}

	return ip;
}

void ip_cfg_set(void)
{
	struct sNetAddr *ip = &gIpAddr;
	ip_env_write(ip);
}
