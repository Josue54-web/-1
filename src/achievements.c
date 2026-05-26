#include <gb/gb.h>
#include "achievements.h"
#include "types.h"

Achievement g_achievements[ACHV_COUNT];
uint8_t     g_biomes_visited = 0;

const char * const ACHV_NAMES[ACHV_COUNT] = {
    "Lumber Jack","Stone Age","Hot Topic",
    "Getting an Upgrade","Acquired Hardware","Diamonds!",
    "Village Hero","Into the Cave","Pack Rat","World Explorer",
};
const char * const ACHV_DESC[ACHV_COUNT] = {
    "Destroy a tree","Mine your first stone","Get some coal",
    "Get some iron","Get some gold","Get some diamonds!",
    "Find the village","Enter a cave","Fill your inventory",
    "Visit all biomes",
};

void achievements_init(void) {
    for (uint8_t i = 0; i < ACHV_COUNT; i++)
        g_achievements[i].unlocked = 0;
    g_biomes_visited = 0;
}

void achievement_unlock(uint8_t id) {
    if (id >= ACHV_COUNT) return;
    if (g_achievements[id].unlocked) return;
    g_achievements[id].unlocked = 1;
}

void achievements_check_biome(uint8_t biome) {
    if (biome >= 6) return;
    g_biomes_visited |= (1 << biome);
    if (g_biomes_visited == 0x3F)
        achievement_unlock(ACHV_ALL_BIOMES);
}

void achievements_draw_screen(void) {
    fill_bkg_rect(0, 0, SCREEN_W, SCREEN_H, 0);
    for (uint8_t i = 0; i < ACHV_COUNT; i++) {
        uint8_t row = i * 2;
        if (row >= SCREEN_H - 2) break;
        uint8_t icon = g_achievements[i].unlocked ? 1 : 0;
        set_bkg_tiles(0, row, 1, 1, &icon);
    }
}
