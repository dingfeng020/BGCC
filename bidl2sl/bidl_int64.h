/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

/**
 * @file     bidl_int64.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 14ʱ31��28��
 *  
 **/
#ifndef _BIDL2SL_INT64_H_
#define _BIDL2SL_INT64_H_

#include "bidl_type.h"

class BidlInt64 : public BidlType {
public:
    BidlInt64() : BidlType() {
        _type_id = INT64;
    }

    virtual ~BidlInt64() {
    }

    virtual std::string get_tag() const {
        return "int64";
    }

    virtual std::string get_tag(const SourceWriter* sw) const {
        return sw->get_int64_tag();
    }

    virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
        if ("cpp" == lang) {
            return "bgcc::IDINT64";
        }
        else {
            return "DataType.IDINT64";
        }
    }

    /**
     * @brief get_return_type_name 
     * ����������Java����ʱ����������Ϊ����ֵ���͵��ַ�����ʾ
     *
     * @return �����ַ���
     * @see
     * @note
     * @author
     * @date    2012��09��08�� 14ʱ32��23��
     */
    virtual std::string get_return_type_name() const {
        return "long";
    }

    /**
     * @brief get_parameter_type_name 
     * ����������Java����ʱ����������Ϊ�������͵��ַ�����ʾ
     *
     * @return �����ַ���
     * @see
     * @note
     * @author
     * @date    2012��09��08�� 14ʱ37��33��
     */
    virtual std::string get_parameter_type_name() const {
        return "long";
    }

    /**
     * @brief get_general_type_name 
     * ����������Java����ʱ����������Ϊ�������͵��ַ�����ʾ
     *
     * @return �����ַ���
     * @see
     * @note
     * @author
     * @date    2012��09��08�� 14ʱ38��19��
     */
    virtual std::string get_general_type_name() const {
        return "Long";
    }

    /**
     * @brief get_holder_type_name 
     * ����������Java����ʱ����������Ϊ�������͵��ַ�����ʾ
     *
     * @return �����ַ���
     * @see
     * @note
     * @author
     * @date    2012��09��08�� 14ʱ45��41��
     */
    virtual std::string get_holder_type_name() const {
        return "LongHolder";
    }

    /**
     * @brief get_init_clause 
     * ����������Java����ʱ�������͵ĳ�ʼ�����
     *
     * @return ���ͳ�ʼ�����
     * @see
     * @note
     * @author
     * @date    2012��09��08�� 14ʱ41��00��
     */
    virtual std::string get_init_clause() const {
        return "0";
    }
};

#endif // _BIDL2SL_INT64_H_

