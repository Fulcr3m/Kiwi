#include "kiwi/kiwi.h"

static kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    KIWI_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        kiwi::Scheduler::GetThis()->schedule(&test_fiber, kiwi::GetThreadId());
    }
}

int main(int argc, char** argv) {
    KIWI_LOG_INFO(g_logger) << "main";
    kiwi::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    KIWI_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    KIWI_LOG_INFO(g_logger) << "over";
    return 0;
}
