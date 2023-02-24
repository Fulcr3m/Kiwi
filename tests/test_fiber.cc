#include "kiwi/kiwi.h"

kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void run_in_fiber() {
    KIWI_LOG_INFO(g_logger) << "run_in_fiber begin";
    kiwi::Fiber::YieldToHold();
    KIWI_LOG_INFO(g_logger) << "run_in_fiber end";
    kiwi::Fiber::YieldToHold();
}

void test_fiber() {
    KIWI_LOG_INFO(g_logger) << "main begin -1";
    {
        kiwi::Fiber::GetThis();
        KIWI_LOG_INFO(g_logger) << "main begin";
        kiwi::Fiber::ptr fiber(new kiwi::Fiber(run_in_fiber));
        fiber->swapIn();
        KIWI_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        KIWI_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    KIWI_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    kiwi::Thread::SetName("main");

    std::vector<kiwi::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(kiwi::Thread::ptr(
                    new kiwi::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
