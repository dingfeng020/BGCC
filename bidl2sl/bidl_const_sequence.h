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
 * @file     bidl_const_sequence.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��28�� 12ʱ29��09��
 *  
 **/
#ifndef _BIDL2SL_CONST_SEQUENCE_H_
#define _BIDL2SL_CONST_SEQUENCE_H_

#include "bidl_type.h"

class BidlConstSequence : public BidlType {
public:
    BidlConstSequence() {
        _type_id = CONSTSEQUENCE;
    }
};

#endif // _BIDL2SL_CONST_SEQUENCE_H_

