;<Copyright Header>
;Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
;All rights reserved.
;
;Redistribution and use in source and binary forms, with or without
;modification, are permitted provided that the following conditions
;are met:
;
;1. Redistributions of source code must retain the above copyright
;   notice, this list of conditions and the following disclaimer.
;2. Redistributions in binary form must reproduce the above copyright
;   notice, this list of conditions and the following disclaimer in the
;   documentation and/or other materials provided with the distribution.
;3. The name of the author may not be used to endorse or promote products
;   derived from this software without specific prior written permission.
;   
;THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
;INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
;AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
;THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
;ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;This file is part of the AlloyOS project
;</Copyright Header>

;This file contains all of the "glue" required for devloping an OS in C -- rings included.

global _loader           ; making entry point visible to linker
extern kmain            ; _kmain is defined elsewhere

; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

section .text
align 4
MultiBootHeader:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM

; reserve initial kernel stack space
STACKSIZE equ 0x8000                 

_loader:
   mov esp, 0x000+STACKSIZE           ; set up the stack
   push eax                           ; pass Multiboot magic number
   push ebx                           ; pass Multiboot info structure

   call  kmain                       ; call kernel proper
   cli
   hlt                                ; halt machine should kernel return



global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x8      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss,ax
    jmp 0x10:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret


global idt_load
extern idtp
idt_load:
    lidt [idtp]
ret

extern int_catcher

global int_template
global int_template_size

INT0_STACK_BASE EQU 0x300000
global int_level
int_level: db 0

int_template: ;compiled once but edited and used as a template
;	push byte 0 ;error code
;	push byte 0 ;interrupt number
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x08   ; Load the Kernel Data Segment descriptor! 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss,ax
	mov ebx, esp   ; Push us the stack
	mov eax,0
	mov al,byte [int_level]
	shl eax,12 ;align it to a page
	or eax,INT0_STACK_BASE
	inc byte [int_level]
	mov esp,eax
	push ebx 
	mov eax, int_catcher ;this stays constant
	call eax   ; A special call, preserves the 'eip' register
	
	pop esp
	dec byte [int_level]
	;pop eax
	
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
end_template:
int_template_size: dd (end_template-int_template)

global Interrupt

Interrupt: ;becuase the int instruction is only available with imm8, must use self modifying code
	mov ebp,esp
	add ebp,4
	push eax
	mov al,byte [ebp]
	mov byte [_int_num],al
	db 0xCD
	_int_num: db 0
	pop eax
	ret


