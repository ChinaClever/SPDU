�}� �  �5	����0J��u
��L�bw���T\�ĶX���h�nP��U�a8��g������iN����@5���:Š�$(��(+��ջF�7������P�F���M�^M���~��x�55�`P��R�G 1��z��97�7ڑ�xÍ��_�� �	��&��.ۍ�o����[+�<aI8�ʗ����������d	�*.zB�:��v�M�`���6"(x�-Q<H]�����`����+>��5��t��Va�[ݜ��a郣]�&�]:ۂ؞-�~���jGS�re�^z�}�Q��rOK߲v�Ǡ��~!�Id��>������$sm�I}�Ԇ�?eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�3S��YZ�K�y�	�`�|��$h� U�&T�p����%3���rd@xl�^�Y�a2��O�y����
[�{���d�k#裭)���Dh��>�Mχć���?�/��WL��yJ�V�$��j�D4
6��F���36y���G�#6�I�$by	��]�v�ҵ�(j�#~�W֐_&�΃�3 ,����Ӹ]Uۓ�j(�Zo�@���Fp���u� D�GPqk\@G�ׄuT�G�~���4�4���`�?���.�|�ѩ����a��
C���Cp�Lo��m!���7��C0d��%XY|Ћ���֩��NX(�;?��o��qz�X�)s-a|��gc�{˦�
��Ԙ=8s^�VʲK"���"Tƺ�%趱,�=Q��?[�4s":�uj��� 6��
ڶ� �����PC9AZ�|dA��cj�np�pG�f�5����`�k����C�	���4AS#�T��^�񘒫B�lҊzP�E*'���VrSȋK�2�ֽ�*/
}data_code;

/**
 * ���ݰ��ṹ�壬
 */
typedef struct
{
	uchar hdr;	/*��Ϣͷ 0x7E*/
	uchar stx;	/*��ʶ��0x5E*/
	data_code code; /*���Ŷ�*/
	ushort len; /*���ݳ��� */
	uchar *data;	/*���ݶ�*/
	ushort XOR; /*У����*/
	uchar ED; /*������*/
}data_packet;

int data_msg_packetSent(data_code *code,uchar *buf, ushort len);
int data_msg_analytic(uchar *buf, ushort len, data_packet *msg);


#endif /* NETDATA_NETDATAPACKET_H_ */
