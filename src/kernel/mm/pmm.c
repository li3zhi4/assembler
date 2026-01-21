#include "pmm.h"

static uint8_t memory_map[MEMORY_MAP_SIZE];
static uint64_t total_frames;
static uint64_t used_frames;

void pmm_init(uint64_t memory_size) {
    total_frames = memory_size / 4096;
    used_frames = 0;
    for (uint64_t i = 0; i < total_frames / 8; ++i) {
        memory_map[i] = 0;
    }
}

void* pmm_alloc_frame() {
    if (used_frames >= total_frames) {
        return 0; // Out of memory
    }

    for (uint64_t i = 0; i < total_frames / 8; ++i) {
        if (memory_map[i] != 0xff) {
            for (uint8_t j = 0; j < 8; ++j) {
                if (!(memory_map[i] & (1 << j))) {
                    memory_map[i] |= (1 << j);
                    used_frames++;
                    return (void*)((i * 8 + j) * 4096);
                }
            }
        }
    }

    return 0; // Should not happen
}

void pmm_free_frame(void* frame) {
    uint64_t frame_index = (uint64_t)frame / 4096;
    memory_map[frame_index / 8] &= ~(1 << (frame_index % 8));
    used_frames--;
}
