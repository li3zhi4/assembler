#include "simple_fs.h"
#include "ata.h"
#include "vga.h"

static struct superblock sb;
static struct file_entry files[16];

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void fs_init() {
    // Read the superblock
    ata_read_sectors(1, 1, (uint16_t*)&sb);

    if (sb.magic != FS_MAGIC) {
        _print_string_pm(0, 18, "Invalid file system!");
        while (1);
    }

    // Read the file entries
    ata_read_sectors(2, 1, (uint16_t*)files);
}

void fs_list_files() {
    char* msg = "Files: ";
    _print_string_pm(0, 19, msg);
    for (uint32_t i = 0; i < sb.num_files; ++i) {
        _print_string_pm(i * 10, 20, files[i].name);
    }
}

void fs_read_file(char* name, uint8_t* buffer) {
    for (uint32_t i = 0; i < sb.num_files; ++i) {
        if (strcmp(name, files[i].name) == 0) {
            ata_read_sectors(files[i].start_sector, files[i].size / 512, (uint16_t*)buffer);
            return;
        }
    }
}
