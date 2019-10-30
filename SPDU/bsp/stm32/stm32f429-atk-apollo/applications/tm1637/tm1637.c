#include "TM1637.h"

struct sTm{
	char hour; // 时
	char min; // 分
	char sec; // 秒
};

//DIO和CLK相关引脚的宏定义，用户只需要修改相关宏即可
#define    TM_DIO_PIN		GET_PIN(C, 2)
#define    TM_CLK_PIN		GET_PIN(C, 3)

//时钟线和数据线高低电平的宏定义，不需修改
#define      CLK_1        rt_pin_write(TM_CLK_PIN, PIN_HIGH)
#define      CLK_0        rt_pin_write(TM_CLK_PIN, PIN_LOW)
#define      DIO_1        rt_pin_write(TM_DIO_PIN, PIN_HIGH)
#define      DIO_0        rt_pin_write(TM_DIO_PIN, PIN_LOW)

static unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};

/*
 *@breif GPIO_INIT
 *@note  no
 */
void TM_GPIO_Config(void)
{
	rt_pin_mode(TM_DIO_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(TM_CLK_PIN, PIN_MODE_OUTPUT);
}

static void TM_delay(void)
{
	rt_hw_us_delay(1);
}

/*时钟线为高时，数据线由高变低*/
static void I2C_Start(void)
{
	CLK_1;
	DIO_1;
	TM_delay();

	DIO_0;
	TM_delay();
	CLK_0;
	TM_delay();
}


/*
 *时钟线为高时，数据线由低变高
 */
static void I2C_stop(void)
{

	CLK_0;
	TM_delay();
	DIO_0;
	TM_delay();

	CLK_1;
	TM_delay();
	DIO_1;
	TM_delay();
}


//写一个比特位
static void TM1637_WriteBit(unsigned char mBit)
{
	CLK_0;
	TM_delay();

	if(mBit)
		DIO_1;
	else
		DIO_0;

	TM_delay();
	CLK_1;
	TM_delay();
}


//写一个字节    
static void TM1637_WriteByte(unsigned char Byte)
{
	char loop = 0;
	for(loop = 0;loop<8;loop++)
	{
		TM1637_WriteBit((Byte>>loop) & 0x01);//先写低位
	}
	CLK_0;
	TM_delay();
	DIO_1;	
	TM_delay();
	CLK_1;		
	TM_delay();
	//rt_thread_mdelay(1); //等待应答信号
	//	while(rt_pin_read(TM_DIO_PIN) == 1);
	//	while(GPIO_ReadInputDataBit(TM_DIO_PORT ,TM_DIO_PIN) == 0x01);
}

/*
 *写指令函数
 *B7:B6 =01  数据命令控制
 *            11地址命令控制
 *            10显示命令控制
 */

static void TM1637_WriteCommand(unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(mData);
	I2C_stop();
}


/*
 *@note  写入地址和数据
 */

static void TM1637_WriteData(unsigned char addr,unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(addr);
	TM1637_WriteByte(mData);
	I2C_stop();
}




/*
控制显示，配置好数据结构体之后，直接调用该函数就可以显示
 */
void TM1637_TimeDisplay(struct sTm *tm)
{
	TM1637_WriteCommand(0x44);
	TM1637_WriteData(0xc0,Data[tm->hour/10]);
	if(tm->sec%2) {
		TM1637_WriteData(0xc1,Data[tm->hour%10]);
	} else {
		TM1637_WriteData(0xc1,DataDp[tm->hour%10]);
	}

	TM1637_WriteData(0xc2, Data[tm->min/10]);
	TM1637_WriteData(0xc3, Data[tm->min%10]);
	TM1637_WriteCommand(0x8a);
}

void TM_TimeDisplay(void)
{
	time_t t;
	time (&t);//获取Unix时间戳。
	struct tm *lt = localtime (&t);//转为时间结构。

	static struct sTm tm;
	tm.hour = lt->tm_hour;
	tm.min = lt->tm_min;
	tm.sec = lt->tm_sec;

	TM1637_TimeDisplay(&tm);
}

void TM_Display(int value)
{
	int len = 4;
	if(value<10) len = 1;
	if(value<100) len = 2;
	if(value<100) len = 3;

	TM1637_WriteCommand(0x44);
	switch(len) {
	case 4: TM1637_WriteData(0xc0, Data[value/1000%10]);
	case 3: TM1637_WriteData(0xc1, Data[value/100%10]);
	case 2: TM1637_WriteData(0xc2, Data[value/10%10]);
	case 1: TM1637_WriteData(0xc3, Data[value%10]); break;
	}
	TM1637_WriteCommand(0x8a);
}

