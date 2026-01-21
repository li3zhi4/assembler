#ifndef PMM_H
#define PMM_H

#include <stdint.h>

#define MEMORY_MAP_SIZE 4096

void pmm_init(uint64_t memory_size);
void* pmm_alloc_frame();
void pmm_free_frame(void* frame);

#endif
