#ifndef TYPES_H
#define TYPES_H

#include <gb/gb.h>
#include <stdint.h>

#define SCREEN_W        20
#define SCREEN_H        18
#define TILE_SIZE        8
#define WORLD_W         64
#define WORLD_H         64

#define BIOME_PLAINS     0
#define BIOME_FOREST     1
#define BIOME_DESERT     2
#define BIOME_SNOW       3
#define BIOME_VILLAGE    4
#define BIOME_OCEAN      5

#define TILE_GRASS       0
#define TILE_DIRT        1
#define TILE_SAND        2
#define TILE_SNOW        3
#define TILE_WATER       4
#define TILE_TREE        5
#define TILE_CACTUS      6
#define TILE_HOUSE       7
#define TILE_PATH        8
#define TILE_CAVE_ENTER  9
#define TILE_STONE      10

#define CAVE_AIR         0
#define CAVE_STONE       1
#define CAVE_COAL        2
#define CAVE_IRON        3
#define CAVE_GOLD        4
#define CAVE_DIAMOND     5
#define CAVE_BEDROCK     6
#define CAVE_LADDER      7

#define TOOL_NONE        0
#define TOOL_WOOD_PICK   1
#define TOOL_STONE_PICK  2
#define TOOL_IRON_PICK   3
#define TOOL_GOLD_PICK   4
#define TOOL_DIAMOND_PICK 5
#define TOOL_SWORD       6

#define INV_SLOTS        9
#define ACHV_COUNT       10
#define CAVE_COUNT       4

typedef struct { uint8_t item_id; uint8_t count; } InvSlot;

typedef struct {
    int16_t world_x, world_y;
    uint8_t tool, health;
    InvSlot inventory[INV_SLOTS];
} Player;

typedef enum { STATE_TITLE, STATE_WORLD, STATE_CAVE, STATE_MENU } GameState;

typedef struct { uint8_t unlocked; } Achievement;

typedef struct {
    Player player;
    Achievement achievements[ACHV_COUNT];
    uint8_t checksum;
} SaveData;

#endif
