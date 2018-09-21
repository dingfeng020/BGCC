/***********************************************************************
  * Copyright (c) 2013, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_NET_UTIL_H_
#define _BGCC_NET_UTIL_H_

#include "bgcc_common.h"
#include <vector>
#include <string>

namespace bgcc {

class NetUtil {
public:
    /**
     * @brief is_valid_ipv4 �ж�ipstr�Ƿ�Ϊ�Ϸ���ipv4��ַ
     *
     * @param ipstr ipv4��ַ
     *
     * @return
     * @see
     * @note
     * @author
     * @date    2013��10��11�� 18ʱ54��26��
     */
    static bool is_valid_ipv4(const char* ipstr);

    /**
     * @brief is_valid_port �ж�portstr�Ƿ�Ϊ�Ϸ��Ķ˿ں�
     *
     * @param portstr port�ַ���
     *
     * @return
     * @see
     * @note
     * @author
     * @date    2013��10��11�� 18ʱ54��57��
     */
    static bool is_valid_port(const char* portstr);

    /**
     * @brief get_valid_port ���ַ���portstrת��Ϊ����ֵ
     *
     * @param portstr
     *
     * @return
     * @see
     * @note
     * @author
     * @date    2013��10��11�� 18ʱ55��41��
     */
    static uint16_t get_valid_port(const char* portstr);

    typedef struct ServerNode {
        std::string ip;
        uint32_t    port;
    }ServerNode;

    /**
     * @brief get_valid_port �ж�����״̬��ѡ��һ������IP
     *
     * @param server_node_list IP�б�
     *
     * @return ���ص�����iterator
     * @see
     * @note
     * @author
     * @date    2015��01��21�� 10ʱ55��41��
     */
    static std::vector<ServerNode>::iterator net_check(std::vector<ServerNode>& server_node_list);
};

}

#endif // _BGCC_NET_UTIL_H_

