/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/



/**
 * @file binary_protocol_fake.cpp
 * @author chenyuzhen(chenyuzhen)
 * @date 2013/04/17 12:08:20
 * @version 1.0.0 
 * @brief 
 *  
 **/

#include "binary_protocol.h"

#include "fake.h"

bool bgcc::Fake::fake_default_body(char *pbody, int32_t &body_len){
	bool ret=false;
	void* data = NULL;
	int32_t len=0;

	if(!pbody||!body_len){
		return ret;
	}

	SharedPointer<BinaryProtocol> bp(new BinaryProtocol(SharedPointer<ITransport>(NULL)));

	bp->writeMessageBegin(DEF_PROCESSOR, DEF_FUNC, bgcc::CALL, 0);
	bp->writeInt32(0);
	bp->writeString(DEF_FUNC);
	bp->writeBool(false);
	bp->writeMessageEnd(false);

	bp->get_data_buffer()->get_data(&data, len);

	if(body_len>=BODY_LEN(data)){
		body_len= BODY_LEN(data);
		memcpy(pbody, BODY_PTR(data), body_len) ;
		ret=true;
	}

	bp->writeMessageEnd();	//free memory
	
	return ret;
}

bool bgcc::Fake::is_reg_proc(const std::string& proc_name){
	return (proc_name==REG_PROCESSOR);
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
