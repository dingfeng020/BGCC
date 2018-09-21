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
 * @file     bidl_const_decimal.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 19ʱ03��29��
 *  
 **/
#ifndef _BIDL2SL_CONST_DECIMAL_H_
#define _BIDL2SL_CONST_DECIMAL_H_

#include "bidl_type.h"

class BidlConstDecimal : public BidlType {
public:
    BidlConstDecimal(const std::string& value) : BidlType(), _value(value) {
        _type_id = DECIMAL;
    }

    virtual ~BidlConstDecimal() {
    }

    virtual std::string get_tag() const {
        return _value + "f";
    }

    std::string get_value() const {
        return _value;
    }

    void set_value(const std::string& value) {
        _value = value;
    }

private:
    std::string _value;
};

#endif // _BIDL2SL_CONST_DECIMAL_H_

