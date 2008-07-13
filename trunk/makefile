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

