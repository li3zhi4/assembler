#include "keyboard.h"
#include "port_io.h"

#define KBD_DATA_PORT   0x60
#define KBD_STATUS_PORT 0x64

static const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0,
    ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void keyboard_init() {
    // Nothing to do for a simple polling driver
}

char keyboard_get_char() {
    uint8_t scancode;
    while (1) {
        // Wait for the keyboard buffer to be full
        if (inb(KBD_STATUS_PORT) & 0x01) {
            scancode = inb(KBD_DATA_PORT);
            // Ignore key releases for now
            if (scancode < sizeof(scancode_to_ascii) && scancode_to_ascii[scancode] != 0) {
                return scancode_to_ascii[scancode];
            }
        }
    }
}
