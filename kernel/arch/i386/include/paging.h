#ifndef I386_PAGING_H
#define I386_PAGING_H

#include <libk/utils.h>

#define PAGING_PRESENT 0x1
#define PAGING_SUPERVISOR 0x0 // bit 2 to 0
#define PAGING_USER 0x4
#define PAGING_READONLY 0x0 // bit 1 to 0
#define PAGING_RW 0x2

#define PAGE_SIZE (1 << 22)

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

void paging_map_kernel(uint32_t* page_directory, uint16_t flags);

// Map for use in kernel use only, RW, supervisor only
void paging_map_4MB_kernel(uint32_t logical_address, uint32_t physical_address);

void paging_map_4MB(uint32_t* page_directory, uint32_t logical_address, uint32_t physical_address, uint16_t flags);

#endif /* ifndef I386_PAGING_H */
