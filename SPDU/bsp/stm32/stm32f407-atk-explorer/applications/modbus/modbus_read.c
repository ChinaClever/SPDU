�} �  ��d
ɩ6ؐ�u
���b)ϙ�G>�}F���RG�Q��N�>#,��^,�|�_&����ߺ��8�)o�`9��F�2�wIZѼ�^�3|`��{�-���-�Z%2ǚ�L�~MWk�fSGU��#w�����Qs0�`�*a�ML�>���W�ү<x����<�.�)�и ��h֑P�m[���@s��jX���/���]vg�h�$\�(`y���(����X���E��[�=t(�9�;���$�R�����>���ܯ���0���H���[)lQ,��4G�BP�ش���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l)�*�k�
��]B��#IB�K�ǔ/�G��n'Ӻypװ�zO�_G~�T> ��aP�w�Ѐ�"�$�������mD9���ps5����}7d�ǍK��&θ1C����Zt���T���!v	�.�2t.+Aj���[�����y��j��[��s��Ƙ��7�Ga��ą�(�E����k����v��l(�n��N�R�9 ��Mm�*G�A+�k}�&r�.	�C�W������H(8��2�ܕ;B<�	1�a�f�!�:�����[���!�E�D1��#�7����j_���|��Q�C�{���|���U[�S��3z�F3&��A��Zy�Է@_�,�д4<c
 Z��j�c�<e@�����Ps�bFE�e��h��\���/�x�}=�u�<E��i ���ɉ���<C���-m%+m��x�H'��I���*B���Z�
Fm���^S���cô|�n��=�n}1�T���_1�f(packet->offLine) {
		sObjData *line = &(packet->data.line); // ������
		sEnvData *env =  &(packet->data.env);
		ptr = mb_read_objData(ptr, line);
		ptr = mb_read_envData(ptr, env);

		*ptr++ = packet->devSpec;
		if(packet->dc) {
			*ptr = packet->hz;
		} else {
			*ptr = line->pl[0];
		}
	}

	return packet->offLine;
}


