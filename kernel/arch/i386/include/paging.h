#ifndef I386_PAGING_H
#define I386_PAGING_H

#include <libk/utils.h>

typedef struct{
    uint32_t page_frame_address; // Have to be 4kB aligned
    // NOTE ! flags are not exactly the same for directory entries and table entries (PAT)
    uint16_t flags; // See Intel Vol 3 fig 4.4
} page_entry_t;

typedef struct{
    uint32_t page_table_address; // Have to be 4kB aligned
    uint16_t flags; // See Intel Vol 3 fig 4.4
} page_directory_t;


void paging_init(void);
void ASM paging_setup(void*); // set bit 4 of CR4 register

// Map 4Mb with a 4kB granularity
void paging_encode_page_directory_table(uint32_t* page_directory_entry, page_directory_t entry);
void paging_encode_page_table_entry(uint32_t* page_table_entry, page_entry_t entry);

// Map an entire 4Mb in one page
void paging_encode_page_directory_map(uint32_t* page_directory_entry, page_entry_t entry);

// Map for use in kernel use only, RW, supervisor only
void paging_map_4MB(uint32_t logical_address, uint32_t physical_address);

#endif /* ifndef I386_PAGING_H */
