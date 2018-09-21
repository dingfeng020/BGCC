/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_SOCKET_BASE_H_
#define _BGCC_SOCKET_BASE_H_

#include "shareable.h"
#include "transport.h"
#include "mutex.h"
#include "guard.h"

#include "socket_util.h"

namespace bgcc {

    /**
     * @class Socket 
     * @brief Socket���ֹ����ӿ�ʵ��
     */
    class Socket :  public ITransport {
    public:

        virtual ~Socket();

        /**
         * @brief   �����ӣ��麯������client��server���о���ʵ��
         * @return  �����ɹ�����0�����򷵻ش����롣
         */
        virtual int32_t open();
		
		virtual int32_t close();

        /**
         * @brief   ��ȡ����
         * @param   buffer ����recv���ݵĴ洢�ռ�
         * @param   length �������ݵĳ���
         * @return  �����ɹ�����0�����򷵻ش����롣
         */
        virtual int32_t read(void * buffer, int32_t length);

        /**
         * @brief   д����
         * @param   buffer ����write���ݵĴ洢�ռ�
         * @param   length д���ݵĳ���
         * @return  �����ɹ�����0�����򷵻ش����롣
         */
        virtual int32_t write(const void* buffer, int32_t length);

        /**
         * @brief   �ж�socket�Ƿ�򿪣��������̺Ϸ��жϣ��麯����client��server�ֱ�ʵ��
         * @return  �ɹ�����ture��ʧ�ܷ���false
         */
        virtual bool is_open() const;

        /**
         * @brief   �����鿴�Ƿ��п�������
         * @return  �����ɹ�����0�����򷵻ش����롣
         */
        virtual bool peek() const;

		TRANSPORTID id() const{
			return _socket;
		}

		protected:
        Socket();
        /**ȫ��socket���*/
        SOCKET _socket;
        int32_t _send_timeout;
        int32_t _recv_timeout;
    };
}

#endif

