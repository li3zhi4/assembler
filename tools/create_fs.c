#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "simple_fs.h"

int main() {
    FILE* f = fopen("fs.img", "wb");

    // Write the superblock
    struct superblock sb;
    sb.magic = FS_MAGIC;
    sb.num_files = 1;
    fwrite(&sb, sizeof(sb), 1, f);

    // Write the file entry
    struct file_entry fe;
    strcpy(fe.name, "test.txt");
    fe.start_sector = 3;
    fe.size = 512;
    fwrite(&fe, sizeof(fe), 1, f);

    // Write a dummy sector to fill the space
    uint8_t dummy[512];
    memset(dummy, 0, sizeof(dummy));
    fwrite(dummy, sizeof(dummy), 1, f);

    // Write the file contents
    char* content = "Hello from test.txt!";
    fwrite(content, strlen(content) + 1, 1, f);

    fclose(f);
    return 0;
}
