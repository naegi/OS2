#include <libk/utils.h>
#include <kernel/i386/serial.h>
#include <kernel/i386/asm/io.h>

// TODO: Find COM port address in the BIOS Data Area (BIOS) / ? (UEFI)
#define PORT_COM1 0x3F8

void serial_init(){
    // Baud rate = 115 200/divisor
    const uint16_t divisor_value = 0x3;

    outb(PORT_COM1 + 1, 0x00); //Disable interrupts
    outb(PORT_COM1 + 3, 0x80); // Set DLAB value to 1 (MSB)

    //set Baud Rate
    outb(PORT_COM1 + 0, GET_BYTE(divisor_value, 0));
    outb(PORT_COM1 + 1, GET_BYTE(divisor_value, 1));

    outb(PORT_COM1 + 3, 0x03); // 8 bits data + 1 stop bit + no parity
    outb(PORT_COM1 + 2, 0xC7); //Enable FIFO, reset in, out FIFO, 14 bits Data ready interrupts
    outb(PORT_COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set (ready to send/receive ?)

    serial_putchar('\n');
}

inline static bool serial_data_unavailable(){
    return ((inb(PORT_COM1 + 5) & 0x1) == 0);
}


inline static bool serial_is_transmit_okay(){
    return ((inb(PORT_COM1 + 5) & 0x20) == 0);
}

char serial_getchar(){
    while(serial_data_unavailable());
    return (char)inb(PORT_COM1);
}

void serial_putchar(char c){
    while(serial_is_transmit_okay());
    outb(PORT_COM1, (uint8_t) c);
}

void serial_write(const char* c, size_t size){
    for (size_t i = 0; i < size; ++i) {
        serial_putchar(c[i]);
    }
}
