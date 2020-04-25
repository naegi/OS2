#include <libk/utils.h>

int atoi(char* s){
    const char digit_min = '0';
    const char digit_max = '9';
    int r = 0;
    bool neg = false;

    if(*s == '-')
        neg = true;

    while(*s <= digit_max && *s >= digit_min){
        r = 10*r + (*s - digit_min);
        s++;
    }

    if(neg)
        r = -r;
    return r;
}
