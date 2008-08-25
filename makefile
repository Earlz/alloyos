#<Copyright Header>
#Copyright (c) 2007 - 2008 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions
#are met:
#
#1. Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#2. Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#3. The name of the author may not be used to endorse or promote products
#   derived from this software without specific prior written permission.
#   
#THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
#INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
#AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
#THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#This file is part of the AlloyOS project
#</Copyright Header>


_CFLAGS=-Wall -nostdlib -nostartfiles -nodefaultlibs -I ./include -fno-builtin
_OBJS=objs/glue.o objs/main.o objs/kernel/string.o objs/kernel/pageman.o objs/kernel/kdebug.o objs/kernel/gdt.o objs/kernel/idt.o objs/kernel/x86.o objs/lib/liballoc/liballoc.o objs/lib/liballoc/liballoc_hooks.o objs/base_dev/keyboard.o objs/base_dev/timer.o objs/kernel/taskman.o

default:
	nasm -f elf -o objs/glue.o glue.asm
	gcc -o objs/main.o -c main.c $(_CFLAGS)
	gcc -o objs/kernel/pageman.o -c kernel/pageman.c $(_CFLAGS)
	gcc -o objs/kernel/kdebug.o -c kernel/kdebug.c $(_CFLAGS)
	gcc -o objs/kernel/string.o -c kernel/string.c $(_CFLAGS)
	gcc -o objs/kernel/gdt.o -c kernel/gdt.c $(_CFLAGS)
	gcc -o objs/kernel/idt.o -c kernel/idt.c $(_CFLAGS)
	gcc -o objs/kernel/x86.o -c kernel/x86.c $(_CFLAGS)
	gcc -o objs/kernel/taskman.o -c kernel/taskman.c $(_CFLAGS)
	gcc -o objs/lib/liballoc/liballoc.o -c lib/liballoc/liballoc.c $(_CFLAGS)
	gcc -o objs/lib/liballoc/liballoc_hooks.o -c lib/liballoc/liballoc_hooks.c $(_CFLAGS)
	gcc -o objs/base_dev/keyboard.o -c base_dev/keyboard.c $(_CFLAGS)
	gcc -o objs/base_dev/timer.o -c base_dev/timer.c $(_CFLAGS)
	ld -T linker.ld -o kernel.bin $(_OBJS)
	cat boot/stage1 boot/stage2 pad kernel.bin > floppy.img

