#include <iostream>
#include "kiwi/log.h"
#include "kiwi/util.h"

int main(int argc, char** argv) {
    kiwi::Logger::ptr logger(new kiwi::Logger);
    logger->addAppender(kiwi::LogAppender::ptr(new kiwi::StdoutLogAppender));

    kiwi::FileLogAppender::ptr file_appender(new kiwi::FileLogAppender("./log.txt"));
    kiwi::LogFormatter::ptr fmt(new kiwi::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(kiwi::LogLevel::ERROR);

    logger->addAppender(file_appender);

    //kiwi::LogEvent::ptr event(new kiwi::LogEvent(__FILE__, __LINE__, 0, kiwi::GetThreadId(), kiwi::GetFiberId(), time(0)));
    //event->getSS() << "hello kiwi log";
    //logger->log(kiwi::LogLevel::DEBUG, event);
    std::cout << "hello kiwi log" << std::endl;

    KIWI_LOG_INFO(logger) << "test macro";
    KIWI_LOG_ERROR(logger) << "test macro error";

    KIWI_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = kiwi::LoggerMgr::GetInstance()->getLogger("xx");
    KIWI_LOG_INFO(l) << "xxx";
    return 0;
}
