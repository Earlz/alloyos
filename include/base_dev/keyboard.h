/*
<Copyright Header>
Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the AlloyOS project
</Copyright Header>
*/

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



