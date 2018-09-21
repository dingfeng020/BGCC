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
 * @file     bidl_int32.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 14ʱ30��49��
 *  
 **/
#ifndef _BIDL2SL_INT32_H_
#define _BIDL2SL_INT32_H_

#include "bidl_type.h"

class BidlInt32 : public BidlType {
public:
    BidlInt32() : BidlType() {
        _type_id = INT32;
    }

    virtual ~BidlInt32() {
    }

    virtual std::string get_tag() const {
        return "int32";
    }

    virtual std::string get_tag(const SourceWriter* sw) const {
        return sw->get_int32_tag();
    }

    virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
        if ("cpp" == lang) {
            return "bgcc::IDINT32";
        }
        else {
            return "DataType.IDINT32";
        }
    }

    virtual std::string get_holder_name(int32_t level) const {
        if (0 == level) {
            return "IntHolder";
        }
        else {
            return "Integer";
        }
    }

    virtual std::string get_r_name(int32_t level) const {
        if (0 == level) {
            return "int";
        }
        else {
            return "Integer";
        }
    }

    virtual std::string get_p_name(int32_t level) const {
        if (0 == level) {
            return "int";
        }
        else {
            return "Integer";
        }
    }

    virtual std::string get_init_clause(int32_t) const {
        return "0";
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
        return "int";
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
        return "int";
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
        return "Integer";
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
        return "IntHolder";
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

#endif // _BIDL2SL_INT32_H_

