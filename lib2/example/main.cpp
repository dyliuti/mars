#include "mars/xlog/appender.h"
#include "mars/comm/xlogger/xlogger.h"

using namespace mars::xlog;

int main() {
    XLogConfig config;
    config.logdir_     = "./log";
    config.nameprefix_ = "app";
    config.pub_key_    = "";   // empty = no encryption
    config.mode_       = kAppenderAsync;

    appender_open(config);

    xinfo2("hello xlog %d", 42);

    appender_flush_sync();
    appender_close();
    return 0;
}
