�}� �  �vD!;D�또�u
��_�b���GNƇ�on�*G��9�Hϓ?P1�����a�M/�ˠ�.5�-(�#V�,Ҡ��{'3q��67��t���!Z����7�(�W����_P�:��FI|�;I�YX ���b>�"�ݥ;E3�ta�����/e�h�qS���l�^IY$�<w����~��@).�1�9M�7S~�S��p�K����p�/|���c��"++� ��AJ7SB�Dj߈fer5mצT��kg�4��P�s~�*O��X�*�Wu%��95It��DHi++>�_&[
ؗf:Ӫ�AK�1h�ɇ�\�ZWX�4���sX�y�@:}[����
q�8��#�t������z h��k�,s�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���lD-���Ctڌ'�n�}ᚢ�|F�l*�i�B߶^�3\�H{�ӀoWJ�:�8!��.�g��{�9Ň"�d�33T��Z����\JX'���Tİ�g|�q�VMd���`�@x͙"j���* ���Πq�}m��x ?9�b 1�ܥέY���mGf�nC��Y�>ֹ�l��1L�Drȹa9(���?���4�I�R�v��H��ҧ�Ż�)������`�j�8��wϪ��}yW��0t,J��>�2��+F�͆;����tZK�-���6KP1��GM��8G�ʖ7۩�K�-Ţ��A��^غ�DFu�S�'�a��W�M ���i��o!p���Y��hG�R�cO1 ��ӁÉ�@���zɁ u>�w��Բ�Z>��P���:Ƌ੘Bd��̔���h��6��e�����f�9��)�Q�q�:��݋�ʏ茌/���؁_g)t��k���l4zX��J]�Yk��}?JuO[�t�>�#�*��{}��7l2�:Z�ج����oF�Ү��+�~�Q"��ºwSoS
�3�����7�����/}����	���D&�"Y�8>344:�k�+uE��P�?�q���zLt���2����['���4�{�TyhS2dbb%�5�_z:�`H����}�b�<U���j����:��䏵r՚f�[n���~e$�?� b��J!�v�XRVTZ��� ���qk�iվ��K�{.���1w���ߩ���ގ�3j��z�ӼA�kMv��jL��M�}8v[�RǷ�p^"}�	RЗ��Rg1���s���Z����?�_����@N����e��@���2d5!;˽��<�X
ڴ�NZ֣���.����2\�����堀x���&����e��pGMU�S�i䵽5+��~/�e��ɪC!���-�C�<�y��`Y�8�����$8��@rB�Thٟo�0m�:!% �Y���ɾ _��Ir��	��\O����3<�%p_time();

	webnet_cgi_register("getDevNum", web_dev_num);
	webnet_cgi_register("getVersion", web_dev_version);
	webnet_cgi_register("reset", web_dev_reset);

	webnet_init();
}

static int web_init_thread(void)
{
    rt_thread_t thread = rt_thread_create("web_init", web_main_entry, NULL, 2*1024, 3, 5);
    if (thread != RT_NULL)  rt_thread_startup(thread);
    return 0;
}

//INIT_ENV_EXPORT(web_init_thread);
