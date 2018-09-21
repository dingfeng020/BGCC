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
 * @file     source_writer.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��10�� 14ʱ03��42��
 *  
 **/
#ifndef _BIDL2SL_SOURCE_WRITER_H_
#define _BIDL2SL_SOURCE_WRITER_H_

#include <string>
#include <stdint.h>

class BidlType;

class SourceWriter {
public:
    virtual ~SourceWriter(){ };
    /**
     * @brief make_source_writer ��������
     * ����Ŀ����������SourceWriter�������
     *
     * @param bidl Ŀ�����ԣ���ѡֵΪcpp��java��
     * ���bidl�Ƿ������ڱ�׼����ϸ���������ʾ�����˳�����
     *
     * @return SourceWriter�������ָ��
     * @see
     * @note
     * @author
     * @date    2012��09��28�� 17ʱ26��01��
     */
    static SourceWriter* make_source_writer(const std::string& bidl);

    /**
     * @brief write_header ���Ŀ�����Դ����ͷ�ļ�
     *
     * @param bt ��BidlParser���ͺ��BidlType����ָ��
     * @see
     * @note
     * @author
     * @date    2012��09��28�� 17ʱ28��46��
     */
    virtual void write_header(const BidlType* bt) = 0;

    /**
     * @brief write_implement ���Ŀ�����Դ����ʵ���ļ�
     *
     * @param bt ��BidlParser���ͺ��BidlType����ָ��
     * @see
     * @note
     * @author
     * @date    2012��09��28�� 17ʱ30��00��
     */
    virtual void write_implement(const BidlType* bt) = 0;

    virtual std::string get_class_tag()     const = 0;
    virtual std::string get_int8_tag()      const = 0;
    virtual std::string get_int16_tag()     const = 0;
    virtual std::string get_int32_tag()     const = 0;
    virtual std::string get_int64_tag()     const = 0;
    virtual std::string get_boolean_tag()   const = 0;
    virtual std::string get_float_tag()     const = 0;
    virtual std::string get_double_tag()    const = 0;
    virtual std::string get_string_tag()    const = 0;
    virtual std::string get_binary_tag()    const = 0;
    virtual std::string get_sequence_tag()  const = 0;
    virtual std::string get_set_tag()       const = 0;
    virtual std::string get_map_tag()       const = 0;
    virtual std::string get_const_tag()     const = 0;
    virtual std::string get_namespace_tag() const = 0;
    virtual std::string get_void_tag() const = 0;
    virtual std::string get_direction_tag(int32_t dir) const = 0;
    virtual std::string get_identifier_tag(const std::string& id) const = 0;

protected:
    static std::string get_indent(int level);
};
#endif // _BIDL2SL_SOURCE_WRITER_H_

