#include "kiwi/address.h"
#include "kiwi/log.h"

kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void test() {
    std::vector<kiwi::Address::ptr> addrs;

    KIWI_LOG_INFO(g_logger) << "begin";
    bool v = kiwi::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //bool v = kiwi::Address::Lookup(addrs, "www.kiwi.top", AF_INET);
    KIWI_LOG_INFO(g_logger) << "end";
    if(!v) {
        KIWI_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        KIWI_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<kiwi::Address::ptr, uint32_t> > results;

    bool v = kiwi::Address::GetInterfaceAddresses(results);
    if(!v) {
        KIWI_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for(auto& i: results) {
        KIWI_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    //auto addr = kiwi::IPAddress::Create("www.kiwi.top");
    auto addr = kiwi::IPAddress::Create("127.0.0.8");
    if(addr) {
        KIWI_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    //test_ipv4();
    //test_iface();
    test();
    return 0;
}
