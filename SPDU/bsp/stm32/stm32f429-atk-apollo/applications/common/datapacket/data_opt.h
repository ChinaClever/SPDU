/*
 * data_opt.h
 *
 *  Created on: 2019年6月6日
 *      Author: luozhiyong
 */

#ifndef BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_OPT_H_
#define BSP_STM32_STM32F407_ATK_EXPLORER_APPLICATIONS_PACKET_DATA_OPT_H_
#include <board.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h> /* 使用BSD socket，需要包含sockets.h头文件 */
#include <easyflash.h>

typedef  unsigned char      boolean;     /* Boolean value type. */
typedef  unsigned int  		uint;      /* Unsigned 32 bit value */
typedef  unsigned long int  ulong;      /* Unsigned 32 bit value */
typedef  unsigned short     ushort;      /* Unsigned 16 bit value */
typedef  unsigned char      uchar;       /* Unsigned 8  bit value */

typedef  unsigned char     byte;         /* Unsigned 8  bit value type. */
typedef  unsigned short    word;         /* Unsinged 16 bit value type. */

// 得到指定地址上的一个字节或字
#define  MEM_B( x )  ( *( (uchar *) (x) ) )
#define  MEM_W( x )  ( *( (ushort *) (x) ) )

//求最大值和最小值
#define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )

//按照LSB格式把两个字节转化为一个Word
#define  FLIPW( ray ) ( (((word) (ray)[0]) << 8) + (ray)[1] )

// 按照LSB格式把一个Word转化为两个字节
#define  FLOPW( ray, val ) \
		(ray)[0] = ((val) / 256); \
		(ray)[1] = ((val) & 0xFF)

// 得到一个字的高位和低位字节
#define  WORD_LO(val)  ((byte) ((word)(val) & 255))
#define  WORD_HI(val)  ((byte) ((word)(val) >> 8))

//返回一个比X大的最接近的8的倍数
#define RND8( x )       ((((x) + 7) / 8 ) * 8 )

//将一个字母转换为大写
#define  UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )

//返回数组元素的个数
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
