�}� r  ���9j �f?��u
���b���GN�=v���e*)���Z]����pX��6?�ܐ�GZ9� ���ݸ�;
��B#7DIl�eY���P|�Kv�gA��t��R+��U'��w�l8�ۓ[��Cȴ�d�+D��N���b�~ӌd;�	���=׬vnI��1�G1�kI��z<IR�=%�Ek&ǃA����~�B<��=����+��*Ok�=o����n3���&�,���D�\>���m���JЋ7c��!zU4��(]p˱0�밞yn�k�	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD%T���TND�kw��\���HΕR�N4�Z��3�n�#�իx;���V&g\�ԛ�"��-�ef�՜���u�eP�M��t3����y�93� )�Պ��T���0�1~��iB�������oA3!J$��;[�?5��p��Q1��UpCV�\K��noӚ8Z���!�t��=-�J�-[z�,��Y��u��&k̇sQ��B�Fp�Q���"�{f�3xit��Ce5�r��
f�jm$���Uny[��iT )�n6;<�Zq��o�34�N淵�L�@�P:�b�cV�I~j�� ��[��i�$��;���WQF�S8�nk�z?��e����i�&�?k	aJ��;Ϥ70nr�����Őۧc�&��`R�|aA�+	��Yx����0���a�����Y~��.�@���3�x�w?��]52O����Od����CK"�WO9ܬ*�ST��7:PLr ���M���s���wW�!&|ݙG����(�OνV7����҃�r(mb, 0, sizeof(sMdCfg));
		mb_env_read(mb);
	}
	return mb;
}


void mb_cfg_set(sMdCfg *t)
{
	struct sMdCfg *mb = mb_cfg_get();
	mb->en = t->en;
	mb->port = t->port;
	mb->addr = t->addr;
	mb->baud = t->baud;
	mb_env_write(mb);
}

