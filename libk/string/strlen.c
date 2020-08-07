#include <libk/string.h>

size_t strlen(const char * s){
    size_t len = 0;
    const char * t = s;
    while(*t != '\0'){
        len++;
        t++;
    }
    return len;
}
