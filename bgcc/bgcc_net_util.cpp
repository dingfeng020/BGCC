/***********************************************************************
  * Copyright (c) 2013, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifdef WIN32
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "bgcc_net_util.h"
#include "string_util.h"
#include "socket_util.h"
#include "time_util.h"
#include "log.h"

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

std::vector<bgcc::NetUtil::ServerNode>::iterator NetUtil::net_check(
    std::vector<ServerNode>& server_node_list)
{
    int64_t count_time = 0;
    int64_t temp_time = 0; 
    int64_t min_time = -1; 
    int64_t flag = 0;
    std::vector<ServerNode>::iterator iter;
    iter = server_node_list.end();
    if (server_node_list.size() == 0) {
        return server_node_list.end();
    }

    struct sockaddr_in client_addr;
    SocketTool::init();

    for (std::vector<NetUtil::ServerNode>::iterator it = server_node_list.begin();
                it != server_node_list.end();
                ++it) {
        for (int j = 0; j < 3; ++j) { 
            SOCKET sock;
            memset(&client_addr, 0, sizeof(client_addr));
            fd_set  write_set; 
            timeval to; 
            to.tv_sec = 1; 
            to.tv_usec = 0; 
            char  error = '\0';
            int   len = sizeof(char); 

            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                BGCC_WARN("bgcc", "create socket fail ip=%s, port=%d.", it->ip.c_str(), it->port);
                break;
            }
            struct sockaddr_in server_addr;
            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET; 
            server_addr.sin_port = htons(it->port);    
#ifndef  _WIN32
            server_addr.sin_addr.s_addr = inet_addr(it->ip.c_str());
#else
            server_addr.sin_addr.S_un.S_addr = inet_addr(it->ip.c_str());
#endif
            SocketTool::set_nonblock(sock, 1);
            temp_time = TimeUtil::get_timestamp_us();
            if (connect(sock, (struct sockaddr *)&server_addr, sizeof(sockaddr_in)) != 0) { 

                FD_ZERO(&write_set); 
                FD_SET(sock, &write_set); 

                if (select(sock + 1, NULL, &write_set, NULL, &to) > 0) { 
                    getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, (socklen_t*)&len);  
                    if (error == 0) {
                        flag = 0;
                        BGCC_TRACE("bgcc", "connect successful ip=%s, port=%d.", 
                                it->ip.c_str(), 
                                it->port);
                        SocketTool::close(sock);
                    } 
                    else { 
                        flag = -1;
                        BGCC_WARN("bgcc", "connect fail ip=%s, port=%d.", it->ip.c_str(), it->port);
                        break;
                    }
                } else { 
                    flag = -1;
                    BGCC_WARN("bgcc", "connect fail ip=%s, port=%d.", it->ip.c_str(), it->port);
                    break;
                } 
            } 
            else {
                flag = 0;
                BGCC_TRACE("bgcc", "connect successful ip=%s, port=%d.", it->ip.c_str(), it->port);
                SocketTool::close(sock);
            }

            temp_time = TimeUtil::get_timestamp_us() - temp_time;
            count_time += temp_time;
            BGCC_TRACE("bgcc", "%d times (ip=%s, port=%d) need %ld us.", 
                j, 
                it->ip.c_str(), 
                it->port, 
                temp_time); 
        }
        if (flag == 0) {
            if (min_time == -1 || (count_time < min_time && min_time != -1)) {
                min_time = count_time;
                iter = it;
                BGCC_TRACE("bgcc", "(%s, %d) sum need %ld us.", 
                    iter->ip.c_str(), 
                    iter->port, 
                    count_time);
            }
        } else {
            BGCC_TRACE("bgcc", "connect fail throw ip = %s, port=%d.", it->ip.c_str(), it->port);
        }

        count_time = 0;
    }
    SocketTool::uninit();
    return iter;
}
}

