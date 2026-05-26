#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
extern Player g_player;
void    player_init(void);
void    player_update_world(uint8_t joy);
void    player_draw_world(int16_t cam_x, int16_t cam_y);
void    player_draw_cave(void);
uint8_t inv_add_item(uint8_t item_id, uint8_t count);
void    inv_draw(void);
int16_t cam_x(void);
int16_t cam_y(void);
#endif
