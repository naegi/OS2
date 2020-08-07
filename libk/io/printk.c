#include <stdarg.h>

#include <libk/utils.h>
#include <libk/string.h>
#include <libk/io.h>

#include <kernel/i386/kcall.h>


size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream){
    kcall_write_t kcall_write_data = {.fd=stream->fd, .buf=ptr, .count=size*nmemb};
    kcall(KCALL_WRITE, &kcall_write_data);

    return size*nmemb;
}

int fputs(const char* s, FILE *stream){
    size_t len = strlen(s);
    fwrite(s, 1, len, stream);

    return (int)len;
}

int puts(const char* s){
    size_t len = strlen(s);

    fwrite(s, 1, len, stdout);
    putchar('\n');
    return (int)(len + 1); // TODO: check for overflow
}

int putchar(int c){
    fwrite(&c, 1, 1, stdout);
    return c;
}

size_t vprintfk_buffsize(const char* format, va_list ap);

// ap will be undefined after call, va_end has not been called
size_t vprintfk_buffsize(const char* format, va_list ap){
    size_t count = 0;
    while(*format != 0){
        switch (*format) {
            case '%':
                format++;
                if(*format == 0)
                    break;

                switch (*format) {
                    case 's':{
                        char* s = va_arg(ap, char*);
                        while(*s != 0){
                            s++;
                            count++;
                        }
                        format++;
                        break;
                    }
                    case '%':
                        count++;
                        format++;
                        break;
                    case 'i':
                    case 'd': {
                        int i = va_arg(ap, int);
                        count += itoa_buffsize(i, 10);
                        format++;
                        break;
                    }
                    case 'x':
                    case 'X': {
                        unsigned int i = va_arg(ap, unsigned int);
                        count += uitoa_buffsize(i, 16);
                        format++;
                        break;
                    }
                    case 'o':
                    case 'O': {
                        int i = va_arg(ap, int);
                        count += itoa_buffsize(i, 8);
                        format++;
                        break;
                    }
                    case 'c':{
                        int i = va_arg(ap, int); // Yes int
                        UNUSED(i);
                        count +=1;
                        format++;
                        break;
                    }
                    default:
                        // TODO: What to do in this case?
                        NOP;

                }

                break;
            default:
                count += 1;
                format++;
        }
    }
    return  count;
}

void printfk(const char* format, ...){
    va_list va;
    va_start(va, format);
    vprintfk(format, va);
    va_end(va);
}

/* Same restrictions as on vprintf: ap is undefined after call and va_end has not been called */
void vprintfk(const char* format, va_list ap){
    while(*format != 0){
        switch (*format) {
            case '%':
                format++;
                if(*format == 0)
                    break;

                switch (*format) {
                    case 's':{
                        char* s = va_arg(ap, char*);
                        fputs(s, stdout);
                        format++;
                        break;
                    }
                    case '%':
                        putchar('%');
                        format++;
                        break;
                    case 'i':
                    case 'd': {
                        int i = va_arg(ap, int);
                        char buff[3*sizeof(int) + 1]; // 3 > log10(2**8), so every number will hold in buff

                        itoa(i, buff, 10);
                        fputs(buff, stdout);
                        format++;
                        break;
                    }
                    case 'x':
                    case 'X': {
                        unsigned int i = va_arg(ap, unsigned int);
                        char buff[2*sizeof(int) + 1]; // 2 = log16(2**8)

                        uitoa(i, buff, 16);
                        fputs(buff, stdout);
                        format++;
                        break;
                    }
                    case 'o':
                    case 'O': {
                        int i = va_arg(ap, int);
                        char buff[3*sizeof(int) + 1]; // 3 > log16(2**8)

                        itoa(i, buff, 8);
                        fputs(buff, stdout);
                        format++;
                        break;
                    }
                    case 'c':{
                        int i = va_arg(ap, int); // Yes int
                        putchar((char) i);
                        format++;
                        break;
                    }
                    default:
                        // TODO: What to do in this case?
                        NOP;

                }

                break;
            default:
                putchar(*format);
                format++;
        }
    }
}
