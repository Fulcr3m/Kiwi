#ifndef __KIWI_MACRO_H__
#define __KIWI_MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define KIWI_LICKLY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define KIWI_UNLICKLY(x)     __builtin_expect(!!(x), 0)
#else
#   define KIWI_LICKLY(x)      (x)
#   define KIWI_UNLICKLY(x)      (x)
#endif

/// 断言宏封装
#define KIWI_ASSERT(x) \
    if(KIWI_UNLICKLY(!(x))) { \
        KIWI_LOG_ERROR(KIWI_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << kiwi::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define KIWI_ASSERT2(x, w) \
    if(KIWI_UNLICKLY(!(x))) { \
        KIWI_LOG_ERROR(KIWI_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << kiwi::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
