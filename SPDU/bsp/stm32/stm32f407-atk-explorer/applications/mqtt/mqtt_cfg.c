�}� ^ ���zF�G�8��u
���b9·�>�}&mᔱB�`�M(��Hn}�BÂ�a�׎��V�����I��y|�4�.�s���:���g�@fxO!�%Ķ>�|C�8_��yO�zgT#wy	D��Y6ԷG�5e��p-c�V�+�	Esi%�ϰ��J+�[-C��Uv��>�0��d42B�%�=W�d��$�gi>}w�龆�q;�v < �t6�J0M�udow�,[/��f?�a6�
� ܁(�A��\��+&qL:M@�	[M�O5��Q�7#`�M��y��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l*|=����{#M7/�c���0�T���9��~�p}�U.�	�:��ϻ!��ȘN՚��Q�:c���+�S%�/':O>{)^��8^�0�)[1�������S�w���K��>��D<��f��Q,o��>�h-�|ɜワ?/�i�>n^�� }�D���{kfo���c��]$�	e*�]�-�u+��a}H���+��]�mp	|Sc��WG*"�����+��$���;|�"�����KPw1>Y��;k���7���k��Xj��#ku���yGq9A.)��i*�5�" ��m%���
�S�E��֋Q"�����E�f��g�)���1�}+��>�AF�\�7!��U����`��Y�)^\�Ih�B�Z� �|
�L�Pr��a�?�J��Z�_ $',����|�K�۽��v]3MV�,8Y����Z٧2�̦i�ІE���+|�	Ѳ.o�Q�w�x9����@��v�
� mqtt_cfg_mdelay(void)
{
	struct sMqtt *cfg = &gMqtt;
	if(cfg->mdelay < 15) {
		cfg->mdelay = 15;
	}
	return cfg->mdelay;
}

void mqtt_cfg_set(void)
{

}
