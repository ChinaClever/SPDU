�}� �-  P�&�c���u
��Z�b�{�G^�=��@~�H��=Kh�#�T��6�� �$r��i���a����lE����:d��s
')IyST/AG)�F��-�u?ް|�]��JiE�$̙�"�()��C*J��!�Z����b
^&
��;�ܺR�y1��hZY_CL?����j�RO e�}���m�k4y�j�41�n�CFn����8���/���n�52�~�ua�y.RhRZX���������C��3G�D�UJ5%�Zۇ-��A�����n�r&�x�kY��~zNf>%ܔ~����D��z�&�HF�cxT>��W���0
�[�(�,[�_�����}��?�"��!}�֔nX���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���n;

	char pub_topic[32];
	char pub_qos; // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���
	char retain;

	char sub_topic[32];
	char sub_qos; // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���

	char *pub_payload;
	short mdelay;
};

struct sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

void mqtt_cfg_set(void);
#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
