�}: *  ��G7�vC�i    ��}�bw��,�ހ�����H�A����)
˔�������XbbcvK�����¯��XA��XoT��|�����bS{'L�6s�����B��0�A%�q��Pd��]�K~<�7NUΈ�@^��f>�[�[9�����,~�<�8
s���R�g0��S# �l&���CXN���>�s��Y��fږ�ԭ��܌�ɳ@7Yf��,����Y[�R�ّ������dSP8a�1���
Ŧ�[Ds�gad�
��ѣ�	h+9���X��Z�„�/� ���}�����ήݗ��Q��цz��$��d0�X�4MzF�Ǐ�ܫ=�8��l������E�*�.e�R�2��C��R�+���
��mM-�-����<=�=h��<��ˬ�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�4��{�!mؽ��ӊ�&#��Ws��YE;�v�A��U��h'ޜx_�z�oi�}���;ӐYu�1۩���r�F�(��&���i���EIR���)�v�����#/q��kC�5E�m=�*}�}�(#����*��=���R7��8�F�4�Ə]���+����1�����r?i`�o{~.9X��!N��"tl���+<#��w�ՠ�/��GȢ��^T�=�@�MA�(d\$Έ�ɺv�>�������t���
$�T�������{�����D���:{�����D�2S(�A�l�ۚ�O� �[ڞ�g����7>�U�ώ����ʹVsѪΜr����Y��$�xk��b��D:���1y�����7�$���=�>Ԭ���
ז;�R|�1�$]ט[JJ+Ѣ�%7�%��M|9$� ��G�����?��d��ېrbb[+-�x�h��-�2.��i��k|���{R�O���r�����aQ�L��/
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return RT_ERROR;
    }
    /* ���ÿ��Ź����ʱ�� */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }
    /* ���ÿ����̻߳ص����� */
    rt_thread_idle_sethook(idle_hook);

    return ret;
}




