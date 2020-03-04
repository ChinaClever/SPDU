/*
 * data_opt.h
 *
 *  Created on: 2019��6��6��
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_OPT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_OPT_H_
#include <board.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h> /* ʹ��BSD socket����Ҫ����sockets.hͷ�ļ� */
#include <easyflash.h>

typedef  unsigned char      boolean;     /* Boolean value type. */
typedef  unsigned int  		uint;      /* Unsigned 32 bit value */
typedef  unsigned long int  ulong;      /* Unsigned 32 bit value */
typedef  unsigned short     ushort;      /* Unsigned 16 bit value */
typedef  unsigned char      uchar;       /* Unsigned 8  bit value */

typedef  unsigned char     byte;         /* Unsigned 8  bit value type. */
typedef  unsigned short    word;         /* Unsinged 16 bit value type. */

// �õ�ָ����ַ�ϵ�һ���ֽڻ���
#define  MEM_B( x )  ( *( (uchar *) (x) ) )
#define  MEM_W( x )  ( *( (ushort *) (x) ) )

//�����ֵ����Сֵ
#define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )

//����LSB��ʽ�������ֽ�ת��Ϊһ��Word
#define  FLIPW( ray ) ( (((word) (ray)[0]) << 8) + (ray)[1] )

// ����LSB��ʽ��һ��Wordת��Ϊ�����ֽ�
#define  FLOPW( ray, val ) \
		(ray)[0] = ((val) / 256); \
		(ray)[1] = ((val) & 0xFF)

// �õ�һ���ֵĸ�λ�͵�λ�ֽ�
#define  WORD_LO(val)  ((byte) ((word)(val) & 255))
#define  WORD_HI(val)  ((byte) ((word)(val) >> 8))

//����һ����X�����ӽ���8�ı���
#define RND8( x )       ((((x) + 7) / 8 ) * 8 )

//��һ����ĸת��Ϊ��д
#define  UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )

//��������Ԫ�صĸ���
#define  ARR_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) )

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#ifndef nullptr
#define nullptr  NULL
#endif

#define usleep(x) rt_hw_us_delay(x)
#define msleep(x) rt_thread_mdelay(x)
#define sleep(x)  msleep(1000*x)

#endif /* BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_OPT_H_ */
