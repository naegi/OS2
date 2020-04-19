#ifndef I386_ASM_IO
#define I386_ASM_IO

#include <stdint.h>
#include <libk/utils.h>

void ASM outb(uint16_t port, uint8_t); // send 8 bits to port
void ASM outw(uint16_t port, uint16_t); // send 16 bits to port
void ASM outdw(uint16_t port, uint32_t); // send 32 bits to port

uint8_t ASM inb(uint16_t); // receive 8 bits from port
uint16_t ASM inw(uint16_t); // receive 16 bits from port
uint32_t ASM indw(uint16_t); // receive 32 bits from port

#endif /* ifndef I386_ASM_IO */
