/*
 * modbus_trans.c
 *
 *  Created on: 2019年6月11日
 *      Author: luozhiyong
 */
#include "modbus_server.h"

#define RS485_RE GET_PIN(G, 8)

#define MD_REG_NUM 	OUTPUT_NUM_MAX
static modbus_mapping_t *mb_mapping = NULL;
static uint8_t mb_query[MODBUS_TCP_MAX_ADU_LENGTH/2];

modbus_t *mb_tcp_init(int port)
{
	char *ip = "127.0.0.1";
	modbus_t *ctx = modbus_new_tcp(ip, port);
	modbus_set_debug(ctx, TRUE);
	int s = modbus_tcp_listen(ctx, 1);
	modbus_tcp_accept(ctx, &s);

	return ctx;
}

modbus_t *mb_rtu_init(int addr)
{
	modbus_t *ctx = ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
	modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
	modbus_rtu_set_rts(ctx, RS485_RE, MODBUS_RTU_RTS_UP);
	modbus_set_slave(ctx, addr);
	modbus_connect(ctx);

	return ctx;
}

modbus_t *mb_init(void)
{
	int id = 0; ////===== 连接模块

	modbus_t *ctx = NULL;
	if(id) {
		ctx = mb_rtu_init(3);
	} else {
		ctx = mb_tcp_init(502);
	}

	return ctx;
}

void mb_deinit(modbus_t *ctx)
{
	modbus_close(ctx);
	modbus_free(ctx);
}

// 写入
boolean mb_write_entry(void)
{
	boolean ret = true;
	int i, v, id = mb_mapping->start_input_registers;
	int nb = mb_mapping->nb_input_registers - mb_mapping->start_input_registers;
	if(nb > 0) {
		for(i=0; i<nb; ++i) {
			v = mb_mapping->tab_input_registers[i];
			setSwStatus(id+i, v);
		}
	} else {
		ret = false;
	}

	return ret;
}

void mb_down_task(void *param)
{
	int rc=0;
	modbus_t *ctx = mb_init();
	mb_mapping = modbus_mapping_new(0, 0, MD_REG_NUM, MD_REG_NUM);

	while(1) {
		rc = modbus_receive(ctx, mb_query);
		if (rc > 0) {
			if(!mb_write_entry()) {
				modbus_reply(ctx, mb_query, rc, mb_mapping);
			}
		} else if (rc  == -1) {
			mb_deinit(ctx);
			ctx = mb_init();
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
				mb_mapping->tab_registers[i] = getSwStatus(i);
			}
			sleep(1);
		}
	}
}

void mb_thread_pool(void)
{
	uchar i;
	thread_pool pool;

	init_thread_pool(&pool, "modbus", 2, 256);
	pool.add_task(&pool, mb_down_task, NULL);
	pool.add_task(&pool, mb_updata_task, NULL);
}
