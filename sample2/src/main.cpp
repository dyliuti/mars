#include "mars/xlog/appender.h"
#include "mars/comm/xlogger/xloggerbase.h"

#include <sys/time.h>

int main() {
    mars::xlog::XLogConfig config;
    config.mode_ = mars::xlog::kAppenderAsync;
    config.logdir_ = "./log";
    config.nameprefix_ = "sample2";
    config.pub_key_ = "";

    mars::xlog::appender_open(config);
    xlogger_SetLevel(kLevelInfo);

    XLoggerInfo info = {};
    info.level = kLevelInfo;
    info.tag = "sample2";
    info.filename = __FILE__;
    info.func_name = __FUNCTION__;
    info.line = __LINE__;
    gettimeofday(&info.timeval, nullptr);
    info.pid = xlogger_pid();
    info.tid = xlogger_tid();
    info.maintid = xlogger_maintid();

    xlogger_Print(&info, "xlog static library initialized from sample2");

    mars::xlog::appender_flush_sync();
    mars::xlog::appender_close();
    return 0;
}
