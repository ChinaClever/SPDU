�}j �  ���vKC$bU��u
��w�b��F^����5HJ\�X�KNs6@����͈�ȿoD��V�h:B� v\�!'S���p0ā���*̝�C^��B��;�z�c-ZT�N)�j'd���$
�^s?k-��~T�C���2=��Η�����3 �T?YX�֟�56gR:���M �BL&����R��}�R&h�k�V�M��HKW���yn�ѧ�@��򔋎 ��k̢�!vƮ�\�ɴg�|u '"�wRD	��x�l{���%�XɏԀ"����ONh�?&d7�T�.�
�� ^�(���+�̉fٗ�wGgSG�7���� �}EZC�)��#�'/e�,���w�V�>2:d�M�DO��L��>M��^��@X�kط=�������=��k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l� �$�BΑ�L1�G�%��x�?�h%w�`\��6����W�����ac*����U� Qb���2�shP��v�Vi������2G~��=�w��VwcWO��*�#/�IJWAa����9S6YX[<v�Nf�<�漚����-���V�6�-}��~"�� �v�m�H3,d3{�����d�'�GGҋi�$]#��Qq�]�pY���w��� =��o++�q���?�Y->����ѵXA&�ޟ"J�Ɠ�V��+x��^��n(.�OYG>IW�Q"��I8� n�<�p������#>ױ)!�����.e���@;s⺉Ej�ǒyVA�q�<{L�g�Aȑ=���'>���� �(�����{��B+N�h�ޒ5�p QCz%F:v�<_4KΏI4�5��D���q���)�r�\�6w�͏��|��d�>Ь�SN[�)�$$��*�F'Ot�fN��>�y���Ft��"��Vy��0��}AG�A_�30������-V�vice port
    };

    if (lssdp_service_add(&service) != 0)
    {
        printf("service %s add failed!", service.name);
    }

    return RT_EOK;
}


int ssdp_service_del(void)
{
    struct lssdp_service service = {
        .name = "service name",
    };

    lssdp_service_del(&service);

    return RT_EOK;
}
