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
 * @file     bidl_type.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��08�� 16ʱ18��02��
 *  
 **/
#ifndef _BIDL2SL_TYPE_H_
#define _BIDL2SL_TYPE_H_

#include <string>
#include <vector>

#include "coordination.h"
#include "source_writer.h"

class BidlType {
    public:
        enum bidl_type_id_t {
            UNKNOWN,
            NAMESPACE,
            ENUM,
            ENUMFIELD,
            STRUCT,
            STRUCTFIELD,
            BOOLEAN,
            INT8,
            INT16,
            INT32,
            INT64,
            FLOAT,
            DOUBLE,
            STRING,
            BINARY,
            IDENTIFIER,
            SEQUENCE,
            SET,
            MAP,
            TYPEDEF,
            CONST,
            INTEGER,
            LITERAL,
            DECIMAL,
            CONSTBOOLEAN,
            CONSTSEQUENCE,
            CONSTSET,
            CONSTMAP,
            CONSTMAPFIELD,
            CLASS,
            VOID,
            FUNCTION,
            FUNCTIONFIELD,
            FIELDDIRECTION,
            INCLUDE
        };

    private:
        std::string _name;
        BidlType* _parent;
        int32_t _line;
        std::string _filename;
    protected:
        const BidlType* _real_type;

    protected:
        bidl_type_id_t _type_id;
        std::vector<BidlType*> _children;

    public:

        std::string _symtab_name;
        Coordination coordination;

        BidlType(const std::string& name = "root") :
            _name(name), _parent(NULL), _line(0),
            _real_type(NULL), _type_id(UNKNOWN) {
        }

        virtual ~BidlType() {
            std::vector<BidlType*>& v = get_children();
            std::vector<BidlType*>::iterator itr;
            for (itr = v.begin(); itr != v.end(); ++itr) {
                delete *itr;
            }
            v.clear();
        }

        virtual void set_real_type(const BidlType* r) {
            _real_type = r;
        }

        virtual const BidlType* get_real_type() const {
            return this;
        }

        int32_t get_line() const {
            return _line;
        }

        void set_line(int line) {
            _line = line;
        }

        void set_filename(const std::string& filename) {
            _filename = filename;
        }

        std::string get_filename() const {
            return _filename;
        }

        BidlType* get_parent() {
            return _parent;
        }

        void set_parent(BidlType* parent) {
            _parent = parent;
        }

        virtual std::string get_tag() const {
            return "Unknown type";
        }

        virtual std::string get_tag(const SourceWriter*) const {
            return "Unknown type";
        }

        bool is_container() const {
            return SET == _type_id
                || SEQUENCE == _type_id
                || MAP == _type_id;
        }

        bool is_sequence() const {
            return SEQUENCE == _type_id;
        }

        bool is_set() const {
            return SET == _type_id;
        }

        bool is_map() const {
            return MAP == _type_id;
        }

        bool is_pod() const {
            return BOOLEAN == _type_id
                || INT8 == _type_id
                || INT16 == _type_id
                || INT32 == _type_id
                || INT64 == _type_id
                || FLOAT == _type_id;
        }

        bool is_basic() const {
            return BOOLEAN == _type_id
                || INT8 == _type_id
                || INT16 == _type_id
                || INT32 == _type_id
                || INT64 == _type_id
                || FLOAT == _type_id
                || STRING == _type_id
                || BINARY == _type_id;
        }

        bool is_identifier() const {
            return IDENTIFIER == _type_id;
        }

        bool is_namespace() const {
            return NAMESPACE == _type_id;
        }

        bool is_enum() const {
            return ENUM == _type_id;
        }

        bool is_struct() const {
            return STRUCT == _type_id;
        }

        bool is_void() const {
            return VOID == _type_id;
        }

        int get_type_id() const {
            return _type_id;
        }

        void set_name(const std::string& name) {
            _name = name;
        }

        std::string get_name() const {
            return _name;
        }

        virtual void append(BidlType* bt) {
            _children.push_back(bt);
        }

        std::vector<BidlType*>& get_children() {
            return _children;
        }

        const std::vector<BidlType*>& get_children() const {
            return _children;
        }

        virtual BidlType* find_child_by_name() {
            return NULL;
        }

        virtual std::string get_bgcc_type_name(const std::string& lang = "cpp") const {
            (void*)(&lang);
            return "-1";
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
            return "";
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
            return "";
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
            return "";
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
            return "";
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
            return "";
        }
};
#endif // _BIDL2SL_TYPE_H_

