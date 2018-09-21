/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC2_RWLOCK_H_
#define _BGCC2_RWLOCK_H_

#include "bgcc_common.h"

namespace bgcc {

    class RWLock
    {
    public:
        /**
         * @brief ���캯��
         *
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:08:31
        **/
        RWLock();

        /**
         * @brief ��������
         *
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:08:44
        **/
        ~RWLock();

        /**
         * @brief ��ȡ����
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:08:51
        **/
        int32_t get_rdlock();
        
        /**
         * @brief ���Ի�ȡд��
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:08:57
        **/
        int32_t try_rdlock();

        /**
         * @brief ��ȡд��
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:09:03
        **/
        int32_t get_wrlock();
        
        /**
         * @brief ���Ի�ȡд��
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:09:09
        **/
        int32_t try_wrlock();

        /**
         * @brief ����
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:09:13
        **/
        int32_t unlock();
    private:
#ifdef _WIN32
        /**
         * @brief ����һ��д�ߣ�windows�µĺ���
         *
         * @return  void 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:09:20
        **/
        void add_writer();
        
        /**
         * @brief ɾ��һ��д��
         *
         * @return  void 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/21 15:09:25
        **/
        void remove_writer();
        
        HANDLE _mutex;                  /**< ������       */
        HANDLE _evt_reader;             /**< �����¼�     */
        HANDLE _evt_writer;             /**< д���¼�     */

        int32_t _reader_num;            /**< ��ǰ�õ����Ķ���   */
        int32_t _writer_num;            /**< ��ǰ�õ�����д��   */
        int32_t _writer_waiting_num;    /**< ��ǰ�Ŷ���д��������  */
#else
        pthread_rwlock_t _rwlock;       /**< Linux�Ķ�д��      */
#endif
    };
}
#endif // _BGCC2_RWLOCK_H_
