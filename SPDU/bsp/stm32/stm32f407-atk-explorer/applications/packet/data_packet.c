�} _  ��R����.    ��2�b���GN�O���q 7��!I��I�L�{J���JVl�b�p
��u����&S�'�o~-{ g_��oĭ�T'��E��A}�� ��>�h�A���c�w�B�R\[zwE�X����D=�/�"qt�DZ��0�̾v��6�Zu`�� �E�w��9��A����1��2?w�g�AU��ẏ�i&��g�yg:-O0�!����?�������X�������Ξ����a	1�L�N�rz����߲��@��ݧ�vM���@w���fa���cs��
�~��3c�h���{����E�?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���
	struct sSwItem *it = getSwItem(pin);
	if(it) it->sw = v;
	else ret = false;

	return ret;
}

void setAllSwStatus(int v)
{
	uchar i;
	struct sSwItem *it = NULL;

	for(i=0; i<OUTPUT_NUM_MAX; ++i) {
		it = getSwItem(i);
		if(it) it->sw = v;
	}
}

int getSwStatus(int pin)
{
	int ret = -1;
	struct sSwItem *it = getSwItem(pin);
	if(it) ret = it->sw;

	return ret;
}
