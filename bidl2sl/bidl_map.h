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
 * @file     bidl_map.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 16ʱ22��13��
 *  
 **/
#ifndef _BIDL2SL_MAP_H_
#define _BIDL2SL_MAP_H_

#include "bidl_type.h"

class BidlMap : public BidlType {
    public:
        BidlMap() : BidlType(), _key_type(NULL), _value_type(NULL) {
            _type_id = MAP;
        }

        virtual ~BidlMap() {
            if (_key_type) {
                delete _key_type;
            }

            if (_value_type) {
                delete _value_type;
            }
        }

        virtual std::string get_tag(const SourceWriter* sw) const {
            std::string str;
            str.append(sw->get_map_tag());
            str.append("<");
            if (_key_type) {
                str.append(_key_type->get_tag(sw));
            }
            str.append(", ");
            if (_value_type) {
                str.append((_value_type->get_tag(sw)));
            }
            str.append("> ");
            return str;
        }

        void set_key_type(BidlType* bt) {
            _key_type = bt;
        }

        void set_value_type(BidlType* bt) {
            _value_type = bt;
        }

        const BidlType* get_key_type() const {
            return _key_type;
        }

        const BidlType* get_value_type() const {
            return _value_type;
        }

        virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
            if ("cpp" == lang) {
                return "bgcc::IDMAP";
            }
            else {
                return "DataType.IDMAP";
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
            str.append("Map<");
            if (_key_type) {
                str.append(_key_type->get_real_type()->get_general_type_name());
            }
            else {
                str.append("null");
            }
            str.append(", ");
            if (_value_type) {
                str.append(_value_type->get_real_type()->get_general_type_name());
            }
            else {
                str.append("null");
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
            str.append(this->get_return_type_name());
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
            str.append("new HashMap<");
            if (_key_type) {
                str.append(_key_type->get_real_type()->get_general_type_name());
            }
            else {
                str.append("null");
            }
            str.append(", ");
            if (_value_type) {
                str.append(_value_type->get_real_type()->get_general_type_name());
            }
            else {
                str.append("null");
            }
            str.append(">()");
            return str;
        }
    private:
        BidlType* _key_type;
        BidlType* _value_type;
};

#endif // _BIDL2SL_MAP_H_

