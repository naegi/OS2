#include <kernel/i386/memory_management.h>

#include <kernel/i386/multiboot.h>
#include <libk/utils.h>
#include <libk/string.h>

#include <libk/logging.h>
#include <libk/kassert.h>
#include <libk/utils.h>

// Bits 0 -> aa are flagsS
// No flags now
// Bits 12->31 is index of next (free) entry, if free is set
typedef uint32_t heap_entry_t;


// TODO: more optimal heap system !
static heap_entry_t heap_map[1024 * 1024]; // 4 MB

static size_t first_free_index;
static size_t last_free_index;

static inline size_t memory_map_index_from_addr(void* addr){
    return ((size_t) addr >> 12);
}

static inline void* memory_map_addr_from_index(size_t index){
    return (void*) (index << 12);
}

void* memory_management_get_block(){
    if(first_free_index == last_free_index){ // There is only one block left
        return (void*)BLOCK_ERROR; // Not enough memory
    }

    size_t tmp = first_free_index;

    first_free_index = heap_map[first_free_index] >> 12; // get next free

    return memory_map_addr_from_index(tmp);
}

void memory_management_free_block(void* addr){
    size_t index = memory_map_index_from_addr(addr);
    heap_map[last_free_index] ^= heap_map[last_free_index] & 0xFFFFF000; // reset 24 most important bits
    heap_map[last_free_index] |= index << 12; // set them to index
    last_free_index = index;
}

void memory_management_init(multiboot_info_t* mbd){
    kassert_m(mbd->flags & (1 << 6), "No memory map in multiboot infos, can't contine. Bye.")


    memset(heap_map, 0, sizeof heap_map );

    multiboot_memory_map_t* mmap;

    extern uintptr_t start_kernel;
    extern uintptr_t end_kernel;
    info("Kernel starts at 0x%x, ends at 0x%x and has a size of %d kB", &start_kernel, &end_kernel,
            SIZE_KB((uint32_t)&start_kernel, (uint32_t)&end_kernel));

    size_t index_kernel_low = memory_map_index_from_addr((void*)&start_kernel);
    size_t index_kernel_high = memory_map_index_from_addr((void*)&end_kernel);

    bool first_free = false;


    // Setup available and free memory
    for(mmap = (multiboot_memory_map_t*)mbd->mmap_addr; (uint32_t)mmap < (uint32_t)mbd->mmap_addr + mbd->mmap_length; mmap+=1){
        debug("memory available starting 0x%X on length of 0x%X bytes, of type %d", mmap->base_addr_low, mmap->length_low, mmap->type);
        if(mmap->type != 1) // is memory really available ?
            continue;

        for(size_t i = (size_t)memory_map_index_from_addr((size_t*)mmap->base_addr_low);
                i < (size_t)memory_map_index_from_addr((size_t*)mmap->base_addr_low + mmap->length_low);
                i++){
            if (!(index_kernel_low <= i && i < index_kernel_high)){ // if memory is free (not used by kernel)
                if(first_free){
                    first_free_index = i;
                    first_free = true;
                }
                heap_map[last_free_index] = i << 12;
                last_free_index = i;
            }
        }
    }
}
