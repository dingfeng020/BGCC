/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  *
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      license.txt
  *********************************************************************/

#ifndef _BGCC2_CONF_LOADER_H_
#define _BGCC2_CONF_LOADER_H_

#include "bgcc_common.h"
#include <vector>

namespace bgcc {

class ConfUnit;
class ConfLoader;

/**
 * @brief �����ļ�������
 * @see
 * @note
 * @author
 * @date    2012��06��01�� 10ʱ48��10��
 */
class ConfLoader {
public:
    /**
     * @brief ����󳤶�
     * @see
     * @note
     * @author
     * @date    2012��06��01�� 10ʱ46��17��
     */
    static const int32_t MAX_LINE_LEN;

    /**
     * @brief load_conf ���������ļ�
     *
     * @param conf_filename �����ļ���
     *
     * @return �������ݵ�Root;�����س���ʱ����NULL
     * @see
     * @note
     * @author
     * @date    2012��06��01�� 10ʱ46��48��
     */
    static DEPRECATED(ConfUnit* load_conf(const char* conf_filename));

private:
    /**
     * @brief is_white_line �ж�line�Ƿ�Ϊ�հ���----�Կհ׷���ɵ���
     *
     * @param line C����ַ���
     *
     * @return true��ʾlineΪ�հ��У����򷵻�false
     * @see
     * @note ��(line == NULL)ʱ����false
     * @author
     * @date    2012��06��01�� 10ʱ45��17��
     */
    static bool is_white_line(const char* line);

    /**
     * @brief is_comment_line �ж�line�Ƿ�Ϊע����----��'#'���ص���
     *
     * @param line C����ַ���
     *
     * @return true��ʾlineΪע���У����򷵻�false
     * @see
     * @note ��(line == NULL)ʱ����false
     * @author
     * @date    2012��06��01�� 10ʱ43��22��
     */
    static bool is_comment_line(const char* line);

    static int32_t handle_line(const char* line, ConfUnit* root, ConfUnit*& current);

    static int32_t handle_as_section(const char* line, std::vector<std::string>& paths);

    static int32_t handle_as_item(const char* line, std::string& key, std::string& value);

    static ConfUnit* push_section(ConfUnit* root, const std::vector<std::string>& paths);

    static int32_t push_item(ConfUnit* current, const std::string& key,
            const std::string& value);

};
} // bgcc

namespace bgcc2 {
// ��ǰ������
class ConfUnit;

class ConfLoader {
public:
    /**
     * @brief load_conf �������ļ�conf_file�м������õ�conf_unit�С�
     *
     * @param conf_file �����ļ�����
     * @param conf_unit ���õ�Ԫ
     *
     * @return �ɹ�����true�����򷵻�false������false��ͬʱ�����ܻ����׼���������ӡ������Ϣ��
     * @see
     * @note
     * @author
     * @date    2013��10��11�� 14ʱ10��43��
     */
    static bool load_conf(const std::string& conf_file, ConfUnit& conf_unit);
};

} // bgcc2


#endif  //_BGCC2_CONF_LOADER_H_
