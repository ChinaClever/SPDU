�}. 5 ��n�,�z��u
��H�b���FN�>�50<\�J��|/���[fg���t:�h]�G��wk��&�ךWI����C�|!%�w��a���9�<� I��	�*;	nN�������zK��G�Wd�����U�W߯������`��;+����ߨ���K}�dEp��O���j�W+�H��K��;7ϕT�#$f`��eN�,6�,���t]�2��x񶠷!�H]���=�)�`Jh'c]H���P������T�o(v�ƞ#�wh ���^$+�Z~�Ë��-�,�
�@�y�ux=����ò�������B�U��֭��ID4"�:�ԡ�eq��m�ww�y;���rۏ�k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�+���m�u��WX��*Xh4RQ��A}cμ?�
��:��5�H�Tf�-�qbF��'N�kE��(��珁x\����_�x�ɘ�3ȿڧ�hp��m~0u��_�4|��20%)-�Y�ʉ�˂Zc�=�HF�(S���Z�Y�lG����$��]_+c�-��v�	��e�Q����s�a5_6V�"�7�e:^�-�vk�C��wkb���!Ԧ�'��1fAD�PA���@�	�U����nfR�5�$�,��ʹj��s��o0�[��_��R{�%va_`C�ycc�n��l�._�k�s����d+��c3��켮�����),�eѥ�	"��3�֙a$8;����>ɭVS��Wx~a*t�P̪](R!�p�B�V��O�UD����o�Hs�����?����	g������Ə��[O$,�泒���x��1X�_;��F;o�����:���Y�x+��o��Hᦕ!ӊf���.ܡGm&��y�X�)�s)���s�hCl�)��Rq�6��9��S߁j9t���W�֐��f�ɥPi�խ�9��Q?N�z��������0��V.�5���yCr�#��0��߻A<���a��)kz[-<P��m���^ϋ�r��|n��%u;t�˵kk�q���v��$���a�7�Aѩ���?����Sѫ��r��� ��Eӳ{� b��M�ĉ�$6c���~��!���m���pj ��O��fh��XFk���:#�6[�p\�qp�)��w�J+m_s�4<̠!ȿ�W��
�����.G�hR\�l]+�~V�u^�9u!+������\�i�?N@9+��1˴��c^H�#$�д�ڇ*4GzR��޸��s13i����"��O�a6绝����I�57�4��=�g�	G��&o��O�������6��=b�\N�_v��֍���?c�V��5�m�ʳ[*�Uk7h:�o��!;��f��28��+�gL�K�^�1��j�񗡬��T.�|��V1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
