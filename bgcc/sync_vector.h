/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_SYNC_VECTOR_H_
#define _BGCC_SYNC_VECTOR_H_

#include <queue>
#include "mutex.h"
#include "sema.h"
#include "guard.h"
#include "bgcc_error.h"
#include "shareable.h"
#include "libs/rwlock.h"
#include "log.h"

/**
 * @brief �̰߳�ȫvector
 * @see
 * @note
 * @author
 * @date    2012��05��30�� 16ʱ42��56��
 */
namespace bgcc {

    template <typename ElemType>
        class SyncVector : public Shareable {
        public:
            SyncVector() 
            {
                _psem = new Semaphore();
            }
            
            ~SyncVector()
            {
                if(_psem != NULL)
                {
                    delete _psem;
                }
            }
            typedef Guard<Mutex> ScopedGuard;

            /**
             * @brief put ��ͬ��vector�����Ԫ�أ������ظ�����ͬʱ�����ź���
             *
             * @param elem ��Ԫ��
             *
             * @return ��ӳɹ�����0�����򷵻ش�����
             * @see
             * @note
             * @author
             * @date    2012��05��30�� 19ʱ11��24��
             */
            int32_t put(ElemType elem) {
                {
                    ScopedGuard guard(&_mutex);
                    if (guard.is_locked()) {
                        try {
                            _queue.push(elem);
                        }
                        catch(std::bad_alloc &) {
                            return E_BGCC_NOMEM;
                        }
                    }
                    else {
                        return E_BGCC_SYSERROR;
                    }
                }
                _psem->signal();
                return 0;
            }

            /**
             * @brief get ��ͬ��vector��ȡԪ�ء����ͬ��vectorΪ�գ�������ָ��ʱ��
             * BGCC_SEMA_WAIT_INFINITE��ʾ����������
             *
             * @param elem ȡ�õ�Ԫ��
             * @param millisecond ��ʱʱ�������룩
             *
             * @return �ɹ�����0�����򷵻ش�����: E_BGCC_TIMEOUT��ʾ��ʱ.
             * @see
             * @note
             * @author
             * @date    2012��05��30�� 19ʱ12��19��
             */
            int32_t get(ElemType& elem, int millisecond) {
                _rwlock_clear.get_rdlock();
                int32_t ret = _psem->wait(millisecond);

                if (0 == ret) {
                    {   
                        ScopedGuard guard(&_mutex);
                        if (guard.is_locked()) {
                            elem = _queue.front();
                            _queue.pop();
                        }   
                        else {
                            _rwlock_clear.unlock();
                            return E_BGCC_SYSERROR;
                        }   
                    }
                    _rwlock_clear.unlock();   
                    return 0;
                }   
                else {
                    _rwlock_clear.unlock();
                    return ret;
                }
            }

            int32_t size() {
                return (int32_t)_queue.size();
            }

            /**
             * @brief ���
             *
             * @return  void
             * @retval   
             * @see 
             * @note 
             * @author zhangyue
             * @date 2013/01/05 15:12:51
            **/
            void clear() {
                BGCC_DEBUG("bgcc","SyncVector Clear()");
                _rwlock_clear.get_wrlock();
                ScopedGuard guard(&_mutex);
                std::vector<ElemType> tmp;
				while(_queue.size()){
					_queue.pop();
				}
                delete _psem;
                _psem = new Semaphore();
                _rwlock_clear.unlock();
            }

        protected:
            SyncVector(const SyncVector&);
            SyncVector& operator=(const SyncVector&);

        private:
            std::queue<ElemType> _queue;
            Mutex _mutex;
            RWLock _rwlock_clear;
            Semaphore * _psem;

        }; // end of class SyncVector
}

#endif // _BGCC_SYNC_VECTOR_H_
