�}N   �����B6qb    ��s�b���GN�����i<��w�EY�_l��M�yĔh?��?���~2`�}�M�H��Ȕ��v�/�>�ZKs��a_�:2 uh�My姌	��s�\:އ����%M��(�A�E�)*)94htf6)!�e��n�2�U_�&��M_8��Jtt3��{���`���b~�������'�Sk!�ԙ�'h�R�}Sž ��$�0��P��� �s��͌���R���w�,BF϶$'����{n�}�2t쀉e�]@㖨�	U�2��0g��h'�Smv��S�$d�)B��6�3���Q�d}�}��3ACۭ�T�;Jւ-l��(E�JȚBG8��	�8%��3�K}��L��8E0�zHq����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�1�P�<�W`FkOE֡��:;��:��@F�����Z�U���k3Ks�w���a�$L骏TV�"`���2�����ќ��t^:��a������`�^P!69cS�[r���;�9�₂��a+D-���QB�$�~�:J��� �I�֑�#j���eB[�=qB�3��������w3bY}���G��=�]�~Y͆���5+�O>�ϭNL�s��`���
N�é�}I�δ�ۺ�.X4���+��f��`N&.�DLz�	�(n��0�O鄸�$�>��K�1g֎6��$����a+��#~|朰6ٴ+��ߞ ��'����!W���������Q���(����Ήv`yN���'�B$���o�;��������=���� ������RdJ)�2s��ٝ�����߷��N��:�&sof��I�:���P���h�3u�P��*�.�L5��QA��W ��8pq<`\q��.r�f-<�%]����l�3S�й���M�[R�^�}_�Dc"K�s������K%I�s��Y�E��CUw�����K���Sd�Z�g3X�³>�Zڀ~�_ �.{�`���`���p��¯܁Q�[ة�\-!u�y��f�f*».��TU0۝�7נ�c����ݙ��O �_0�?Ц�L����V�l#�� �<\i?&��Ԡ��^�k2z��;�S*�����k(�Zo�v��-�}W3�h�Y��=��f���a8BL΂�C�F�����~�	C�3�]S�OƮ�ͺ脚`�����w�0��ld�,����s?(\xU��@:ggUʤӛ�Sp/�z4����=��b��jc�4�V
��:xHT�˂	O��E�β��F%E�S��T�����-n���Df觯>�n���-���:���jwf��+T�,BR$�%`O9u������86V�W�KX��x-8��J����=��*^����SP^nu��.�j	,~ �-)�7�&����t;O��Tj�kql�,na]0h�λ�Ꟶ��I?�n�I�99��4E�E����*��C��f몝�~D�����ž��[�<�o�:VpIZ�o�"x)�m�C�b[�#1*�˄"8`��-
5i��pN�1+ZFD0ܦ�� �Ws8�8����5SpԪB
>�_�>�YM��!�D�t�^�Lp�Hme�_	WL��z��T>�tO�$"��j^":S 	N{���ń#I3���C���=��Q<�o'n�0>\�,	UN B_�M��>���'�����Ty��񾏒b`���e����#��d*�r1"���������c ����~I��k�_���l(p{�$����Kڛqџ��4?ձ�罺����T�	GSB�f2�N���y�1[��/w6]}�LB-��F/L�������]j�~����U�쬵�X��R�j�-�� '�6�W�z��۩�r)P�O$���[��\��TD��리P�28(>�^���]n���_q�~ddł��z�KX����m?on); break;
			case Http:  net_push_http(json); break;
			}
			net_delay();
			free(json);
		}
		sleep(1+rand()%3);
	}
}


void net_work_thread(void)
{
	rt_thread_t tid = rt_thread_create("network",net_updata_task, NULL,4*512,28, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

