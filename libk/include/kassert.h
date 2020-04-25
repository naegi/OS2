#ifndef LIBK_KASSERT_H
#define LIBK_KASSERT_H

#include <libk/logging.h>
#include <libk/utils.h>

#define kerror(s) { \
    err(make_debug_intro_format(s)); \
    for(;;); \
}

#define kassert(cond) if(!(cond)){kerror("Kassert failed (" #cond ")");}
#define kassert_m(cond, s) if(!(cond)){kerror("Kassert failed (" #cond "): " s );}


#endif /* ifndef LIBK_KASSERT_H */
