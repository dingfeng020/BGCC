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
 * @file     format_checker.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��16�� 15ʱ47��48��
 *  
 **/
#ifndef _BIDL2SL_FORMAT_CHECKER_H_
#define _BIDL2SL_FORMAT_CHECKER_H_

#include <string>

class FormatChecker {
public:
    /**
     * @brief is_bidl_filename_valid ���bidl�ļ��Ƿ���'.bidl'��β
     *
     * @param bidl
     *
     * @return 
     * @see
     * @note
     * @author
     * @date    2012��08��16�� 15ʱ49��23��
     */
    static bool is_bidl_filename_valid(const std::string& bidl);
};
#endif // _BIDL2SL_FORMAT_CHECKER_H_

