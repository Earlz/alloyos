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

#include <x86.h>
#include <stdlib.h>
#include <idt.h>
#include <string.h>
#include <kdebug.h>

inline void hlt();




void RemapIrqs(void) { //this will remap IRQs to where they take up interrupts 32-48
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}

void ExceptionDivideBy0(struct InterruptInfo *f){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Division By 0 >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionNmi(struct InterruptInfo *c){
	kd_puts_xy(">>KERNEL PANIC>> Non Maskable Interrupt >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionInvalidOp(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Invalid Opcode >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionNoDevice(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> FPU Not Present >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionDoubleFault(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Double Fault Exception >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionInvalidTss(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Invalid TSS >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionSegNotPresent(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Segment Not Present >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionStack(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Stack Exception >> Halting!",0,24);
	stopints();
	hlt();
}


void ExceptionGpf(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> General Protection Fault >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionPageFault(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> Page Fault >> Halting!",0,24);
	stopints();
	hlt();
}

void ExceptionFpuError(struct InterruptInfo *c){
	kd_set_color(0xCF);
	kd_puts_xy(">>KERNEL PANIC>> FPU Error >> Halting!",0,24);
	stopints();
	hlt();
}

void InterruptTest(struct InterruptInfo *c){
	kd_puts_xy("Int Test",0,12);
}


volatile interrupt_hook int_hooks[256];
volatile struct idt_entry idt[256];
volatile struct idt_ptr idtp;

void InitIdt(){
	uint8_t i;
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (uint32_t)&idt;
	memset((char*)&idt, 0, sizeof(struct idt_entry) * 256);
	RemapIrqs();
	
	for(i=0;i<8;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_NORMAL),0x10,0x8E);
	}
	for(i=8;i<15;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_NO_ERR),0x10,0x8E);
	}
	for(i=15;i<32;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_NORMAL),0x10,0x8E);
	}
	for(i=32;i<40;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_IRQ_M),0x10,0x8E);
	}
	for(i=40;i<49;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_IRQ_S),0x10,0x8E);
	}
	for(i=49;i<0xFF;i++){
		idt_set_gate(i,CreateInterruptStub(i,INTERRUPT_NORMAL),0x10,0x8E);
	}
	
	for(i=0;i<0xFF;i++){
		int_hooks[i]=NULL;
	}
	InstallInterruptHook(0,ExceptionDivideBy0);
	InstallInterruptHook(2,ExceptionNmi);
	InstallInterruptHook(6,ExceptionInvalidOp);
	InstallInterruptHook(7,ExceptionNoDevice);
	InstallInterruptHook(8,ExceptionDoubleFault);
	InstallInterruptHook(10,ExceptionInvalidTss);
	InstallInterruptHook(11,ExceptionSegNotPresent);
	InstallInterruptHook(12,ExceptionStack);
	InstallInterruptHook(13,ExceptionGpf);
	InstallInterruptHook(14,ExceptionPageFault);
	InstallInterruptHook(16,ExceptionFpuError);
	InstallInterruptHook(80,InterruptTest);
	//InstallInterruptHook(17,ExceptionAlignmentCheck);
	
	
	idt_load();
}




/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(uint8_t num, void (*base), uint16_t sel, uint8_t flags) {
	uint32_t base2;
	base2=(uint32_t)base; /*change to a non pointer to do maths*/
	idt[num].base_lo=base2 & 0xFFFF;
	idt[num].base_hi=(base2 >> 16) & 0xFFFF;
	idt[num].always0=0;
	idt[num].flags=flags;
	idt[num].sel=sel;
}

//	0x6A,0, //push 0 <change this to nops if special int



/**This is one heck of a function, but it works quite well...
This function takes the assembly routine, int_template and copies it
into malloc'd memory and makes small modifications(as well as adding a bit of code in hex)
to make it so that C functions can tell what interrupt was called and what not
note, this should only be used once for each interrupt number, and should only be used during init**/
void *CreateInterruptStub(uint8_t num, uint8_t type){
	char *tmp;
	switch(type){
		case INTERRUPT_NORMAL:
			tmp=malloc(int_template_size+4);
			memset(tmp,0x90,int_template_size+4);
			tmp[0]=0x6A;
			tmp[1]=0x00; //mean push 0, this is for a dummy error code
			tmp[2]=0x6A;
			tmp[3]=num; //means push <num> this is for interrupt number.
			memcpy((void*)&tmp[4],(void*)&int_template,int_template_size);
			
		break;
		case INTERRUPT_NO_ERR:
			tmp=malloc(int_template_size+2);
			memset(tmp,0x90,int_template_size+2);
			tmp[0]=0x6A;
			tmp[1]=num;
			memcpy((void*)&tmp[2],(void*)&int_template,int_template_size);
		break;
		case INTERRUPT_IRQ_M:
			tmp=malloc(int_template_size+7);
			memset(tmp,0x90,int_template_size+7);
			tmp[0]=0x6A;
			tmp[1]=0x00; //mean push 0, this is for a dummy error code
			tmp[2]=0x6A;
			tmp[3]=num; //means push <num> this is for interrupt number.
			memcpy((void*)&tmp[4],(void*)&int_template,int_template_size);
			tmp[int_template_size+4-1]=0xB0; //mov al,0x20 --this actually overwrites the iret in int_template
			tmp[int_template_size+4+0]=0x20; //^
			tmp[int_template_size+4+1]=0xE6; //out 0x20,al
			tmp[int_template_size+4+2]=0x20; //^
			tmp[int_template_size+4+3]=0xCF; //iret
		break;
		case INTERRUPT_IRQ_S:
			tmp=malloc(int_template_size+9);
			memset(tmp,0x90,int_template_size+9);
			tmp[0]=0x6A;
			tmp[1]=0x00; //mean push 0, this is for a dummy error code
			tmp[2]=0x6A;
			tmp[3]=num; //means push <num> this is for interrupt number.
			memcpy((void*)&tmp[4],(void*)&int_template,int_template_size);
			tmp[int_template_size+4-1]=0xB0; //mov al,0x20 --this actually overwrites the iret in int_template
			tmp[int_template_size+4+0]=0x20; //^
			tmp[int_template_size+4+1]=0xE6; //out 0xA0,al
			tmp[int_template_size+4+2]=0xA0; //^
			tmp[int_template_size+4+3]=0xE6; //out 0x20,al
			tmp[int_template_size+4+4]=0x20; //^
			tmp[int_template_size+4+5]=0xCF; //iret
		break;
		default:
			return NULL;
		break;
	}
	return tmp;
}


int InstallInterruptHook(uint8_t num,interrupt_hook func){
	if(int_hooks[num]!=NULL){return -1;}
	int_hooks[num]=func;
	return 0;
}






void int_catcher(struct InterruptInfo *cpu){
	if(int_hooks[cpu->int_no]==NULL){return;}
	int_hooks[cpu->int_no](cpu);
}





/*
	_int_template: ;compiled once but edited and used as a template
	push byte 0 ;error code
	push byte 0 ;interrupt number
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x0   ; Load the Kernel Data Segment descriptor! -this is changed...
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss,ax
	mov eax, esp   ; Push us the stack
	push eax ;for whatever reason
	mov eax, _int_catcher ;this stays constant
	call eax   ; A special call, preserves the 'eip' register
	pop eax
	pop gstmp=malloc(int_template_size+4);
			memset(tmp,0x90,int_ttmp=malloc(int_template_size+4);
			memset(tmp,0x90,int_template_size+4);emplate_size+4);
	pop fs
	pop es
	pop ds
	popa
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
*/









