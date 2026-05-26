#ifndef WORLD_H
#define WORLD_H
#include "types.h"
extern const uint8_t WORLD_MAP[WORLD_H][WORLD_W];
extern const uint8_t WORLD_BIOME[WORLD_H][WORLD_W];
extern const uint8_t CAVE_X[CAVE_COUNT];
extern const uint8_t CAVE_Y[CAVE_COUNT];
void    world_init(void);
void    world_draw(int16_t cam_x, int16_t cam_y);
uint8_t world_get_tile(int16_t x, int16_t y);
uint8_t world_is_solid(int16_t x, int16_t y);
uint8_t world_is_cave_entrance(int16_t x, int16_t y, uint8_t *cave_id);
#endif
