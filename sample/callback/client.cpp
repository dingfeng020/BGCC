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
 * @file client.cpp
 * @author chenyuzhen(chenyuzhen@baidu.com)
 * @date 2012/11/13 16:21:10
 * @version 1.0.0 
 * @brief 
 *  
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bgcc.h>

#include "output-cpp/callback.h"
#include "callback_recv_impl.h"

using namespace bgcc;

#define SERVER_PORT 9999
#define SERVER_IP "127.0.0.1"

void menu();

int main( int argc, char **argv ){
	log_open("client.cfg");

	SharedPointer<IProcessor> proc_recv (
			new demo::CallbackRecverProcessor(
				SharedPointer<callback_recv_impl_t> (new callback_recv_impl_t) ));

	ServiceManager mgr;
	mgr.add_service(proc_recv);
	ServerInfo si(SERVER_IP, SERVER_PORT);
	
	demo::CallbackSenderProxy prx(si, 1, &mgr);

	menu();
	
	char c;
    do{
        try{
			std::cout << "==> ";
			std::cin >> c;
            if(c == 'a'){
				prx.AddClient();
            }
            else if(c == 'd'){
				prx.DelClient();
            }
            else if(c == 'x'){
            }
            else if(c == '?') {
                menu();
            }
            else{
				std::cout << "unknown command `" << c << "'" << std::endl;
                menu();
            }
        }
        catch(const std::exception& ex){
			BGCC_FATAL("client","ex:%s",ex.what());
        }
    }
    while(std::cin.good() && c != 'x');
}

void menu()
{
	std::cout <<
		"Usage:\n"
		"a: Add Client\n"
		"d: Del Client\n"
		"x: Exit\n"
		"?: Help\n";
}


/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
