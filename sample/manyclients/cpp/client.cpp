/***************************************************************************
 * 
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/



/**
 * @file client.cpp
 * @author liuxupeng(liuxupeng@baidu.com)
 * @date 2012/3/23 16:23:12
 * @version $Revision$ 
 * @brief demo client
 *  
 **/

#include <iostream>
#include <iomanip>
#include <limits.h>

#include <bgcc.h>
using namespace bgcc;

#include <manyclients.h>
using namespace manyclients;

int main(int argc, char* argv[])
{

	log_open("client.conf");
	ServerInfo serverInfo("localhost", 8321);

	if (argc < 2) {
		fprintf(stderr, "Usage: %s count\n", argv[0]);
		return -1;
	}

	int count = atoi(argv[1]);

	ManyClientsProxy** proxys = (ManyClientsProxy**)malloc(sizeof(ManyClientsProxy*) * count);

	if (proxys == NULL) {
		BGCC_WARN("bgcc", "Malloc proxys array failed");
		return -1;
	}

	for (int i = 0; i < count; ++i) {
		proxys[i] = new(std::nothrow) ManyClientsProxy(serverInfo, 1);
		if (proxys[i] == NULL) {
			BGCC_WARN("bgcc", "New Mathproxy: %d failed", i);

			while (--i >= 0) {
				delete proxys[i];
			}

			free(proxys);

			return -1;
		}

		proxys[i]->ping();

		if (proxys[i]->get_errno() != 0) {
			std::cerr << "Call proxy.ping failed " << i << std::endl;
			return 0;
		} else {
			std::cerr << "Call proxy.ping success " << i << std::endl;
		}
	}

	bgcc::TimeUtil::safe_sleep_s(1000);

	for (int i = 0; i < count; ++i) {
		delete proxys[i];
	}

	free(proxys);

	return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
