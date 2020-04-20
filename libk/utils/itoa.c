
#include <libk/utils.h>
#include <libk/kassert.h>

size_t itoa_buffsize(int x, unsigned int base){
    size_t count = 0;
    if(x < 0){
        x = -x;
        count += 1;
    }
    while(x != 0){
        count += 1;
        x /= base;
    }
    return count;
}

// reverse a 0-terminated string
void reverse(char* buff);
void reverse(char* buff){
    char* end = buff;

    // seek last character
    while(*end != 0) end++;
    end--;

    while(buff < end){
        // swap *buff and *end
        char tmp = *buff;
        *buff = *end;
        *end = tmp;

        end--;
        buff++;
    }
}

void itoa(int x, char* buff, unsigned int base);
void itoa(int x, char* buff, unsigned int base){
    kassert_m(base >= 2 && base <= 36, "Base has to be between 2 and 36");

    char * tmp = buff;
    unsigned int y;

    if(x < 0){
        y = (unsigned int) (-x);
        *tmp = '-';
        tmp++;
        buff++; // To allow reverse to work;
    }
    else
        y = (unsigned int) x;

    while(y != 0){
        *tmp = "0123456789abcdefghijklmnopqrstuvwxyz" [y % base];
        tmp++;
        y /= base;
    }
    *tmp = 0;
    reverse(buff);
}
