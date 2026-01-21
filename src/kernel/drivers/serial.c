#include "serial.h"
#include "port_io.h"

#define COM1_PORT 0x3F8

void serial_init() {
    outb(COM1_PORT + 1, 0x00); // Disable all interrupts
    outb(COM1_PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(COM1_PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1_PORT + 1, 0x00); //                  (hi byte)
    outb(COM1_PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COM1_PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1_PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int is_transmit_empty() {
    return inb(COM1_PORT + 5) & 0x20;
}

void serial_write_char(char c) {
    while (is_transmit_empty() == 0);
    outb(COM1_PORT, c);
}

void serial_write_string(const char* s) {
    while (*s) {
        serial_write_char(*s++);
    }
}
