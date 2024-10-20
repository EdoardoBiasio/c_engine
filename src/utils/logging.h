#pragma once

#include "../includes.h"

enum log_levels {
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_DEBUG,
    LOG_INFO,
    LOG_TEST_PASS,
    LOG_TEST_FAIL,
    LOG_SIZE
};

void _log(u16 log_level, const char* string, ...);
void btest(b8 result, u16 num);


#define bfatal(str, ...) _log(LOG_FATAL, str, ##__VA_ARGS__)
#define berror(str, ...) _log(LOG_ERROR, str, ##__VA_ARGS__)
#define bwarning(str, ...) _log(LOG_WARNING, str, ##__VA_ARGS__)
#define bdebug(str, ...) _log(LOG_DEBUG, str, ##__VA_ARGS__)
#define binfo(str, ...) _log(LOG_INFO, str, ##__VA_ARGS__)
#define btest_pass(str, ...) _log(LOG_TEST_PASS, str, ##__VA_ARGS__)
#define btest_fail(str, ...) _log(LOG_TEST_FAIL, str, ##__VA_ARGS__)

