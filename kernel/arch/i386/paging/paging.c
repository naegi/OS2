#include <libk/utils.h>
#include <libk/logging.h>
#include <libk/kassert.h>
#include <kernel/i386/paging.h>

static inline uint32_t get_physical(uint32_t x){
    return x - 0xC0000000;
}


// We use 4Mbyte paging (for now) so we don't have page_table (Cf. Intel Vol 3 fig 4.2)

uint32_t page_directory_kernel[1024] __attribute__((aligned(4096))); // Have to be 4Kb aligned, and have 1024 entries
//uint32_t page_table_kernel[1024] __attribute__((aligned(4096))); // Have to be 4Kb aligned, and have 1024 entries

void paging_setup_4MB(void);

void paging_encode_page_table_entry(uint32_t* page_table_entry, page_entry_t entry){
    *page_table_entry = 0;
    *page_table_entry = entry.page_frame_address & 0XFFFFF000;
    *page_table_entry |= entry.flags & 0x01FFF;
}

void paging_encode_page_directory_table(uint32_t* page_directory_entry, page_directory_t entry){
    *page_directory_entry = 0;
    *page_directory_entry = entry.page_table_address & 0XFFFFF000;
    *page_directory_entry |= entry.flags & 0x0FFF;
    *page_directory_entry &=  ~(uint32_t)0x80; // Disable bit 7 => point to page table
}

// Map pages of 4Mb of memory
void paging_encode_page_directory_map(uint32_t* page_directory_entry, page_entry_t entry){
    *page_directory_entry = 0;
    *page_directory_entry = entry.page_frame_address & 0xFFC00000;
    *page_directory_entry |= entry.flags & 0x01FFF;
    *page_directory_entry |=  0x80; // Set bits 7 => page size = 4Mb
}

void paging_init(){
    paging_map_kernel(page_directory_kernel, PAGING_SUPERVISOR | PAGING_RW | PAGING_PRESENT);
    paging_setup((void*)get_physical((uint32_t)page_directory_kernel));
}

void paging_map_4MB_kernel(uint32_t logical_address, uint32_t physical_address){
    paging_map_4MB(page_directory_kernel, logical_address, physical_address,
            PAGING_SUPERVISOR | PAGING_RW | PAGING_PRESENT);
}

void paging_map_kernel(uint32_t* page_directory, uint16_t flags){
    extern uintptr_t start_kernel;
    extern uintptr_t end_kernel;

    for(size_t i=((size_t)&start_kernel >> 22); i <= ((size_t)&end_kernel >> 22) ; i++){
        paging_map_4MB(page_directory, i << 22, get_physical(i << 22), flags);
    }
}

void paging_map_4MB(uint32_t* page_directory, uint32_t logical_address, uint32_t physical_address, uint16_t flags){
    size_t pde_entry = logical_address >> 22;
    paging_encode_page_directory_map(page_directory + pde_entry,
            (page_entry_t){.page_frame_address=physical_address, .flags=flags});
}
