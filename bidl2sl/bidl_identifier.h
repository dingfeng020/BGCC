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
 * @file     bidl_identifier.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 15ʱ40��52��
 *  
 **/
#ifndef _BIDL2SL_IDENTIFIER_H_
#define _BIDL2SL_IDENTIFIER_H_

#include "bidl_type.h"

class BidlIdentifier : public BidlType {
public:
    BidlIdentifier(const std::string& name) : BidlType(name) {
        _type_id = IDENTIFIER;
    }

    virtual ~BidlIdentifier() {
    }

    virtual std::string get_tag() const {
        return get_name();
    }

    virtual std::string get_tag(const SourceWriter* sw) const {
        return sw->get_identifier_tag(get_name());
    }

    virtual const BidlType* get_real_type() const {
        if (_real_type && _real_type->is_identifier()) {
            return _real_type->get_real_type();
        }
        else {
            return _real_type;
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
        return this->get_real_type()->get_return_type_name();
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
        return this->get_real_type()->get_parameter_type_name();
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
        return this->get_real_type()->get_general_type_name();
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
        return this->get_real_type()->get_holder_type_name();
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
        return this->get_real_type()->get_init_clause();
    }
};

#endif // _BIDL2SL_IDENTIFIER_H_

