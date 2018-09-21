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
 * @file     bidl_include.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��14�� 20ʱ02��28��
 *  
 **/
#ifndef _BIDL2SL_INCLUDE_H_
#define _BIDL2SL_INCLUDE_H_

#include "bidl_type.h"

class BidlInclude : public BidlType {
    public:
        BidlInclude() : BidlType() {
            _type_id = INCLUDE;
        }
};
#endif // _BIDL2SL_INCLUDE_H_

