#ifndef VGA_H
#define VGA_H

#include <stdint.h>

// Screen printing functions
void _print_string_pm(uint64_t col, uint64_t row, char* s);
void _clear_screen_pm();

#endif
