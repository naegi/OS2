# Memory management

A simple heap management system. 

Here, we manage physical memory.

Heap is partitionned in blocks of 4MB of memory. Each block has a state which is logged in `heap_map`. The index of a block starting at address XXX is `XXX >> 12` (last 24 bits).

State of a block is available (bit 0) and free (bit 1). Whether a block is available or not is determined thanks to multiboot datas.

A block is by default free if it isn't between `start_kernel` and `end_kernel` symbols.

When you ask for a new free block, `memory_management_get_block` will grab the first free block, set it's state to used (bit 1 is now set) and return it's beginning address. When you free a block, it's state will be set back to free.


`heap_map` takes 1MB of memory.

`memory_management_get_block` is in O(`sizeof heap_map`)
`memory_management_free_block` is in O(1)

An alternative implementation could make use of trees/linked lists so that `get` and `free` are in O(log `sizeof  heap_map`) but this would lead to a bit more memory usage.
