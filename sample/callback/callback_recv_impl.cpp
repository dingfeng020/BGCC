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
 * @file callback_recv_impl.cpp
 * @author chenyuzhen(chenyuzhen@baidu.com)
 * @date 2012/11/13 11:33:15
 * @version 1.0.0 
 * @brief 
 *  
 **/

#include "callback_recv_impl.h"

extern std::map<std::string,demo::CallbackRecverProxy > g_proxys;
extern bgcc::Mutex g_mutex;

demo::CallbackResult callback_recv_impl_t::Callback(
            int32_t num,
            const std::map<std::string, std::string>& ctx){

	BGCC_TRACE("client","recv callback %d",num);

	return demo::CallbackResult(demo::CallbackResult::R_SUCC);
}




















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
