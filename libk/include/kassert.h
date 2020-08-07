#ifndef LIBK_KASSERT_H
#define LIBK_KASSERT_H

#include <libk/logging.h>
#include <libk/utils.h>

#define kerror(...) { \
    assert_func(__VA_ARGS__); \
    for(;;); \
}

#define kassert(cond) if(!(cond)){kerror("Kassert failed (" #cond ")");}
#define kassert_m(cond, s) if(!(cond)){kerror("Kassert failed (" #cond "): " s );}


#endif /* ifndef LIBK_KASSERT_H */
