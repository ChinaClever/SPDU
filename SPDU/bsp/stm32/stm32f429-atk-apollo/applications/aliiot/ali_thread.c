�}A   �ju�^ݳS�    ���b9�G>.m�*ds{�ح!K�^�e{��va����\�+����U���)�����g]$]�"�B=Ԍ�jk�'a�ɽϴ�_��zU>���Ԧ)�$.�!����j�8���pG$`Ʀr���4A��=a��	�M�/#��f�l&���z�a>�ˀC(�2�>z��G�aHF��g���J�b;�����͏f��E�O�3{.�)V2����X0WsJ�Nm�`�ЂX����p�����,�Ov���%>����>���ԃhxH��`e�xױ���$Ծ�i��� u����L�g?(��5|=��a�f�2��cH��ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l4G)�٧ �jS7Y �>�;�oT��C�^��b��.bQh4�Кֺy:��=Y��h�֍����.��B���(C:DR�o�H<'9:��k��.-��{5���u,���Q ��<�]�ƃ ~���&r�q�4~t~Am$zi�_��^������#2Ag���ӫ���;I0����(��FB���*C���X�0�&Y��dNm%4[v�g���8S{7!�h�9��)n�O_�.�x���Ɲa�5�t�;@�@f]��3��<���)�#._����%�,2X�@3�?U���jg-GX��0P�Cdɓ��Y~r��XW��+^���j �m�	^���n�Â����G�Y�m۳8�f݊NM��4'X��nLo��*=Dxvu�<X<g�pd �$(6��\��� +�!��w���֚2:vR������SI�+Y#��U!��;(�(�ň��#{�1��q�N�-B�񣂶�	��;o�����G��n��;
					free(msg_pub);

					if(ret > 0) {
						ali_pub_alarm(i);
						ali_pub_error(i);
					} else {
						break;
					}
				}
			}
		}

		if(ret > 0) ret = 10;
		else ret = 1;
		sleep(ret);
	}
}


void ali_thread(void)
{
	rt_thread_t tid = rt_thread_create("ali",ali_pub_task, NULL,6*1024,19, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

