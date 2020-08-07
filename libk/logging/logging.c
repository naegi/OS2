#include <libk/logging.h>
#include <libk/io.h>

static int _log_level = LOG_DEFAULT;

static const char *log_msg[] = {
    "DEBUG: ",
    "INFO: ",
    "WARNING: ",
    "ERROR: ",
    "ASSERT: ",
};

#ifndef NO_COLOR

static const char *log_colors[] = {
    "37m",// white
    "34m", // blue
    "33m", // yellow
    "41;30m", // black on red
    "41;30m", // black on red
};

#define COLOR_PREFIX "\x1B[" // escape key code
#define COLOR_RESET "0m" // escape key code

#endif

void _logf(int log_level, const char* fmt, ...){
    if(log_level < _log_level || log_level < LOG_MIN_LEVEL
                              || log_level > LOG_MAX_LEVEL)
        return;

    va_list args;
    va_start(args, fmt);

#ifndef NO_COLOR
    fputs(COLOR_PREFIX, stdout);
    fputs(log_colors[log_level], stdout);
#endif

    fputs(log_msg[log_level], stdout);
    vprintfk(fmt, args);

#ifndef NO_COLOR
    fputs(COLOR_PREFIX COLOR_RESET, stdout);
#endif

    putchar('\n');

    va_end(args);
}

int log_get_level(){
    return _log_level;
}

void log_set_level(int log_level){
    _log_level = log_level;
}
