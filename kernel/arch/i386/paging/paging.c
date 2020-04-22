#include <libk/utils.h>
#include <kernel/i386/paging.h>


// We use 4Mbyte paging (for now) so we don't have page_table (Cf. Intel Vol 3 fig 4.2)

uint32_t page_directory_kernel[1024]; // Have to be 4Kb aligned, and have 1024 entries
uint32_t page_table_kernel[1024]; // Have to be 4Kb aligned, and have 1024 entries


void paging_encode_page_table_entry(uint32_t* page_table_entry, page_entry_t entry){
    *page_table_entry = 0;
    *page_table_entry = entry.page_frame_address & 0XFFFFF000;
    *page_table_entry |= entry.flags & 0x01FFF;
    *page_table_entry |=  0x80; // Set bits 7 => page size = 4Mb
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
    UNUSED(paging_encode_page_directory_map);

    paging_encode_page_directory_table(page_directory_kernel + 0, // Surpervisor, RW, P
            (page_directory_t){.page_table_address=(uint32_t)page_table_kernel, .flags=0x7});

    // Identity map first Mb
    for (size_t i = 0; i < 256; ++i) {
        paging_encode_page_table_entry(page_table_kernel + i,
                (page_entry_t){.page_frame_address=i*0x1000, .flags=0x7});
    }

    // identity map 4Mb (= 1*4Mb pages)
    // paging_encode_page_directory_map(page_directory_kernel + 0, // Surpervisor, RW, P TODO: Global when higher-half ?
    //        (page_entry_t){ .page_frame_address=0, .flags=0x7 });
    // for (size_t i = 1; i < 1024; ++i) {
    //    paging_encode_page_directory_map(page_directory_kernel + i, (page_entry_t){0});
    // }

    paging_setup(page_directory_kernel);
}
