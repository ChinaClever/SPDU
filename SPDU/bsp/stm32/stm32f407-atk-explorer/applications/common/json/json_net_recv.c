�}� �  �����Z�����u
��R�b����G>�>�ۡ�p�����<C&���{�\�yP+S�$ԣλ�KsS���У̔\�V@'��D/ƣ���s�+b �I�  g�*�'q
n5��|g"��=�Q*%�66��yx8�g��d��`�p�k�yN�z�A�qr���4�N�I�����
,a8�4p��aPg�}�t��TsuYS�N�jk������W��p�#~�겦	���wq|�4�Z���H���ǁ�1���"�#Cd-�ᬉfi	4d0�����m�qDt�c"{���Phr��q
W��T2V���h��&n�q�.ӛ-qwg����yI˽���z����io@g��'?�B�F�!Ĺww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���in = cJSON_GetObjectItem(arr_item,"min")->valuedouble;
			double max = cJSON_GetObjectItem(arr_item,"max")->valuedouble;

			arr_item = arr_item->next;//��һ���Ӷ���
			//setSwStatus(id-1, v);
		}
	} else {
		ret = false;
	}

	return ret;
}

boolean json_analysis(char *str)
{
	cJSON *json = cJSON_Parse(str);  //�ӻ������н�����JSON�ṹ
	boolean ret = json_recv_array(json);
	cJSON_Delete(json); //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
	return ret;
}



