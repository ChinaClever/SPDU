�}` �  ��c(��R!��u
����b���G>�>>J��­s�?u�6�{C��$Xl(Dʻ�]D�%X<K�Rl�c	�p�G��> ��]��Pއ>��b^�=}��n	�lD8RKk�\!n�ܵ9x�D_l��U��{�벎�yC��& ��5��F-�`�L�h�4U����y�S|+�혙�-�q� ?o@����o���`.O�G�}����
���G�^v���wߥ�mL����B�WUm����O��N0�����G����Iy�F�o�F���{�E��2�q�0�밞yn�k�	<��@���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���r->pass, res);
	} else { // ��ȡʧ�ܣ��ָ�Ĭ��ֵ
		user_env_default(user);
	}
}

sUser *user_cfg_get(void)
{
	static sUser *user = nullptr;
	if(!user) {
		user = malloc(sizeof(sUser));
		memset(user, 0, sizeof(sUser));
		user_env_read(user);
	}

	return user;
}

void user_cfg_set(const char *name, const char *pass)
{
	sUser *user = user_cfg_get();

	strcpy(user->name, name);
	strcpy(user->pass, pass);
	user_env_write(user);
}
