/*
 * aes.c
 * 高级加密标准（Advanced Encryption Standard: AES）是美国国家标准与技术研究院（NIST）
 * 在2001年建立了电子数据的加密规范。
 * 其是对称加解密算法的最经典算法之一，它是一种分组加密标准，
 * 每个加密块大小为128位，允许的密钥长度为128、192和256位。这里只介绍ECB、CBC、CFB和OFB四种加密模式。
 *
 *  Created on: 2019年11月5日
 *      Author: luozhiyong
 */
#include <rtthread.h>
#ifdef TINY_CRYPT_AES
#include <tiny_aes.h>
#include <stdlib.h>

typedef unsigned char uchar;

/**
 * ECB模式又称电子密码本模式（Electronic codebook）：
 * ECB是最简单的块密码加密模式，加密前根据加密块大小（如AES为128位）分成若干块，
 * 之后将每块使用相同的密钥单独加密，解密同理。
 *
 * ECB模式由于每块数据的加密是独立的因此加密和解密都可以并行计算，
 * ECB模式最大的缺点是相同的明文块会被加密成相同的密文块，这种方法在某些环境下不能提供严格的数据保密性。
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
 * aes 加密
 * CBC模式又称密码分组链接（Cipher-block chaining）：
 * CBC模式对于每个待加密的密码块在加密前会先与前一个密码块的密文异或然后再用加密器加密。
 * 第一个明文块与一个叫初始化向量的数据块异或。
 *
 * AES_cbc_encrypt允许length不是16(128位)的整数倍，不足的部分会用0填充，输出总是16的整数倍。
 * 完成加密或解密后会更新初始化向量IV。CBC模式相比ECB有更高的保密性，
 * 但由于对每个数据块的加密依赖与前一个数据块的加密所以加密无法并行。
 * 与ECB一样在加密前需要对数据进行填充，不是很适合对流数据进行加密。
 */
void aes_cbc_encrypt(uchar *iv, uchar *private_key, uchar *data, uchar *data_encrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_enc(&ctx, private_key, 256);
	tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, rt_strlen((const char *)data), iv, data, data_encrypt);
}

// aes 解密
void aes_cbc_decrypt(uchar *iv, uchar *private_key, uchar len, uchar *data_encrypt, uchar *data_decrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_dec(&ctx, private_key, 256);
	tiny_aes_crypt_cbc(&ctx, AES_DECRYPT, len, iv, data_encrypt, data_decrypt);
}

/**
 * OFB模式又称输出反馈模式（Output feedback）：
 * OFB是先用块加密器生成密钥流（Keystream），然后再将密钥流与明文流异或得到密文流，
 * 解密是先用块加密器生成密钥流，再将密钥流与密文流异或得到明文，
 * 由于异或操作的对称性所以加密和解密的流程是完全一样的。
 *
 * OFB与CFB一样都非常适合对流数据的加密，OFB由于加密和解密都依赖与前一段数据，所以加密和解密都不能并行。
 */
void aes_cfb_encrypt(int *iv_off, uchar *iv, uchar *private_key, uchar *data, uchar *data_encrypt)
{
	tiny_aes_context ctx;

	tiny_aes_setkey_enc(&ctx, private_key, 128);
	tiny_aes_crypt_cfb128(&ctx, AES_ENCRYPT, rt_strlen((const char *)data), iv_off, iv, data, data_encrypt);
}

// aes 解密
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
