#ifndef LIBK_KASSERT_H
#define LIBK_KASSERT_H

#include <libk/io.h>
#include <libk/utils.h>

#define kerror(s) {puts(s); for(;;);}

#define _TO_STR(c) #c
#define TO_STR(c) _TO_STR(c) // Need a double macro to force c being executed

#define kassert(cond) if(!(cond)) kerror("Kassert failed in " __FILE__ ":" TO_STR(__LINE__) " kassert(" #cond ")") NOP
#define kassert_m(cond, s) if(!(cond)) kerror("Kassert failed in " __FILE__ ":" TO_STR(__LINE__) "\nCondition: " #cond "\nMessage: " s ) NOP


#endif /* ifndef LIBK_KASSERT_H */
