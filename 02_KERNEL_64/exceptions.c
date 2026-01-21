#include "exceptions.h"
#include "vga.h"

void exception_handler(uint64_t interrupt_number, uint64_t error_code, uint64_t rip) {
    char* msg = "Exception received:  ";
    msg[20] = '0' + interrupt_number;
    _print_string_pm(0, 16, msg);
    // Halt the system for now
    while (1);
}
