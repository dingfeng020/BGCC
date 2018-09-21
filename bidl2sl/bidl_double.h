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
 * @file     bidl_double.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��09�� 14ʱ33��15��
 *  
 **/
#ifndef _BIDL2SL_DOUBLE_H_
#define _BIDL2SL_DOUBLE_H_

#include "bidl_type.h"

class BidlDouble : public BidlType {
public:
    BidlDouble() : BidlType() {
        _type_id = DOUBLE;
    }

    virtual ~BidlDouble() {
    }

    virtual std::string get_tag() const {
        return "double";
    }

    virtual std::string get_tag(const SourceWriter* sw) const {
        return sw->get_double_tag();
    }
};

#endif // _BIDL2SL_DOUBLE_H_

