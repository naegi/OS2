#include <libk/io.h>

FILE _IO_stdout = {.fd = 1};

FILE* stdout = &_IO_stdout;
