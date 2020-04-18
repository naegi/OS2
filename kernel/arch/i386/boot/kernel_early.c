#include <stdint.h>
#include <stddef.h>

#include <kernel/i386/multiboot.h>
#include <libk/utils.h>

void kernel_early(multiboot_info_t*, uint32_t);

void kernel_early(multiboot_info_t* mbd, uint32_t magic){
    UNUSED(mbd);
    UNUSED(magic);
}
