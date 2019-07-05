/*
 * ntp_cfg.c
 *
 *  Created on: 2019年7月4日
 *      Author: luozhiyong
 */
#include "ntp_cfg.h"


void ntp_datetime_get(char* ptime)
{
	time_t t;
	time(&t);//获取Unix时间戳。
	dt_datetimeToStr(t, ptime);
}


void ntp_datetime_set(const char *str_time)
{
	time_t cur_time = dt_strToDatetime(str_time);
	struct tm *cur_tm = localtime(&cur_time);

	set_time(cur_tm->tm_hour, cur_tm->tm_min, cur_tm->tm_sec);
	set_date(cur_tm->tm_year + 1900, cur_tm->tm_mon + 1, cur_tm->tm_mday);
}

