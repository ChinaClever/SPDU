�}K   �H�gX��S    ��L�bw��,�ހ��֜� �~�W�c������Pu���
¯�:�A����,�o�E�����D������gmdZTV0����'|������@!Qؚ^��+Xp�A[����]�;�#~���}�E�˖I�T��0B�4y.�p���������{�-�3����?BK?�II�Tۓ!6m썍:��X����uM�.g�j�,O�V�7���l�$cz���x�/�.�Ja�P��2T,�U�&���(�_�l� ��(2������H�mfxQA��T
;sf�D���=��Y����7wM��SQ�j���ɨ1փ�D��Ή���3�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���  ushort crc; // ��ʾCRCУ��
}sRtuSent;

typedef struct sRtuSetCmd
{
	uchar addr;
	ushort reg;
    ushort value;
}sRtuSetCmd;

int rtu_sentAc(uchar addr, uchar *buf);
int rtu_sentDc(uchar addr, uchar *buf);
int rtu_sentCmd(uchar addr, ushort reg, ushort value, uchar *buf);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_SENT_H_ */
