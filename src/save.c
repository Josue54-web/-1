#include <gb/gb.h>
#include "save.h"
#include "player.h"
#include "achievements.h"
#include "types.h"
#define SRAM_BASE  ((volatile uint8_t *)0xA000)
extern Achievement g_achievements[];
uint8_t save_checksum(const SaveData *sd) {
    const uint8_t *p = (const uint8_t *)sd;
    uint8_t chk = 0;
    for (uint16_t i = 0; i < sizeof(SaveData)-1; i++) chk ^= p[i];
    return chk;
}
uint8_t save_exists(void) { return SRAM_BASE[0] == SAVE_MAGIC; }
void save_write(void) {
    SaveData sd;
    sd.player = g_player;
    for (uint8_t i = 0; i < ACHV_COUNT; i++) sd.achievements[i] = g_achievements[i];
    sd.checksum = save_checksum(&sd);
    ENABLE_RAM_MBC;
    SRAM_BASE[0] = SAVE_MAGIC;
    const uint8_t *src = (const uint8_t *)&sd;
    for (uint16_t i = 0; i < sizeof(SaveData); i++) SRAM_BASE[1+i] = src[i];
    DISABLE_RAM_MBC;
}
void save_read(void) {
    if (!save_exists()) return;
    SaveData sd;
    uint8_t *dst = (uint8_t *)&sd;
    for (uint16_t i = 0; i < sizeof(SaveData); i++) dst[i] = SRAM_BASE[1+i];
    if (save_checksum(&sd) != sd.checksum) return;
    g_player = sd.player;
    for (uint8_t i = 0; i < ACHV_COUNT; i++) g_achievements[i] = sd.achievements[i];
}
void save_erase(void) { ENABLE_RAM_MBC; SRAM_BASE[0] = 0x00; DISABLE_RAM_MBC; }
