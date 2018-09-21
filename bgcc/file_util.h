/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  *
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      license.txt
  *********************************************************************/

#ifndef _BGCC2_FILE_UTIL_H_
#define _BGCC2_FILE_UTIL_H_

#include "bgcc_common.h"

namespace bgcc {

class FileUtil {
public:
    /**
     * @brief close_r ȷ��close�������ж��źź����������
     *
     * @param fd �ļ�������
     *
     * @return
     * @see
     * @note
     * @author
     * @date    2012��06��12�� 14ʱ34��26��
     */
    static int32_t close_r(int32_t fd);

    /**
     * @brief create_directories ��������Ŀ¼
     *
     * @param path ����Ŀ¼����
     *
     * @return 0��ʾ�����ɹ�
     * @see
     * @note
     * @author
     * @date    2013��10��31�� 15ʱ36��09��
     */
    static int32_t create_directories(const char* path);

	static const char SEP; /* ·���ָ��� */

};

}
#endif // _BGCC2_FILE_UTIL_H_

