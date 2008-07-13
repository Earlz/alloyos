#ifndef KDEBUG_H
#define KDEBUG_H

#include <stdint.h>

void kd_putc_xy(char c,uint8_t x,uint8_t y);
void kd_puts_xy(char *str,uint8_t x,uint8_t y);
void kd_cls();
void kd_set_color(uint8_t color);






#endif
