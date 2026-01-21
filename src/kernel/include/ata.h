#ifndef ATA_H
#define ATA_H

#include <stdint.h>

// ATA PIO read/write functions
void ata_read_sectors(uint32_t lba, uint8_t sector_count, uint16_t* buffer);
void ata_write_sectors(uint32_t lba, uint8_t sector_count, uint16_t* buffer);

#endif
