#ifndef SIMPLE_FS_H
#define SIMPLE_FS_H

#include <stdint.h>

#define FS_MAGIC 0x53465321 // "SFS!"

struct superblock {
    uint32_t magic;
    uint32_t num_files;
};

struct file_entry {
    char name[32];
    uint32_t start_sector;
    uint32_t size;
};

void fs_init();
void fs_list_files();
void fs_read_file(char* name, uint8_t* buffer);

#endif
