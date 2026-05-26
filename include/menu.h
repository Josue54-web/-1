#ifndef MENU_H
#define MENU_H
#include "types.h"
typedef enum {
    TAB_ACHIEVEMENTS = 0,
    TAB_SAVE,
    TAB_LOAD,
    TAB_QUIT,
    TAB_COUNT
} MenuTab;
extern MenuTab g_menu_tab;
void menu_open(void);
void menu_update(uint8_t joy);
void menu_draw(void);
#endif
