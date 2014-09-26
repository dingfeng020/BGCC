#ifndef BGCC_SSL_EPOLL_SERVER_H_
#define BGCC_SSL_EPOLL_SERVER_H_

#ifndef _WIN32

#include <epoll_server.h>

namespace bgcc {

    class SSLEpollServer : public EpollServer {
        public:
            SSLEpollServer(ServiceManager* service_manager,
                    ThreadPool* thread_pool,
                    uint16_t port,
                    const std::string& node = "");

            virtual ~SSLEpollServer() { }

            virtual int32_t serve();
    };
}

#endif

#endif
