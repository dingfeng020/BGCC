/***************************************************************************
 *
 * Copyright (c) 2012 , Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @file     bgcc_net_util.cpp
 * @brief
 * @author   liuxupeng(liuxupeng@baidu.com)
 * @version
 * @date     2013年10月11日 18时57分38秒
 *
 **/

#ifdef WIN32
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "bgcc_net_util.h"
#include "string_util.h"

namespace bgcc {

bool NetUtil::is_valid_ipv4(const char* ipstr)
{
#ifdef WIN32
	WSADATA info;
	memset(&info, 0, sizeof(info));
	WSAStartup(MAKEWORD(2, 0), &info);

	sockaddr sa;
	int len = sizeof(sa);
	int ret = WSAStringToAddressA(const_cast<char*>(ipstr), AF_INET, NULL, &sa, &len);
	
	WSACleanup();
	return ret == 0;
#else
    struct in_addr ia;

    if (inet_pton(AF_INET, ipstr, &ia) == 0) {
        return false;
    }
    return true;
#endif
}

bool NetUtil::is_valid_port(const char* portstr)
{
    uint32_t uint32;
    bool ret = bgcc::StringUtil::str2uint32(portstr, uint32);

    if (ret != true || uint32 > 65535) {
        return false;
    }
    return true;
}

uint16_t NetUtil::get_valid_port(const char* portstr)
{
    uint32_t uint32;
    bgcc::StringUtil::str2uint32(portstr, uint32);
    return uint32;
}

}

