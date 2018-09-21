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
 * @file     bidl_struct.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 12ʱ29��27��
 *  
 **/
#ifndef _BIDL2SL_STRUCT_H_
#define _BIDL2SL_STRUCT_H_

#include "bidl_type.h"

class BidlStructField : public BidlType {
public:
    BidlStructField(const std::string& name) : BidlType(name), _field_id(0), _field_type(NULL) {
        _type_id = STRUCTFIELD;
    }

    virtual ~BidlStructField() {
        if (_field_type) {
            delete _field_type;
        }
    }

    int get_field_id() const {
        return _field_id;
    }

    void set_field_id(int field_id) {
        _field_id = field_id;
    }

    BidlType* get_field_type() const {
        return _field_type;
    }

    void set_field_type(BidlType* bt) {
        _field_type = bt;
    }

private:
    int _field_id;
    BidlType* _field_type;
};

class BidlStruct : public BidlType {
public:
    BidlStruct() : BidlType(), _field_id(0) {
        _type_id = STRUCT;
    }

    virtual ~BidlStruct() {
    }

    virtual void append(BidlType* bt) {
        BidlStructField* sf = dynamic_cast<BidlStructField*>(bt);
        assert(sf != NULL);
        sf->set_field_id(++_field_id);
        BidlType::append(bt);
    }

    virtual std::string get_tag() const {
        return "struct";
    }

    virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
        if ("cpp" == lang) {
            return "bgcc::IDSTRUCT";
        }
        else {
            return "DataType.IDSTRUCT";
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
        size_t first_dot = _symtab_name.find_first_of('.');
        return _symtab_name.substr(first_dot + 1);
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
        return this->get_return_type_name();
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
        return this->get_return_type_name();
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
        return this->get_return_type_name() + "Holder";
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
        return "new " + this->get_name() + "()";
    }
private:
    int _field_id;
};
#endif // _BIDL2SL_STRUCT_H_

