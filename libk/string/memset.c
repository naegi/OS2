#include <libk/string.h>

void* memset(void* ptr, int value, size_t num){
    uint8_t* t = (uint8_t*)ptr;
    for (size_t i = 0; i < num; ++i) {
        t[i] = (uint8_t) value;
    }
    return ptr;
}
