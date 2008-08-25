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

/**This file contains all of the platform and OS dependent kernel functions for handling interrupts.**/


#ifndef IDT_H
#define IDT_H
#include <stdint.h>
#define INTERRUPT_NORMAL 0
#define INTERRUPT_NO_ERR 1
#define INTERRUPT_IRQ_M 2
#define INTERRUPT_IRQ_S 3

/* Defines an IDT entry */
struct idt_entry {
	uint16_t base_lo;
	uint16_t sel;        /* Our kernel segment goes here! */
	uint8_t always0;     /* This will ALWAYS be set to 0! */
	uint8_t flags;       /* Set using the above table! */
	uint16_t base_hi;
}
__attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
}
__attribute__((packed));

struct InterruptInfo{
	uint32_t ds, es, fs, gs;      /* pushed the segs last */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
	uint32_t int_no, err_code;    /* our 'push byte #' and ecodes do this */
	uint32_t eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
}
__attribute__((packed));


extern void idt_load();
extern volatile struct idt_entry idt[256];
extern volatile struct idt_ptr idtp;

typedef void (*interrupt_hook)(struct InterruptInfo*);
extern volatile interrupt_hook int_hooks[];

extern void* int_template;
extern uint32_t int_template_size;



void idt_set_gate(uint8_t num, void (*base), uint16_t sel, uint8_t flags);
void *CreateInterruptStub(uint8_t num, uint8_t type);
void RemapIrqs(void);
int InstallInterruptHook(uint8_t num,interrupt_hook func);
void InitIdt();

#define IRQ_BASE_INT 32 //add this number to the IRQ number for the interrupt number

#define INT0_STACK_BASE 0x300000 //this area is for temporary interrupt stacks

extern uint8_t int_level;


#endif

