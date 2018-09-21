/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#include <sstream>
#include "bgcc_common.h"
#include "base_proxy.h"
#include "protocol.h"
#include "log.h"
#include "client_socket.h"
#include "string_util.h"
#include "thread_util.h"
#include "transaction.h"
#include "callback_task.h"

namespace bgcc { 
    BaseProxy::BaseProxy(
            ServerInfo serverinfo,
            int32_t maxConn,
            bool initConsNow,
            ServiceManager* service_manager,
            int32_t tryCount,
            int32_t tryInterval)
        :_serverinfo(serverinfo.getIP(),serverinfo.getPort()),
        _service_manager(service_manager)
    {
        _name = StringUtil::generate_uuid();
        _nMaxConn = maxConn;
        _tryCount = tryCount;
        _tryInterval = tryInterval;
		_seqid=~0;
		_use_existing_socket=false;
#ifndef _WIN32
        signal(SIGPIPE, SIG_IGN);
#endif
        if(initConsNow){
            init(INIT_ALL);
        }
		else{
			init(INIT_CALLBACK);
		}
    }

    BaseProxy::~BaseProxy() {
        uninit();
    }

    int32_t BaseProxy::init(INIT_TYPE type) {
        int32_t ncreated = 0;

        if (_service_manager && (INIT_CALLBACK&type)) {
			if(_selector.Create()==0){
				_callback_thread = SharedPointer<Thread>(
                    new Thread( SharedPointer<CallBackTask>(
							new CallBackTask(_serverinfo.getIP(), _serverinfo.getPort(),
								_name, _service_manager, &_selector))));
	            if (_callback_thread.is_valid()) {
		            BGCC_TRACE("bgcc", "Before Start proxy_name=%s Callback Thread",
						_name.c_str());
			        _callback_thread->start();
				}
			}
			else{
				BGCC_WARN("bgcc", "Selector Create Failed, CallBackTask Start Failed");
			}
        }

		if((type&INIT_CALL)&&!_use_existing_socket){
			for (int32_t i = 0; i < _nMaxConn; ++i) {
				SharedPointer<ClientSocket> connect(
                    new(std::nothrow) ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));
	            if (connect.is_valid() && connect->open() == 0) {
		            SharedPointer<BinaryProtocol> proto(
                        new(std::nothrow) BinaryProtocol(connect));
			        if (proto.is_valid()) {
				        if (_protocols.put(proto) == 0) {
					        ++ncreated;
						}
	                }
		        }
			}
        
			BGCC_TRACE("bgcc", "Proxy %s create %d conntections to server(%s:%d)",
                _name.c_str(), ncreated, _serverinfo.getIP().c_str(), _serverinfo.getPort());
		}

        return ncreated;
    }

    int32_t BaseProxy::uninit() {
        if (_callback_thread.is_valid()) {
            _callback_thread->stop();
            _callback_thread->join();
        }

		_selector.Destroy();

        return 0;
    }

    int32_t BaseProxy::__get_ticket_id(
            const std::string& fun,
            int32_t& ticket_id,
            bool ,
            SharedPointer<IProtocol> ,
            SharedPointer<IProtocol> __oprot)
    {
		ticket_id=Transaction::get_instance()->getTicketId(__oprot,(ThreadIdType)ThreadUtil::self_id(),fun);
        set_errno(0);
		return 0;
    }

    /**
     * @brief �ֶ��ر�����
     *
     * @return  void 
     * @retval   
     * @see 
     * @note 
     * @author zhangyue
     * @date 2013/01/05 15:07:28
    **/
    void BaseProxy::close()
    {
        _protocols.clear();
    }

    std::string BaseProxy::get_name() const {
        return _name;
    }

    void BaseProxy::set_name(const std::string& name) {
        _name = name;
    }

    std::string BaseProxy::get_whoami() const {
        return _whoami;
    }

    void BaseProxy::set_whoami(const std::string& whoami) {
        _whoami = whoami;
    }

	bool BaseProxy::set_property(const std::string &key, int32_t val){
		std::ostringstream os;
		os<<val;

		if(set_property(key, os.str())){
			if(key==PROXY_HB_TIMEOUT){
				_selector.UpdateHBTimeout(val);
			}
			return true;
		}
		
		return false;
	}

	bool BaseProxy::set_property(const std::string &key, const std::string& val){
		if(!is_support(key)){
			return false;
		}

		_property[key]=val;

		return true;
	}
	
	bool BaseProxy::get_property(const std::string &key, int32_t &val) const{
		std::string ret;
		if(get_property(key, ret)){
			val=atoi(ret.c_str());
			return true;
		}

		return false;
	}
	
	bool BaseProxy::get_property(const std::string &key, std::string &val) const{
		if(!is_support(key)){
			return false;
		}

		std::map<std::string, std::string>::const_iterator it=_property.find(key);
		if(it!=_property.end()){
			val=it->second;
			return true;
		}

		return false;
	}

	bool BaseProxy::is_support(const std::string &key) const {
		return (key==PROXY_SEND_TIMEOUT)
			||(key==PROXY_RECV_TIMEOUT
			||(key==PROXY_HB_TIMEOUT));
	}
	
	SharedPointer<ConnInfo> BaseProxy::create_Conn(){
        SharedPointer<bgcc::ClientSocket> client = 
			SharedPointer<bgcc::ClientSocket>(
					new ClientSocket(_serverinfo.getIP(),_serverinfo.getPort()));
        
		if (client.is_valid()) {
            if(client->open()==0){
                SharedPointer<BinaryProtocol> prot = 
					SharedPointer<BinaryProtocol>(new bgcc::BinaryProtocol(client));
                return SharedPointer<ConnInfo>(new ConnInfo(prot));
            }
        }
        return SharedPointer<ConnInfo>(NULL);
    }

    void BaseProxy::free_Conn(SharedPointer<ConnInfo> conn, int32_t err){
        if(_use_existing_socket){
            ConnectionManager::get_instance()->put_connection(_name, conn, (err!=0));
        }
        else if(!err && _protocols.put(conn->proto)!=0) {
            BGCC_WARN("bgcc", "free conn failed");
        }
    }
    
	SharedPointer<ConnInfo> BaseProxy::get_Conn(){
        SharedPointer<ConnInfo> conn;
        if (_use_existing_socket) {
            conn = ConnectionManager::get_instance()->get_connection(_name);
        } else {
            SharedPointer<BinaryProtocol> prot;
			bool ok=false;

			while(_protocols.get(prot, 10)==0&&!ok){ //deal CLOSE_WAIT connect 
				if(prot.is_valid()&&prot->getTransport().is_valid()){
					if((ok=SocketTool::is_ok(prot->getTransport()->id()))){
						conn=SharedPointer<ConnInfo>(new(std::nothrow)ConnInfo(prot));
						break;
					}
				}
			}

            if(!ok){
                conn=create_Conn();
            }
        }
        
        if (conn.is_valid() && conn->proto.is_valid() 
            && conn->proto->getTransport().is_valid()) { 
            int32_t tm = 0;
            if (get_property(PROXY_SEND_TIMEOUT, tm)) { 
                SocketTool::set_sndtimeout(conn->proto->getTransport()->id(), tm);
            }
            if (get_property(PROXY_RECV_TIMEOUT, tm)) {
                SocketTool::set_rcvtimeout(conn->proto->getTransport()->id(), tm);
            }
        }

        return conn;
    }

	const char * BaseProxy::PROXY_SEND_TIMEOUT="proxy.send.timeout";
	const char * BaseProxy::PROXY_RECV_TIMEOUT="proxy.recv.timeout";
	const char * BaseProxy::PROXY_HB_TIMEOUT="proxy.heartbeat.timeout";
} // namespace
