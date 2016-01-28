#include "logging.h"


int main() {
    bingchen::LOG_ERROR << "hahaha" << 12345;
    bingchen::LOG_TRACE << "hahaha" << 12345;
    bingchen::LOG_INFO << "hahaha" << 12345;
    bingchen::LOG_FATAL << "hahaha" << 12345;


    return 0;
}
