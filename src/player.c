#include <gb/gb.h>
#include "player.h"
#include "world.h"
#include "types.h"
Player g_player;
void player_init(void) {
    g_player.world_x = 20; g_player.world_y = 20;
    g_player.tool = TOOL_WOOD_PICK; g_player.health = 20;
    for (uint8_t i = 0; i < INV_SLOTS; i++) {
        g_player.inventory[i].item_id = 0;
        g_player.inventory[i].count = 0;
    }
}
int16_t cam_x(void) {
    int16_t cx = g_player.world_x - SCREEN_W/2;
    if (cx < 0) cx = 0;
    if (cx > WORLD_W-SCREEN_W) cx = WORLD_W-SCREEN_W;
    return cx;
}
int16_t cam_y(void) {
    int16_t cy = g_player.world_y - SCREEN_H/2;
    if (cy < 0) cy = 0;
    if (cy > WORLD_H-SCREEN_H) cy = WORLD_H-SCREEN_H;
    return cy;
}
static uint8_t move_timer = 0;
void player_update_world(uint8_t joy) {
    if (move_timer > 0) { move_timer--; return; }
    int16_t nx = g_player.world_x, ny = g_player.world_y;
    if      (joy & J_UP)    ny--;
    else if (joy & J_DOWN)  ny++;
    else if (joy & J_LEFT)  nx--;
    else if (joy & J_RIGHT) nx++;
    else return;
    if (!world_is_solid(nx, ny)) {
        g_player.world_x = nx; g_player.world_y = ny;
        move_timer = 8;
    }
}
void player_draw_world(int16_t cx, int16_t cy) {
    uint8_t sx = (uint8_t)((g_player.world_x - cx) * TILE_SIZE + 8);
    uint8_t sy = (uint8_t)((g_player.world_y - cy) * TILE_SIZE + 16);
    move_sprite(0, sx, sy);
}
void player_draw_cave(void) {
    extern uint8_t cave_player_x, cave_player_y;
    move_sprite(0, cave_player_x*TILE_SIZE+8, cave_player_y*TILE_SIZE+16);
}
uint8_t inv_add_item(uint8_t item_id, uint8_t count) {
    for (uint8_t i = 0; i < INV_SLOTS; i++)
        if (g_player.inventory[i].item_id == item_id && g_player.inventory[i].count < 64) {
            g_player.inventory[i].count += count; return 1;
        }
    for (uint8_t i = 0; i < INV_SLOTS; i++)
        if (g_player.inventory[i].count == 0) {
            g_player.inventory[i].item_id = item_id;
            g_player.inventory[i].count = count; return 1;
        }
    return 0;
}
void inv_draw(void) { (void)g_player; }
