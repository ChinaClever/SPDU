�}� 8  �⽲:�Q�`��u
��d�b	�{�GN�|��P������MK��ɊX�����C`H<�5�����w+G��Ռ�x���q�-t�zן[P��](�_Ww��{1��q)a�w���zF�@\Ρ��ce��@#����_ŋ��م~����:c�|�
�������kO�۳&L%��D�)�ԥ�m�!0i]�-m��q�s�[6����L�L��D�sF��y�ķ��h�$<�"�CeJGk"�fxӼ.8� �f �qu\,)�6�6d���'���+�Ώ�3��I �:W�&�<H7a� ����!L/<�vu'O$N�[�*$"0��F]z�yY��9�����t�l�H�|��v���k\@$�;�yݵ�Yws�ϲ�+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j���l�-h�тC��� 1����2b��&*	�}ȉS��ۈ����V�:!^��Œ�y��Қ5Mp�`�m~է;
��Y���]Hs�[֦�[�ц"��P@k/�!cxx����o{9�'/z�$&gq(��̛�O$�_ҩ}��.Y�^�ylP;~�5������n�����_BI��,�w%�����L8�]t����qE�Q��U]S{��?��YH�5%��ꑲ�|����(��*��gOXj�l�{ڒ(���ng�.�S��x'�<�J�|L��y�W1:Zn`�x���D]N��^|q'ӄ%��.D�2�Z���pUp<`8iD!��e�P.T���#�- `[|0�1E[�Qzܯ^d�P��3p!�����n��"�s>T-�iG���s��rm����YSb�_�+�"�2�x�Q���������L�R�s�iA��H=�lp|t�̈��^x/�Zo�%�zS]J���.j�G��B m�s0�q��E^Bml"�"��#���L�"B��Z+Mily, Cycle, Once, Ats};

uchar getDelaytm(void);
void setDelaytm(uchar tm);

int getOutputNum(void);
struct sSwItem *getSwItem(int id);
struct sTitem *getSequence(void);

boolean setSwStatus(int pin, int v);
void setAllSwStatus(int v);
int getSwStatus(int pin);

boolean setInitialStatus(int pin, int v);
void setAllInitialStatus(int v);
int getInitialStatus(int pin);

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_PACKET_H_ */
