#include <gb/gb.h>
#include <gb/cgb.h>
#include "types.h"
#include "world.h"
#include "cave.h"
#include "player.h"
#include "achievements.h"
#include "save.h"
#include "menu.h"
GameState g_state = STATE_TITLE;
void main(void) {
    cpu_fast();
    DISPLAY_OFF;
    SPRITES_8x8;
    SHOW_BKG; SHOW_SPRITES; DISPLAY_ON;
    uint8_t joy=0,joy_old=0,joy_pressed=0;
    while(1){
        joy_old=joy; joy=joypad(); joy_pressed=joy&~joy_old;
        if((g_state==STATE_WORLD||g_state==STATE_CAVE)&&(joy_pressed&J_SELECT)){
            g_state=STATE_MENU; menu_open();
        }
        switch(g_state){
            case STATE_TITLE:
                if(joy_pressed&J_START){
                    if(save_exists()) save_read();
                    else{ player_init(); achievements_init(); }
                    world_init(); g_state=STATE_WORLD;
                }
                break;
            case STATE_WORLD:{
                player_update_world(joy);
                uint8_t cid=0;
                if(world_is_cave_entrance(g_player.world_x,g_player.world_y,&cid)){
                    cave_init(cid); g_state=STATE_CAVE;
                    achievement_unlock(ACHV_ENTER_CAVE);
                }
                uint8_t biome=WORLD_BIOME[g_player.world_y][g_player.world_x];
                if(biome==BIOME_VILLAGE) achievement_unlock(ACHV_VISIT_VILLAGE);
                achievements_check_biome(biome);
                world_draw(cam_x(),cam_y());
                player_draw_world(cam_x(),cam_y());
                inv_draw();
                break;}
            case STATE_CAVE:
                cave_update(&g_player,joy);
                if((joy_pressed&J_B)&&cave_get_block(cave_player_x,cave_player_y)==CAVE_LADDER)
                    g_state=STATE_WORLD;
                cave_draw(); player_draw_cave(); inv_draw();
                break;
            case STATE_MENU:
                menu_update(joy_pressed); menu_draw();
                if(joy_pressed&J_B)
                    g_state=(current_cave_id==0xFF)?STATE_WORLD:STATE_CAVE;
                break;
        }
        wait_vbl_done();
    }
}
