#include <stdnoreturn.h>

#include <libk/io.h>
#include <libk/utils.h>
#include <kernel/process.h>
#include <kernel/i386/kcall.h>

noreturn void kernel_main(void);

static void init2(){
    puts("TEST21");
    kcall(KCALL_YIELD, NULL);
    puts("TEST22");
    kcall(KCALL_YIELD, NULL);
}

static void init(){
    puts("TEST11");
    kcall(KCALL_YIELD, NULL);
    puts("TEST12");
    kcall(KCALL_YIELD, NULL);
}

void kernel_main(){
    process_init();
    process_create((void*)init);
    process_create((void*)init2);
    process_start();

    halt();
}
