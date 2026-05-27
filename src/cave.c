#include <gb/gb.h>
#include "cave.h"
#include "player.h"
#include "achievements.h"
#include "types.h"
uint8_t cave_mined[CAVE_COUNT][CAVE_H][3];
uint8_t cave_player_x = 10, cave_player_y = 2;
uint8_t current_cave_id = 0xFF;
#define _ CAVE_AIR
#define S CAVE_STONE
#define C CAVE_COAL
#define I CAVE_IRON
#define G CAVE_GOLD
#define D CAVE_DIAMOND
#define B CAVE_BEDROCK
#define L CAVE_LADDER
const uint8_t CAVE_DATA[CAVE_COUNT][CAVE_H][CAVE_W] = {
{{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,S,L,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,S,S,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S},{S,S,S,_,_,_,_,S,S,S,S,_,_,_,_,_,S,S,S,S},{S,S,C,C,_,_,_,S,C,C,S,_,_,_,_,_,C,S,S,S},{S,S,C,C,S,S,S,S,C,C,S,S,S,S,S,S,C,S,S,S},{S,C,C,C,C,S,S,S,S,S,S,S,C,C,C,C,C,C,S,S},{S,C,C,I,C,S,S,S,S,S,S,S,C,C,I,C,C,C,S,S},{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,S,_,_,_,_,_,_,_,_,S,S,S,S,S,S,S},{S,S,S,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,I,I,_,_,C,C,C,S,S,C,C,_,_,_,I,S,S,S},{S,S,I,I,S,S,C,C,C,S,S,C,C,S,S,S,I,S,S,S},{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}},
{{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,S,S,L,_,_,_,_,_,S,S,S,S,S,S,S,S},{S,S,S,S,S,_,_,_,_,_,_,_,_,S,S,S,S,S,S,S},{S,S,S,S,_,_,_,_,_,S,_,_,_,_,S,S,S,S,S,S},{S,S,S,_,_,_,_,_,_,S,_,_,_,_,_,S,S,S,S,S},{S,S,C,C,C,S,S,S,S,S,S,S,C,C,C,C,S,S,S,S},{S,S,C,I,C,S,S,S,S,S,S,S,C,I,C,C,S,S,S,S},{S,S,S,I,S,S,S,S,S,S,S,S,S,I,S,S,S,S,S,S},{S,S,_,_,_,_,_,_,_,S,S,_,_,_,_,_,S,S,S,S},{S,S,_,_,_,_,_,_,_,S,S,_,_,_,_,_,S,S,S,S},{S,I,I,I,S,S,S,S,S,S,S,S,I,I,I,S,S,S,S,S},{S,I,G,I,S,S,S,S,S,S,S,S,I,G,I,S,S,S,S,S},{S,S,S,S,S,_,_,_,_,_,_,_,_,S,S,S,S,S,S,S},{S,S,S,S,C,C,S,S,S,S,S,S,C,C,S,S,S,S,S,S},{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}},
{{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,S,S,S,L,_,_,_,_,S,S,S,S,S,S,S,S},{S,S,S,S,S,S,_,_,_,_,_,_,_,S,S,S,S,S,S,S},{S,S,S,S,S,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,S,C,C,_,_,_,S,S,_,_,_,C,C,S,S,S,S,S},{S,S,S,C,C,S,S,S,S,S,S,S,S,C,C,S,S,S,S,S},{S,S,I,I,S,S,S,S,S,S,S,S,S,I,I,S,S,S,S,S},{S,S,I,I,S,_,_,_,_,_,_,_,S,I,I,S,S,S,S,S},{S,S,S,S,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,S,_,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S},{S,S,G,G,S,S,S,S,S,S,S,S,G,G,S,S,S,S,S,S},{S,S,G,G,S,S,S,S,S,S,S,S,G,G,S,S,S,S,S,S},{S,S,S,S,S,S,D,D,S,S,S,D,D,S,S,S,S,S,S,S},{S,S,S,S,S,S,D,D,S,S,S,D,D,S,S,S,S,S,S,S},{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}},
{{S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S,S},{S,S,S,S,L,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,S,_,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S},{S,S,_,_,_,_,C,S,S,S,S,C,_,_,_,_,S,S,S,S},{S,_,_,_,_,_,C,S,C,C,S,C,_,_,_,_,_,S,S,S},{S,_,_,_,_,S,S,S,C,C,S,S,S,_,_,_,_,_,S,S},{S,C,C,S,S,S,S,S,S,S,S,S,S,C,C,S,S,S,S,S},{S,C,I,C,S,S,S,S,S,S,S,S,I,I,C,S,S,S,S,S},{S,S,_,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,S,_,_,_,_,_,_,_,_,_,_,_,_,S,S,S,S,S,S},{S,G,G,S,S,S,S,S,S,S,S,S,S,G,G,S,S,S,S,S},{S,G,G,S,I,I,S,S,S,S,I,I,S,G,G,S,S,S,S,S},{S,S,S,S,I,I,S,S,S,S,I,I,S,S,S,S,S,S,S,S},{S,S,S,D,D,S,S,S,S,S,S,D,D,S,S,S,S,S,S,S},{S,S,S,D,D,S,S,S,S,S,S,D,D,S,S,S,S,S,S,S},{B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}},
};
#undef _
#undef S
#undef C
#undef I
#undef G
#undef D
#undef B
#undef L
uint8_t cave_is_mined(uint8_t cid,uint8_t cx,uint8_t cy){return(cave_mined[cid][cy][cx>>3]>>(cx&7))&1;}
void cave_set_mined(uint8_t cid,uint8_t cx,uint8_t cy){cave_mined[cid][cy][cx>>3]|=(1<<(cx&7));}
uint8_t cave_can_mine(uint8_t block,uint8_t tool){
    if(block==CAVE_STONE||block==CAVE_COAL) return tool>=TOOL_WOOD_PICK;
    if(block==CAVE_IRON) return tool>=TOOL_STONE_PICK;
    if(block==CAVE_GOLD||block==CAVE_DIAMOND) return tool>=TOOL_IRON_PICK;
    return 0;
}
uint8_t cave_get_block(uint8_t cx,uint8_t cy){
    if(cx>=CAVE_W||cy>=CAVE_H) return CAVE_STONE;
    if(cave_is_mined(current_cave_id,cx,cy)) return CAVE_AIR;
    return CAVE_DATA[current_cave_id][cy][cx];
}
void cave_mine_block(uint8_t cx,uint8_t cy,Player *p){
    uint8_t block=cave_get_block(cx,cy);
    if(block==CAVE_AIR||block==CAVE_BEDROCK) return;
    if(!cave_can_mine(block,p->tool)) return;
    cave_set_mined(current_cave_id,cx,cy);
    inv_add_item(block+10,1);
    if(block==CAVE_STONE) achievement_unlock(ACHV_FIRST_STONE);
    if(block==CAVE_COAL)  achievement_unlock(ACHV_FIRST_COAL);
    if(block==CAVE_IRON)  achievement_unlock(ACHV_FIRST_IRON);
    if(block==CAVE_GOLD)  achievement_unlock(ACHV_FIRST_GOLD);
    if(block==CAVE_DIAMOND) achievement_unlock(ACHV_FIRST_DIAMOND);
}
void cave_init(uint8_t cave_id){
    current_cave_id=cave_id;
    cave_player_x=10; cave_player_y=2;
    for(uint8_t x=0;x<CAVE_W;x++)
        for(uint8_t y=0;y<CAVE_H;y++)
            if(CAVE_DATA[cave_id][y][x]==CAVE_LADDER){cave_player_x=x;cave_player_y=y+1;}
}
void cave_draw(void){
    for(uint8_t row=0;row<CAVE_H;row++)
        for(uint8_t col=0;col<CAVE_W;col++){
            uint8_t t=cave_get_block(col,row);
            set_bkg_tiles(col,row,1,1,&t);
        }
}
static uint8_t cave_move_timer=0;
void cave_update(Player *p,uint8_t joy){
    if(cave_move_timer>0){cave_move_timer--;return;}
    if(joy&J_A){cave_mine_block(cave_player_x+1,cave_player_y,p);}
    uint8_t nx=cave_player_x,ny=cave_player_y;
    if(joy&J_LEFT&&nx>0) nx--;
    else if(joy&J_RIGHT&&nx<CAVE_W-1) nx++;
    else if(joy&J_UP&&ny>0) ny--;
    else if(joy&J_DOWN&&ny<CAVE_H-1) ny++;
    else return;
    if(cave_get_block(nx,ny)==CAVE_AIR){cave_player_x=nx;cave_player_y=ny;}
    else cave_mine_block(nx,ny,p);
    cave_move_timer=6;
}
