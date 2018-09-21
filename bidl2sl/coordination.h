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
 * @file     coordination.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��16�� 13ʱ55��30��
 *  
 **/
#ifndef _BIDL2SL_COORDINATION_H_
#define _BIDL2SL_COORDINATION_H_

#include <stdint.h>
#include <string>

class Coordination {
public:
    Coordination() : line(0), column(0) { }
    int32_t line;
    int32_t column;
    std::string filename;
};
#endif // _BIDL2SL_COORDINATION_H_

