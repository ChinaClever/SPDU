�}�   �(�#�2�K���u
��R�bw��,�ހ�Қ� *���+�w��v8�kܔV3M4�F�/k#��b�]����:�k>N�%�K�k-�� �E�t���8\Ҽ����|���O����˹״7k@M.<��8~�Tw�%�	�,Y8!�wo��{����*b�]so�+Cc�[�>�Hi�0(���0��v��pu�Y�Q�@g�XÐ5~]���hղ 5:q����X�2t5��H�"K�(���Aiݹ��B�ߵL� 5��>����t�|����x�����ɟ��6��B�_��Vz�)��
(ʚ�n�.��I��I�Q�믾�!�.�E�e��Bю��bq	�πww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���uct sLocalAddr {
	boolean isUpload; // �����Ƿ��ϴ�
	char idc[CFG_NAME_LEN];
	char room[CFG_NAME_LEN]; // ������
	char cabinet[CFG_NAME_LEN]; // ������
	char line[CFG_NAME_LEN]; // ������
};


struct sDevCfg {
	char devName[CFG_NAME_LEN];

	struct sNetAddr net;
	struct sLocalAddr local;
};


#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DEV_CFG_H_ */
