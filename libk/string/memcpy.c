#include <libk//string.h>

void memcpy(void* dest, const void * src, size_t n){
    char* d = (void*) dest;
    char* s = (void*) src;
    while(n){
        *d = *s;
        d += 1;
        s += 1;
        n--;
    }
}
