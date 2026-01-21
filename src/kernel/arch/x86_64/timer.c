#include "timer.h"
#include "port_io.h"

#define PIT_DATA_PORT0 0x40
#define PIT_COMMAND_PORT 0x43

void timer_init(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;
    outb(PIT_COMMAND_PORT, 0x36);
    outb(PIT_DATA_PORT0, (uint8_t)(divisor & 0xFF));
    outb(PIT_DATA_PORT0, (uint8_t)((divisor >> 8) & 0xFF));
}
