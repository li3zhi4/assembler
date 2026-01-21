#include "ata.h"
#include "port_io.h"

#define ATA_DATA_PORT 0x1F0
#define ATA_SECTOR_COUNT_PORT 0x1F2
#define ATA_LBA_LOW_PORT 0x1F3
#define ATA_LBA_MID_PORT 0x1F4
#define ATA_LBA_HIGH_PORT 0x1F5
#define ATA_DRIVE_HEAD_PORT 0x1F6
#define ATA_COMMAND_PORT 0x1F7
#define ATA_STATUS_PORT 0x1F7

void ata_wait() {
    while (inb(ATA_STATUS_PORT) & 0x80);
}

void ata_poll() {
    ata_wait();
    while (!(inb(ATA_STATUS_PORT) & 0x08));
}

void ata_read_sectors(uint32_t lba, uint8_t sector_count, uint16_t* buffer) {
    outb(ATA_DRIVE_HEAD_PORT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH_PORT, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND_PORT, 0x20); // READ SECTORS command

    for (int i = 0; i < sector_count; ++i) {
        ata_poll();
        for (int j = 0; j < 256; ++j) {
            buffer[i * 256 + j] = inw(ATA_DATA_PORT);
        }
    }
}

void ata_write_sectors(uint32_t lba, uint8_t sector_count, uint16_t* buffer) {
    outb(ATA_DRIVE_HEAD_PORT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH_PORT, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND_PORT, 0x30); // WRITE SECTORS command

    for (int i = 0; i < sector_count; ++i) {
        ata_poll();
        for (int j = 0; j < 256; ++j) {
            outw(ATA_DATA_PORT, buffer[i * 256 + j]);
        }
    }
}
