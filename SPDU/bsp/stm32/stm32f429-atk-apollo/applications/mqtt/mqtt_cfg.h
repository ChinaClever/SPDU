�}�   �{�b5|�q    ��^�bύ�GN�=>���@�5sj<�8�'���0|B8C@6'@�J[�M�D[�$�Dp3���䊔4�mN#<omX�Ж���{u���\{u�x��<�1>(��߱�WwYJ�S���y��ɀ�e5
y�v����b+a$��B��߸"�y1��h�X�~0�W'�nP=�{���	~�����?;ZXj�d*:k�`	��M��(ÅqO	��u�閟�1��|ժ�6�O���O��nݧg��nL�?I׭���r�ćީ����=�$�8Z1wȗ�7m�Z4��3
�Z5�"����N)0ㄎ�b@� �b��~�m�q�_9wN�e�9#H�X��a�Ѳ�3��fq��B�,���k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���ar cleansession;

	char pub_topic[32];
	char pub_qos; // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���
	char retain;

	char sub_topic[32];
	char sub_qos; // QoS�������� 	0���һ�δ���   1����һ�δ���   2 ֻ��һ�δ���

	char *pub_payload;
	short mdelay;
}sMqtt;

sMqtt *mqtt_cfg_get(void);
int mqtt_cfg_mdelay(void);

void mqtt_cfg_set(void);
#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_MQTT_MQTT_CFG_H_ */
