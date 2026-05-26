#ifndef SAVE_H
#define SAVE_H
#include "types.h"
#define SAVE_MAGIC  0xC8
uint8_t save_exists(void);
void    save_write(void);
void    save_read(void);
void    save_erase(void);
uint8_t save_checksum(const SaveData *sd);
#endif
