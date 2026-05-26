#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H
#include "types.h"
#define ACHV_FIRST_WOOD      0
#define ACHV_FIRST_STONE     1
#define ACHV_FIRST_COAL      2
#define ACHV_FIRST_IRON      3
#define ACHV_FIRST_GOLD      4
#define ACHV_FIRST_DIAMOND   5
#define ACHV_VISIT_VILLAGE   6
#define ACHV_ENTER_CAVE      7
#define ACHV_FULL_INV        8
#define ACHV_ALL_BIOMES      9
extern Achievement g_achievements[ACHV_COUNT];
extern uint8_t g_biomes_visited;
extern const char * const ACHV_NAMES[ACHV_COUNT];
extern const char * const ACHV_DESC[ACHV_COUNT];
void achievements_init(void);
void achievement_unlock(uint8_t id);
void achievements_draw_screen(void);
void achievements_check_biome(uint8_t biome);
#endif
