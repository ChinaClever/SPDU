�}� =  �����O�Đ�u
���bw��,�ހ��6�כ�U�]��N���Z�A`�1A�CO�%��Z�`�>Q鋛��h�ύ�u:IyP���ʑ{K&ػ��~r[3��y�w!9
!9�������ßn�p�����L2�9[�����Q����zQ�?��g.ƒ���w�:?��r'�a�!\�蟉�gFDo(��-�5�_@���t�J��Y�L��R,u�Z�$\-��SB)Z��?�M��f�ٙ��2f�?�S{ ���Ԕ���n����{�*�+�ډG��	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���time2);
int dt_cmpCurrentTime(const char* time1);

//��ʱ���ת���ַ���
void dt_datetimeToStr(time_t t, char *pcTime);

// ���ַ���ת��ʱ���
long dt_strToDatetime(const char *str_time);

// ʱ����Ƚ�
int dt_cmpTimestamp(time_t t);

// ʱ��ת��������
int dt_timeToSec(const char* time1);

// ����ת����ʱ��
void dt_secToTime(int t, char *pcTime);

// �����Ƚ�
int dt_cmpSec(int sec);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_TIMER_CTIME_H_ */
