/***************************************************************************
 * 
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/

/**
 * @file client.cpp
 * @author
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s nproxy [internal_ms]\n", argv[0]);
        return -1;
    }

    log_open("client.conf");
    ServerInfo serverInfo("localhost", 8321);

    int nproxy = atoi(argv[1]);
    int internal_ms = 1000;
    if (argv[2]) {
        internal_ms = atoi(argv[2]);
    }

    ManyClientsProxy** proxys = (ManyClientsProxy**)malloc(sizeof(ManyClientsProxy*) * nproxy);
    if (proxys == NULL) {
        BGCC_WARN("bgcc", "Malloc proxys array failed");
        return -1;
    }

    for (int i = 0; i < nproxy; ++i) {
        proxys[i] = new(std::nothrow) ManyClientsProxy(serverInfo, 1);
        if (proxys[i] == NULL) {
            BGCC_WARN("bgcc", "New Mathproxy: %d failed", i);

            while (--i >= 0) {
                delete proxys[i];
            }
            free(proxys);

            return -1;
        }

        proxys[i]->submit(i);

        if (proxys[i]->get_errno() != 0) {
            std::cerr << "Call proxy.submit failed " << i << std::endl;
            return 0;
        } else {
            std::cerr << "Call proxy.submit success " << i << std::endl;
        }
    }

    srand(time(NULL));
    while (true) {
        int r = rand() % nproxy;

        proxys[r]->submit(r);

        if (proxys[r]->get_errno() != 0) {
            std::cerr << "Call proxy.submit failed " << r << std::endl;
        } else {
            std::cerr << "Call proxy.submit success " << r << std::endl;
        }

        bgcc::TimeUtil::safe_sleep_ms(internal_ms);
    }

    for (int i = 0; i < nproxy; ++i) {
        delete proxys[i];
    }
    free(proxys);

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
