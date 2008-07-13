#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <idt.h>
extern uint8_t kbdus[128];
extern uint8_t kbdus_caps[128];

typedef struct {
	unsigned char caps;
	unsigned char shift;
	unsigned char scroll;
	unsigned char num;
	unsigned char ctrl;
	unsigned char alt;
}
shift_locks; /*for simplicity and speed*/

extern volatile shift_locks kbd_shifts;


typedef struct {
	uint16_t scancode;
	uint8_t asci;
}kbd_key;

#define KBD_BUFFER_SIZE 128 
//how many keys the buffer can hold


//key defines
#define LSHIFT_KEY 42
#define RSHIFT_KEY 54
#define CTRL_KEY 29
#define ALT_KEY 56
#define CAPS_KEY 58
#define NUM_KEY 69
#define SCROLL_KEY 70
#define F_BASE_KEY 59  //59 is F1, 60 is F2, and so on until F10
#define HOME_KEY 71
#define UP_KEY 72
#define PAGE_UP_KEY 73
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define END_KEY 79
#define DOWN_KEY 80
#define PAGE_DOWN_KEY 81
#define INSERT_KEY 82
#define DEL_KEY 83
#define F11_KEY 87
#define F12_KEY 89

void kbd_Irq1Handler(struct InterruptInfo *r);
int kbd_PutBuffer(uint16_t scan,uint8_t asci);
int kbd_Init();
uint8_t kbd_GetKey();




#endif



