/*
 * http_client.c
 *
 *  Created on: 2019Äê6ÔÂ12ÈÕ
 *      Author: luozhiyong
 */

#include <webclient.h>
#include "http_client.h"

#define GET_LOCAL_URI                  "http://www.rt-thread.com/service/rt-thread.txt"
#define POST_LOCAL_URI                 "http://www.rt-thread.com/service/echo"

void http_post_resp(char *request)
{
	int index;
	rt_kprintf("webclient send post request by simplify request interface.\n");
	rt_kprintf("webclient post response data: \n");

	for (index = 0; index < rt_strlen(request); index++)
	{
		rt_kprintf("%c", request[index]);
	}
	rt_kprintf("\n");

	if (request) web_free(request);
}

int http_post(char *uri, char *post_data, char *head)
{
	char *url = web_strdup(uri);
	//char *url = web_strdup(POST_LOCAL_URI);
	char *request=RT_NULL, *header=RT_NULL;

	webclient_request_header_add(&header, "Content-Length: %d\r\n", strlen(post_data));
	if(head) {
		webclient_request_header_add(&header, head);
	} else {
		webclient_request_header_add(&header, "Content-Type: application/octet-stream\r\n");
	}
	int ret = webclient_request(url, (const char *)header, post_data, (unsigned char **)&request);
	if(ret < 0) {
		rt_kprintf("webclient send post request failed.");
		web_free(header);
		return -RT_ERROR;
	} else {
		http_post_resp(request);
	}

	if (url) web_free(url);
	if (header) web_free(header);

	return true;
}

void http_get_resp(char *request)
{
	int index;
	rt_kprintf("webclient send get request by simplify request interface.\n");
	rt_kprintf("webclient get response data: \n");

	for (index = 0; index < rt_strlen(request); index++)
	{
		rt_kprintf("%c", request[index]);
	}
	rt_kprintf("\n");

	if (request) {
		web_free(request);
	}
}

int http_get(char *uri)
{
	char *request = RT_NULL;
	char *url = web_strdup(uri);
	//char *url = web_strdup(GET_LOCAL_URI);

	int ret = webclient_request(url, RT_NULL, RT_NULL, (unsigned char **)&request);
	if (ret > 0) {
		http_get_resp(request);
		//json_analysis(request);
	} else {
		rt_kprintf("webclient send get request failed.");
	}

	web_free(url);

	return ret;
}


