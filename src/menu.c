#include <gb/gb.h>
#include "menu.h"
#include "achievements.h"
#include "save.h"
#include "types.h"
MenuTab g_menu_tab = TAB_ACHIEVEMENTS;
static const char * const TAB_NAMES[TAB_COUNT] = {"Logros","Guardar","Cargar","Salir"};
void menu_open(void) { g_menu_tab = TAB_ACHIEVEMENTS; }
void menu_update(uint8_t joy) {
    if (joy & J_RIGHT && g_menu_tab < TAB_COUNT-1) g_menu_tab++;
    if (joy & J_LEFT  && g_menu_tab > 0)           g_menu_tab--;
    if (joy & J_A) {
        if (g_menu_tab == TAB_SAVE) save_write();
        if (g_menu_tab == TAB_LOAD) save_read();
    }
    (void)TAB_NAMES;
}
void menu_draw(void) {
    fill_bkg_rect(0, 0, SCREEN_W, SCREEN_H, 0);
    for (uint8_t t = 0; t < TAB_COUNT; t++) {
        uint8_t active = (t == g_menu_tab) ? 2 : 1;
        set_bkg_tiles(t*5, 0, 1, 1, &active);
    }
    if (g_menu_tab == TAB_ACHIEVEMENTS) achievements_draw_screen();
}
