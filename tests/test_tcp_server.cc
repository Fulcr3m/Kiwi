#include "kiwi/tcp_server.h"
#include "kiwi/iomanager.h"
#include "kiwi/log.h"

kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void run() {
    auto addr = kiwi::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = kiwi::UnixAddress::ptr(new kiwi::UnixAddress("/tmp/unix_addr"));
    std::vector<kiwi::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    kiwi::TcpServer::ptr tcp_server(new kiwi::TcpServer);
    std::vector<kiwi::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    kiwi::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
