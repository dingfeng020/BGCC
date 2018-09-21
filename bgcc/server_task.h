/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_SERVERTASK_H_
#define _BGCC_SERVERTASK_H_

#include "server.h"
#include "runnable.h"
#include "protocol.h"
#include "processor.h"
#include "event_poll.h"

namespace bgcc {
#ifndef _WIN32 
    class TaskAsso{
        public:
        EventLoop   *pLoop;
        Event       event;
		IServer		*pServer;
		ReadItem	*pItem;
        public:
        TaskAsso():pLoop(NULL),pServer(NULL),pItem(NULL){
            memset(&event, 0, sizeof(Event));
        }
		void Reset(){
			pLoop=NULL;
			memset(&event, 0, sizeof(Event));
			pServer=NULL;
			pItem=NULL;
		}
    };
#endif

    /**
     * @class ServerTask
     * @brief �ɱ�ThreadPoolִ�е���������
     */
    class ServerTask : public Runnable {
        public:
            /** 
             * @brief   ���캯��
             * @param   processor ����������
             * @param   in ��������Э�����
             * @param   out д������Э�����
             **/
            ServerTask(SharedPointer<IProcessor> processor, void* request, int32_t request_len, 
					SharedPointer<IProtocol> out, void *pAsso=NULL);

            /**
             * @brief   ����ִ����
             * @param   
             * @return  
             */
            virtual int32_t operator()(const bool* isstopped, void* param = NULL);

            virtual ~ServerTask() { }

        private:
			/** ������������ */
            SharedPointer<IProcessor> _processor;

            void* _request;
            int32_t _request_len;

			/** д������Э����� */
            SharedPointer<IProtocol> _out;
            
			void *_asso;
    };

}

#endif
