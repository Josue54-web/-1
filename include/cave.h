#ifndef CAVE_H
#define CAVE_H
#include "types.h"
#define CAVE_W   20
#define CAVE_H   16
extern const uint8_t CAVE_DATA[CAVE_COUNT][CAVE_H][CAVE_W];
extern uint8_t cave_mined[CAVE_COUNT][CAVE_H][3];
extern uint8_t cave_player_x;
extern uint8_t cave_player_y;
extern uint8_t current_cave_id;
void    cave_init(uint8_t cave_id);
void    cave_draw(void);
void    cave_update(Player *p, uint8_t joy);
uint8_t cave_get_block(uint8_t cx, uint8_t cy);
void    cave_mine_block(uint8_t cx, uint8_t cy, Player *p);
uint8_t cave_can_mine(uint8_t block, uint8_t tool);
uint8_t cave_is_mined(uint8_t cave_id, uint8_t cx, uint8_t cy);
void    cave_set_mined(uint8_t cave_id, uint8_t cx, uint8_t cy);
#endif
