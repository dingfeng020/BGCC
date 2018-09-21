/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifdef _WIN32
#include <stdlib.h>
#include <windows.h>
#include "rwlock.h"

namespace bgcc {

    /**
     * @brief ���캯��
     *
     * @see 
     * @note 
     * @author zhangyue
     * @date 2012/12/21 15:08:31
     **/
    RWLock::RWLock():_reader_num(0),_writer_num(0),_writer_waiting_num(0)
    {
        _mutex = CreateMutex(NULL, FALSE, NULL);
        _evt_reader = CreateEvent(NULL, TRUE, TRUE, NULL);  
        _evt_writer = CreateEvent(NULL, TRUE, TRUE, NULL);  
    }

    /**
     * @brief ��������
     *
     * @see 
     * @note 
     * @author zhangyue
     * @date 2012/12/21 15:08:44
     **/
    RWLock::~RWLock()
    {
        CloseHandle(_mutex);
        CloseHandle(_evt_reader);
        CloseHandle(_evt_writer);
    }

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
    int32_t RWLock::get_rdlock()
    {
        HANDLE h[2];
        h[0] = _mutex;
        h[1] = _evt_reader;
        //ͬʱ�ȴ��������Ͷ����ź�
        switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
        {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                //if(_writer_num == 0)
                //{
                    _reader_num++;
                    ResetEvent(_evt_writer);
                //}
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                return -1;
        }
        return 0;
    }

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
    int32_t RWLock::try_rdlock()
    {
        HANDLE h[2];
        h[0] = _mutex;
        h[1] = _evt_reader;
        //ͬʱ�ȴ��������Ͷ����źţ����ȴ�1����
        switch (WaitForMultipleObjects(2, h, TRUE, 1))
        {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                //if(_writer_num == 0)
                //{
                    _reader_num++;
                    ResetEvent(_evt_writer);
                //}
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                return -1;
        }
        return 0;
    }

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
    int32_t RWLock::get_wrlock()
    {
        //����д�߼�¼
        add_writer();
        HANDLE h[2];
        h[0] = _mutex;
        h[1] = _evt_writer;
        //ͬʱ�ȴ���������д���źţ����ȴ�1����
        switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
        {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                //��¼д����Ŀ���رն���д���ź�
                _writer_num++;
                _writer_waiting_num--;
                ResetEvent(_evt_reader);
                ResetEvent(_evt_writer);
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                //�������ɹ�����Ҫɾ���ȴ�д�߼�¼
                remove_writer();
                return -1;
        }
        return 0;
    }

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
    int32_t RWLock::try_wrlock()
    {
        //����д�߼�¼
        add_writer();
        HANDLE h[2];
        h[0] = _mutex;
        h[1] = _evt_writer;
        //ͬʱ�ȴ���������д���źţ����ȴ�1����
        switch (WaitForMultipleObjects(2, h, TRUE, 1))
        {
            case WAIT_OBJECT_0:
            case WAIT_OBJECT_0 + 1:
                //��¼д����Ŀ���رն���д���ź�
                _writer_num++;
                _writer_waiting_num--;
                ResetEvent(_evt_reader);
                ResetEvent(_evt_writer);
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                //�������ɹ�����Ҫɾ���ȴ�д�߼�¼
                remove_writer();
                return -1;
        }
        return 0;
    }

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
    int32_t RWLock::unlock()
    {
        //��ȡ����������
        switch (WaitForSingleObject(_mutex, INFINITE))
        {
            case WAIT_OBJECT_0:
                if(_writer_num == 0)
                {
                    //�����ͷŵ��Ƕ���
                    if(_reader_num > 0)
                    {
                        //ֻ�ж�����ռ�У��ͷŵ��Ƕ�����������Ϊ�ͷŴ���
                        _reader_num--;
                        if(_reader_num == 0)
                        {
                            SetEvent(_evt_writer);
                        }
                    }
                    else
                    {
                        //û���˻�ö�����д������Ϊʧ��
                        return -1;
                    }
                }
                else
                {
                    //�ͷŵ�һ����д��
                    _writer_num = 0;
                    if(_writer_waiting_num == 0)
                    {
                        //û�еȴ���д�ߣ��������ߺ�д���ź�
                        SetEvent(_evt_reader);
                        SetEvent(_evt_writer);
                    }
                    else
                    {
                        //�еȴ���д�ߣ����Ƚ���д����
                        SetEvent(_evt_writer);
                    }
                }
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                return -1;
        }
        return 0;
    }

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
    void RWLock::add_writer()
    {
        //��ȡ����������
        switch (WaitForSingleObject(_mutex, INFINITE))
        {
            case WAIT_OBJECT_0:
                _writer_waiting_num++;
                //�����˵ȴ�д�����رն����źţ��������ж�������
                if(_writer_waiting_num > 0)
                {
                    ResetEvent(_evt_reader);
                }
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                break;
        }
    }

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
    void RWLock::remove_writer()
    {
        //��ȡ����������
        switch (WaitForSingleObject(_mutex, INFINITE))
        {
            case WAIT_OBJECT_0:
                _writer_waiting_num--;
                //���Ѿ�û�еȴ���д�ߣ����������ź�
                if(_writer_waiting_num == 0)
                {
                    SetEvent(_evt_reader);
                }
                ReleaseMutex(_mutex);
                break;
            default:
                ReleaseMutex(_mutex);
                break;
        }
    }
}
#endif//ifdef _WIN32
