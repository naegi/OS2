#ifndef LOGGING_H
#define LOGGING_H

#define LOG_DEBUG   0
#define LOG_INFO    1
#define LOG_WARN    2
#define LOG_ERR     3
#define LOG_ASSERT  4

#define LOG_DEFAULT LOG_WARN

#define LOG_MAX_LEVEL LOG_ASSERT
#define LOG_MIN_LEVEL LOG_DEBUG


void log_set_level(int log_level);
int log_get_level(void);


#define debug(...)  _logf(LOG_DEBUG, __VA_ARGS__)
#define info(...)   _logf(LOG_INFO,  __VA_ARGS__)
#define warn(...)   _logf(LOG_WARN,  __VA_ARGS__)
#define err(...)    _logf(LOG_ERR,   __VA_ARGS__)
#define assert(...) _logf(LOG_ASSERT,   __VA_ARGS__)

#define FIRST_VA_ARGS(fmt, ...) fmt

#define debug_func(fmt, ...)  _logf(LOG_DEBUG, make_debug_intro_format(fmt), ##__VA_ARGS__)
#define info_func(fmt, ...)   _logf(LOG_INFO, make_debug_intro_format(fmt), ##__VA_ARGS__)
#define warn_func(fmt, ...)   _logf(LOG_WARN, make_debug_intro_format(fmt), ##__VA_ARGS__)
#define err_func(fmt, ...)    _logf(LOG_ERR, make_debug_intro_format(fmt), ##__VA_ARGS__)
#define assert_func(fmt, ...) _logf(LOG_ASSERT, make_debug_intro_format(fmt), ##__VA_ARGS__)


void _logf(int log_level, const char* fmt, ...);

#define _STRINGIZE_DETAIL(x) #x
#define _STRINGIZE(x) _STRINGIZE_DETAIL(x)  // Need a double macro to force c being executed
#define make_debug_intro_format(fmt) "[%s:" __FILE__ ":" _STRINGIZE(__LINE__) "] " fmt, __func__




#endif /* ifndef LOGGING_H */
