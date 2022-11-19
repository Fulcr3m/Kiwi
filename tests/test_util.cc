#include "kiwi/kiwi.h"
#include <assert.h>

kiwi::Logger::ptr g_logger = KIWI_LOG_ROOT();

void test_assert() {
    KIWI_LOG_INFO(g_logger) << kiwi::BacktraceToString(10);
    KIWI_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();
    return 0;
}
