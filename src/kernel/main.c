#include <stdint.h>
#include "vga.h"
#include "simple_fs.h"
#include "serial.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"

void main() {
    _clear_screen_pm();
    _print_string_pm(0, 0, "Kernel loaded successfully! We are now in 64-bit long mode.");

    serial_init();
    serial_write_string("Serial port initialized.\\n");

    idt_init();
    pic_init();
    timer_init(50);
    asm volatile("sti");

    fs_init();
    fs_list_files();

    uint8_t buffer[512];
    fs_read_file("test.txt", buffer);
    _print_string_pm(0, 22, (char*)buffer);
    serial_write_string("Read test.txt: ");
    serial_write_string((char*)buffer);
    serial_write_string("\\n");

    // Trigger a triple fault to exit QEMU
    struct idt_ptr null_idt = {0, 0};
    asm volatile("lidt %0" : : "m"(null_idt));
    asm volatile("int $0x0");
}
