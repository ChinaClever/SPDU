/*
 * modbus_trans.c
 *
 *  Created on: 2019年6月11日
 *      Author: luozhiyong
 */
#include "modbus.h"
#include "modbus_server.h"

#define RS485_RE GET_PIN(G, 8)

#define MD_REG_NUM 	32
static modbus_mapping_t *mb_mapping = NULL;
static uint8_t mb_query[MODBUS_TCP_MAX_ADU_LENGTH/2];

modbus_t *mb_tcp_init(int port)
{
	static int s = 0;
	static modbus_t *ctx = NULL;

	if(ctx == NULL) {
		ctx = modbus_new_tcp(NULL, port);
		modbus_set_debug(ctx, FALSE);
		s = modbus_tcp_listen(ctx, 1);
	}
	modbus_tcp_accept(ctx, &s);

	return ctx;
}


modbus_t *mb_init(void)
{
	modbus_t *ctx = NULL;
	struct sMdCfg *md = mb_cfg_get();

	if(md->en) {
		ctx = mb_tcp_init(md->port); // 502
	}

	return ctx;
}

void mb_deinit(modbus_t *ctx)
{
	modbus_close(ctx);
	modbus_free(ctx);
}

// 写入
void mb_write_entry(modbus_t *ctx, const uint8_t *req, int rc)
{
	int offset = modbus_get_header_length(ctx);
	int slave = req[offset - 1]; // 单元标识，和 RTU 的地址是一样的
	int function = req[offset]; // 功能码
	ushort reg = (req[offset + 1] << 8) + req[offset + 2]; // 起始寄存器基地址
	const uchar *ptr = &(req[offset+3]);
	ushort i, value, num=FLIPW(ptr);

	if(function == MODBUS_FC_WRITE_MULTIPLE_REGISTERS)
	{
		if((rc-offset) > 5) { // 写多个寄存器请求
			ptr++;
			for(i=0; i<num; ++i) {
				ptr += 2;
				value = FLIPW(ptr);
				//sw_pin_write(reg+i, value);
				mb_mapping->tab_registers[reg+i] = value;
				//printf("Write reg=%d  v=%d \n", reg+i, value);
			}
		} else { // 写单个寄存器请求
			value = FLIPW(ptr);
			//sw_pin_write(reg, value);
			mb_mapping->tab_registers[reg] = value;
			//printf("Write reg=%d  v=%d \n", reg, value);
		}
	}
}

void mb_down_task(void *param)
{
	int i, rc=0;
	modbus_t *ctx = mb_init();
	struct sMdCfg *md = mb_cfg_get();
	mb_mapping = modbus_mapping_new(0, 0, 2*MD_REG_NUM, 2*MD_REG_NUM);

	while(1) {
		if(md->en)
		{
			rc = modbus_receive(ctx, mb_query);
			if (rc > 0) {
				mb_write_entry(ctx, mb_query, rc);
				modbus_reply(ctx, mb_query, rc, mb_mapping);
				modbus_flush(ctx);
			} else if (rc  == -1) {
				// mb_deinit(ctx);
				ctx = mb_init();
			}
		}
		msleep(1);
	}
}

void mb_updata_task(void *arg)
{
	uchar i;
	while(1) {
		if(mb_mapping) {
			for(i=0; i<MD_REG_NUM; ++i) {
				//mb_mapping->tab_registers[i] = getSwStatus(i);
			}
		}
		msleep(500);
	}
}


void modbus_thread(void)
{
	rt_thread_t tid = rt_thread_create("mb_rec",mb_down_task, NULL,3*512,8, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);

	tid = rt_thread_create("mb_pub",mb_updata_task, NULL,216,14, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
