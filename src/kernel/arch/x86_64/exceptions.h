#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

void exception_handler(uint64_t interrupt_number, uint64_t error_code, uint64_t rip);

#endif
