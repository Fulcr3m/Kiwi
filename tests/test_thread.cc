#include "kiwi/kiwi.h"
#include <unistd.h>

kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

int count = 0;
//kiwi::RWMutex s_mutex;
kiwi::Mutex s_mutex;

void fun1() {
    KIWI_LOG_INFO(g_logger) << "name: " << kiwi::Thread::GetName()
                             << " this.name: " << kiwi::Thread::GetThis()->getName()
                             << " id: " << kiwi::GetThreadId()
                             << " this.id: " << kiwi::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        //kiwi::RWMutex::WriteLock lock(s_mutex);
        kiwi::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        KIWI_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        KIWI_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    KIWI_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/kiwi/test/kiwi/bin/conf/log2.yml");
    kiwi::Config::LoadFromYaml(root);

    std::vector<kiwi::Thread::ptr> thrs;
    for(int i = 0; i < 1; ++i) {
        kiwi::Thread::ptr thr(new kiwi::Thread(&fun2, "name_" + std::to_string(i * 2)));
        //kiwi::Thread::ptr thr2(new kiwi::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        //thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    KIWI_LOG_INFO(g_logger) << "thread test end";
    KIWI_LOG_INFO(g_logger) << "count=" << count;

    return 0;
}
