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
 * @file     bidl_set.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 16ʱ17��01��
 *  
 **/
#ifndef _BIDL2SL_SET_H_
#define _BIDL2SL_SET_H_

#include "bidl_type.h"

class BidlSet : public BidlType {
public:
    BidlSet() : BidlType(), _sub_type(NULL) {
        _type_id = SET;
    }

    virtual ~BidlSet() {
        if (_sub_type) {
            delete _sub_type;
        }
    }

    virtual std::string get_tag() const {
        std::string str;
        str.append("set<");
        if (_sub_type) {
            str.append(_sub_type->get_tag());
        }
        str.append("> ");
        return str;
    }

    virtual std::string get_tag(const SourceWriter* sw) const {
        std::string str;
        str.append(sw->get_set_tag());
        str.append("<");
        if (_sub_type) {
            str.append(_sub_type->get_tag(sw));
        }
        str.append("> ");
        return str;
    }

    void set_sub_type(BidlType* bt) {
        _sub_type = bt;
    }

    const BidlType* get_sub_type() const {
        return _sub_type;
    }

    virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
        if ("cpp" == lang) {
            return "bgcc::IDSET";
        }
        else {
            return "DataType.IDSET";
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
        std::string str;
        str.append("Set<");
        if (_sub_type) {
            str.append(_sub_type->get_real_type()->get_general_type_name());
        }
        str.append(">");
        return str;
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
        return get_return_type_name();
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
        return get_return_type_name();
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
        std::string str;
        str.append("Holder<");
        str.append(get_return_type_name());
        str.append(">");
        return str;
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
        std::string str;
        str.append("new HashSet<");
        if (_sub_type) {
            str.append(_sub_type->get_real_type()->get_general_type_name());
        }
        str.append(">()");
        return str;
    }

private:
    BidlType* _sub_type;
};
#endif // _BIDL2SL_SET_H_

