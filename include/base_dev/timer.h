#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include <idt.h>
#include <kdebug.h>
#include <x86.h>

#define TIMER_INTERVAL 100

extern volatile uint32_t timer_ticks;

void timer_SetHz(uint32_t hz);
void timer_Irq0Handler(struct InterruptInfo *r);
int timer_Init();





#endif

