�}�  �Ϛw��d�w��u
��V�b����G>�}�ۡҫ��*���+��n!��Fٞȩٌ<<]�Q#zӹ���݊e���&=�8���J�kux�oF!��cM�x!	�A�*�wE$���;e����+��4��ArY�/X.�������
����|ɜ̶!>S9�=�x񷸲���I]���R�k�t����#Q �G�	��)�%���J��üBNpY��v�ak�f|f/�)��� {*�	�o�m��,��M=�d%M��5�L��|/���yr�h�ϸ洿��%��_�q g�V�+o6��r�Ei������O1�$���_��]�W{��f���d2(%�Ȅ~8�	��zx��f:��ni��y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���= RTU_CMD_LEN;
	list_t *list = rtu->cmds;
	list_node_t *node = list_at(list, 0);
	if(node) {
		memcpy(rtu->sentBuf, node->val, ret);
		list_remove(list, node);
	} else {
		ret = 0;
	}
	rtu->sentLen = ret;

	return ret;
}


int rtu_setReg(uchar addr, ushort reg, ushort value)
{
	sRtuSetCmd cmd;
	cmd.addr = addr;
	cmd.reg = reg;
	cmd.value = value;
	return rtu_setCmd(&cmd);
}

int rtu_clean_ele(uchar addr)
{
	return rtu_setReg(addr, SI_ELE_CMD, 0xf0);
}
