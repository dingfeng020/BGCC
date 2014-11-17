#include <algorithm>
#include <bgcc.h>
#include <manyclients.h>

using namespace bgcc;
using namespace manyclients;

class ManyClientsImpl : public ManyClients{
public:
    virtual ~ManyClientsImpl() { }

    virtual void ping(
            const std::map<std::string, std::string>& ctx) {
        BGCC_TRACE("LXB", "Enter ping");
        BGCC_TRACE("LXB", "Leave ping\n");
    }

};

Server* server;

void* server_func(const bool* isstopped, void*) {
    SharedPointer<IProcessor> xp(
            new ManyClientsProcessor(
                SharedPointer<ManyClients>(
                    new ManyClientsImpl)));

    ServiceManager sm;
    sm.add_service(xp);

    ThreadPool tp;
    tp.init(10);
    server = new Server(&sm, &tp, 8321);
    if (0 != server->serve()) {
        return 0;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    log_open("server.conf");
    Thread t(server_func);
    t.start();

    return 0;
}
