�}~   ��kx�xb	    ��F�b�w�GN�|���	�o�U��C�k��xTTp �i����Zm�+Tu�P� ����A�:��&"ş�Q��_�[bXv��?B����Qt�B^�P�e�����w���	����H֓�8_����͠H�/&k�	��T��¶m����.G�.`P�!�l5�Xrp%��é��T��'�!��LŴ�Ie�T-��������n��Ʃ�N�>��j���I�}5fy��En_�%�D�ѱ����-^�H�#+��a�N؟�݌~qᇐP����4��0��M~ь-�s���x\��9nR�*�.Ae�L�8�h7������ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���t id;
    rt_device_t dev;
    uint pin;
    char name[RT_NAME_MAX];

    ushort recvLen;
    uchar recvBuf[UART_RECV_SIZE];

    ushort sentLen;
    uchar sentBuf[UART_SENT_SIZE];
    boolean lock;

    uchar start, end;
}sRtu;

typedef struct sRtus {
	sRtu rtu[UARTS_NUM+1];
}sRtus;

sRtu *rtu_cfg_get(int id);
sRtu *rtu_cfg_device(rt_device_t dev);

#endif /* BSP_STM32_STM32F429_ATK_APOLLO_APPLICATIONS_UART_RTU_CFG_H_ */
