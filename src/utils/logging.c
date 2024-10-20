#include "logging.h"

void _log(u16 log_level, const char* string, ...) {
#ifndef BUILD_DEBUG
    if (log_level > 2) return;
#endif
    static const char* colors[LOG_SIZE] = {"0;41", "1;31", "1;33", "1;34", "1;30", "1;32", "1;31"};
    static const char* tags[LOG_SIZE] = {"[FATAL]: ", "[ERROR]: ", "[WARNING]: ", "[DEBUG]: ", "[INFO]: ", "[TEST PASSED]: ", "[TEST FAILED]: "};
    char final_string[512];

    va_list list;
    va_start(list, string);
    vsnprintf(final_string, 512, string, list);
    va_end(list);

    printf("\033[%sm%s%s\033[0m\n", colors[log_level], tags[log_level], final_string);
    fflush(stdout);
}

void btest(b8 result, u16 num) {
    if (result) {
        btest_pass("Test %u passed.", num);
    } else {
        btest_fail("Test %u failed.", num);
    }
}
