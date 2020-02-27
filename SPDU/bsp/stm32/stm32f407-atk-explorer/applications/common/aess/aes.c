/*
 * aes.c
 * �߼����ܱ�׼��Advanced Encryption Standard: AES�����������ұ�׼�뼼���о�Ժ��NIST��
 * ��2001�꽨���˵������ݵļ��ܹ淶��
 * ���ǶԳƼӽ����㷨������㷨֮һ������һ�ַ�����ܱ�׼��
 * ÿ�����ܿ��СΪ128λ���������Կ����Ϊ128��192��256λ������ֻ����ECB��CBC��CFB��OFB���ּ���ģʽ��
 *
 *  Created on: 2019��11��5��
 *      Author: luozhiyong
 */
#include <rtthread.h>
#ifdef TINY_CRYPT_AES
#include <tiny_aes.h>
#include <stdlib.h>

typedef unsigned char uchar;

/**
 * ECBģʽ�ֳƵ������뱾ģʽ��Electronic codebook����
 * ECB����򵥵Ŀ��������ģʽ������ǰ���ݼ��ܿ��С����AESΪ128λ���ֳ����ɿ飬
 * ֮��ÿ��ʹ����ͬ����Կ�������ܣ�����ͬ��
 *
 * ECBģʽ����ÿ�����ݵļ����Ƕ�������˼��ܺͽ��ܶ����Բ��м��㣬
 * ECBģʽ����ȱ������ͬ�����Ŀ�ᱻ���ܳ���ͬ�����Ŀ飬���ַ�����ĳЩ�����²����ṩ�ϸ�����ݱ����ԡ�
 */
void aes_ecb_encrypt(uchar *private_key, uchar *data, uchar *data_encrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_enc(&ctx, private_key, 128);
	tiny_aes_crypt_ecb(&ctx, AES_ENCRYPT, data, data_encrypt);
}

void aes_ecb_decrypt(uchar *private_key, uchar *data_encrypt, uchar *data_decrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_dec(&ctx, (uchar *) private_key, 128);
	tiny_aes_crypt_ecb(&ctx, AES_DECRYPT, data_encrypt, data_decrypt);
}



/**
 * aes ����
 * CBCģʽ�ֳ�����������ӣ�Cipher-block chaining����
 * CBCģʽ����ÿ�������ܵ�������ڼ���ǰ������ǰһ���������������Ȼ�����ü��������ܡ�
 * ��һ�����Ŀ���һ���г�ʼ�����������ݿ����
 *
 * AES_cbc_encrypt����length����16(128λ)��������������Ĳ��ֻ���0��䣬�������16����������
 * ��ɼ��ܻ���ܺ����³�ʼ������IV��CBCģʽ���ECB�и��ߵı����ԣ�
 * �����ڶ�ÿ�����ݿ�ļ���������ǰһ�����ݿ�ļ������Լ����޷����С�
 * ��ECBһ���ڼ���ǰ��Ҫ�����ݽ�����䣬���Ǻ��ʺ϶������ݽ��м��ܡ�
 */
void aes_cbc_encrypt(uchar *iv, uchar *private_key, uchar *data, uchar *data_encrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_enc(&ctx, private_key, 256);
	tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, rt_strlen((const char *)data), iv, data, data_encrypt);
}

// aes ����
void aes_cbc_decrypt(uchar *iv, uchar *private_key, uchar len, uchar *data_encrypt, uchar *data_decrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_dec(&ctx, private_key, 256);
	tiny_aes_crypt_cbc(&ctx, AES_DECRYPT, len, iv, data_encrypt, data_decrypt);
}

/**
 * OFBģʽ�ֳ��������ģʽ��Output feedback����
 * OFB�����ÿ������������Կ����Keystream����Ȼ���ٽ���Կ�������������õ���������
 * ���������ÿ������������Կ�����ٽ���Կ�������������õ����ģ�
 * �����������ĶԳ������Լ��ܺͽ��ܵ���������ȫһ���ġ�
 *
 * OFB��CFBһ�����ǳ��ʺ϶������ݵļ��ܣ�OFB���ڼ��ܺͽ��ܶ�������ǰһ�����ݣ����Լ��ܺͽ��ܶ����ܲ��С�
 */
void aes_cfb_encrypt(int *iv_off, uchar *iv, uchar *private_key, uchar *data, uchar *data_encrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_enc(&ctx, private_key, 128);
	tiny_aes_crypt_cfb128(&ctx, AES_ENCRYPT, rt_strlen((const char *)data), iv_off, iv, data, data_encrypt);
}

// aes ����
void aes_cfb_decrypt(int *iv_off, uchar *iv, uchar *private_key, uchar len, uchar *data_encrypt, uchar *data_decrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_dec(&ctx, private_key, 128);
	tiny_aes_crypt_cfb128(&ctx, AES_DECRYPT, len, iv_off, iv, data_encrypt, data_decrypt);}


#define TEST_TINY_AES_IV  "0123456789ABCDEF"
#define TEST_TINY_AES_KEY "0123456789ABCDEF0123456789ABCDEF"

void aes_encrypt_test(uchar *data, uchar *data_encrypt)
{
	uchar iv[16 + 1];
	uchar private_key[32 + 1];
//	uchar data_encrypt[32];
//	uchar data_decrypt[32];

	/* encrypt */
	rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
	iv[sizeof(iv) - 1] = '\0';
	rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
	private_key[sizeof(private_key) - 1] = '\0';

	rt_memset(data_encrypt, 0x0, sizeof(data_encrypt));
	aes_cbc_encrypt(iv, private_key, data, data_encrypt);
}


void aes_decrypt_test(uchar len, uchar *data_encrypt, uchar *data_decrypt)
{
	uchar iv[16 + 1];
	uchar private_key[32 + 1];

	rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
	iv[sizeof(iv) - 1] = '\0';
	rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
	private_key[sizeof(private_key) - 1] = '\0';

	//rt_memset(data_decrypt, 0x0, sizeof(data_decrypt));
	aes_cbc_decrypt(iv, private_key, len, data_encrypt, data_decrypt);
}


void aes_test()
{
    unsigned char data[] = "1234567890123456";
    unsigned char data_encrypt[32] = {0};
    unsigned char data_decrypt[32] = {0};

    aes_encrypt_test(data, data_encrypt);

    uchar len = rt_strlen((const char *)data);
    aes_decrypt_test(len, data_encrypt, data_decrypt);

    if(rt_memcmp(data, data_decrypt, len) == 0) {
    	rt_kprintf("AES CBC mode passed!\n");
    } else {
    	rt_kprintf("AES CBC mode failed!");
    }
}

#endif
