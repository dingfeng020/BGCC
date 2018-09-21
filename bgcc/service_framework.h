/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC2_SERVICE_FRAMEWORK_H_
#define _BGCC2_SERVICE_FRAMEWORK_H_

#include <string>

#include "bgcc_common.h"
#include "log.h"
#include "sema.h"
#include "mempool.h"

namespace bgcc {

    /**
     * @brief ��ȡ״̬ö��ֵ
     * @see
     * @note
     * @author
     * @date    2012��06��04�� 14ʱ01��03��
     */
    enum reading_state_t {
        S_SIZE_READING,
        S_DATA_READING,
        S_READING_END
    };

    /**
     * @brief ���ڱ�ʾ��ǰ�Ķ�ȡ״̬
     * @see
     * @note
     * @author
     * @date    2012��06��04�� 14ʱ01��26��
     */
    class reading_item_t {
	public:
        enum reading_state_t    state;  /** ��ǰ�Ķ�״̬*/
        int32_t                 nexpected;  /** �������������ֽ�*/
        int32_t                 nread;  /** �Ѿ���ȡ�˶����ֽ�*/
        char                    head_buf[20]; /** ��Ϣͷ�������� */
        char*                   data;   /** ��Ϣ��������ʹ��mempoll������ͷ�*/
		
		std::string				memo;

        reading_item_t():state(S_SIZE_READING), nexpected(20), nread(0), data(NULL) {
			reset();
        }

		~reading_item_t(){
			reset();
		}

        void reset() {
            state = S_SIZE_READING;
            nexpected = 20;
            nread = 0;
			memset(head_buf,0,sizeof(head_buf));
			if(data){
				bgcc::Mempool::get_instance()->put_mem_block((void**)(&data));
			}
        }
    };
	
	class ReadItem{
		public:
			ReadItem(void *_pTask=NULL):psem(NULL),err(0),isEnroll(false),isWait(false),pTask(_pTask){
				psem=new(std::nothrow)Semaphore(0);
			}

            ~ReadItem() {
                if (psem) {
                    delete psem;
                    psem = NULL;
                }
            }

			void Reset(){
                isWait=false;
				item.reset();

                if (psem) {
                    delete psem;
                    psem = new(std::nothrow)Semaphore(0);
                }
			}

		public:
			reading_item_t item;
			Semaphore *psem;
			int32_t err;
			bool isEnroll;
			bool isWait;
			void *pTask;
	};


    /**
     * @brief ���ڱ�ʾ��ǰ��д��״̬
     * @see
     * @note
     * @author
     * @date    2012��06��04�� 14ʱ04��02��
     */
    struct writing_item_t {
        int32_t nexpected;  /** �������������ֽ�*/
        int32_t nwritten;   /** �Ѿ�д�˶����ֽ�*/
        char* data; /** ��Ϣ��������ʹ��mempoll�ͷ�*/
    };
}
#endif // _BGCC2_SERVICE_FRAMEWORK_H_

