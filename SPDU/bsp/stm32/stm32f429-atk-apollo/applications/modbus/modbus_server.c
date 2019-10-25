/*
 * modbus_trans.c
 *
 *  Created on: 2019年6月11日
 *      Author: luozhiyong
 */
#include "modbus.h"
#include "modbus_server.h"
#include "tcp_server.h"

#define MD_REG_NUM 	32
static modbus_mapping_t *mb_mapping = NULL;
static uchar mb_query[MODBUS_TCP_MAX_ADU_LENGTH];


int mb_tcp_port()
{
	sMdCfg *cfg = mb_cfg_get();
	return cfg->port;
}

int mb_tcp_en()
{
	sMdCfg *cfg = mb_cfg_get();
	return cfg->en;
}


/**
 * 错误返回
 * 功能码 1个字节 请求功能码+0x80
 * 0x01 不支持该功能码
 * 0x02 越界
 * 0x03 寄存器数量超出范围
 * 0x04 读写错误
 */
int mb_reply_exception(modbus_t *ctx, const uchar *req)
{
	return modbus_reply_exception(ctx, req, 4);
}


void mb_entry(modbus_t *ctx, const uchar *req, int rc)
{
	int ret=0, offset = modbus_get_header_length(ctx);
	uchar addr = req[offset - 1]; // 单元标识，和 RTU 的地址是一样的
	uchar function = req[offset]; // 功能码
	ushort reg = (req[offset + 1] << 8) + req[offset + 2]; // 起始寄存器基地址
	const uchar *ptr = &(req[offset+3]);

	switch(function)
	{
	case MODBUS_FC_READ_HOLDING_REGISTERS: // 读 0x03命令
		ret = mb_read_packet(addr, mb_mapping);
		break;

	case MODBUS_FC_WRITE_SINGLE_REGISTER: // 写单个寄存器 0x06命令
		ret = mb_write_reg(addr, reg, FLIPW(ptr));
		break;

	case MODBUS_FC_WRITE_MULTIPLE_REGISTERS: // 写多个寄存器 0x10命令
		ret = mb_write_regs(addr, reg, FLIPW(ptr), ptr);
		break;
	}

	if(ret) {
		modbus_reply(ctx, req, rc, mb_mapping);
	} else {
		mb_reply_exception(ctx, req);
	}
	modbus_flush(ctx);
}

void mb_down_task(void *param)
{
	rt_thread_mdelay(1500);
	modbus_t *ctx = modbus_new_tcp(NULL, 502, AF_INET);
	mb_mapping = modbus_mapping_new(0, 0, 2*MD_REG_NUM, MD_REG_NUM);

	modbus_set_debug(ctx, 0);
	int sock = modbus_tcp_listen(ctx, 1);
	if(sock<0) rt_kprintf("modbus tcp listen err \n");
	while(1) {
		int cs = modbus_tcp_accept(ctx, &sock);
		if(cs<0) { rt_kprintf("modbus tcp accept err \n"); msleep(1); continue;}
		while(1) {
			int rc = modbus_receive(ctx, mb_query);
			if(rc > 0) {
				mb_entry(ctx, mb_query, rc);
			} else {
				closesocket(cs);
				break;
			}
			msleep(1);
		}
	}

	closesocket(sock);
	modbus_close(ctx);
	modbus_free(ctx);
}



void modbus_thread(void)
{
	rt_thread_t tid = rt_thread_create("modbus",mb_down_task, NULL,2*1024,13, 15);
	if (tid != RT_NULL) rt_thread_startup(tid);
}
