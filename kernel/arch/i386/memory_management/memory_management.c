#include <kernel/i386/memory_management.h>

#include <kernel/i386/multiboot.h>
#include <libk/utils.h>
#include <libk/string.h>

#include <libk/logging.h>
#include <libk/kassert.h>
#include <libk/utils.h>

// bit 0 is present (physically)
// bit 1 is available
typedef uint8_t heap_entry_t;

// TODO: more optimal heap system !
heap_entry_t heap_map[1024 * 1024]; // One MB

static size_t memory_map_index_from_addr(void* addr){
    return ((size_t) addr >> 12);
}

static void* memory_map_index_addr_from_index(size_t index){
    return (void*) (index << 12);
}

static void memory_management_add_available_memory(size_t* addr, size_t length, uint8_t type){
    for(size_t i = (size_t)memory_map_index_from_addr(addr);
            i < (size_t)memory_map_index_from_addr(addr + length);
            i++){
        heap_map[i] = (type == 1);
    }
}

void* memory_management_get_block(){
    for (size_t i = 0; i < sizeof heap_map; ++i) {
        if((heap_map[i] & 0x1) && !(heap_map[i] & 0x2)){
            heap_map[i] |= 0x2;
            return memory_map_index_addr_from_index(i);
        }

    }
    return NULL;
}

void memory_management_free_block(void* addr){
    heap_map[memory_map_index_from_addr(addr)] &= ~0x2;
}

void memory_management_init(multiboot_info_t* mbd){
    kassert_m(mbd->flags & (1 << 6), "No memory map in multiboot infos, can't contine. Bye.")


    memset(heap_map, 0, sizeof heap_map * sizeof (*heap_map));

    multiboot_memory_map_t* mmap;

    for(mmap = (multiboot_memory_map_t*)mbd->mmap_addr;
            (uint32_t)mmap < (uint32_t)mbd->mmap_addr + mbd->mmap_length; mmap+=1){
        debug("memory available starting 0x%X on length of 0x%X bytes", mmap->base_addr_low, mmap->length_low);
        memory_management_add_available_memory(
                (size_t*)mmap->base_addr_low,
                (size_t)mmap->length_low,
                (uint8_t)mmap->type);
    }

    extern uintptr_t start_kernel;
    extern uintptr_t end_kernel;
    info("Kernel starts at 0x%x, ends at 0x%x and has a size of %d kB", &start_kernel, &end_kernel,
            SIZE_KB((uint32_t)&start_kernel, (uint32_t)&end_kernel));

    size_t index_kernel_low = memory_map_index_from_addr((void*)&start_kernel);
    size_t index_kernel_high = memory_map_index_from_addr((void*)&end_kernel);

    for(size_t i = index_kernel_low; i <= index_kernel_high; i++){
        heap_map[i] |= 0x2;
    }
}
