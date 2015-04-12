The Alloy project is a unix based OS. It is a microkernel which has it's drivers outside of the kernel space. This is a research project and is for the i386 platform. it implements software task switching.

The current work that is done on this project is GDT, IDT, IRQ hooking, keyboard, video, and timer(PIT) driver.

This project may also attempt to implement a new type of driver which, compiled once for a single target, will work on any OS that implements the driver framework... This is planned, though it may not get done...

currently, it uses the GRUB bootloader, though this may change as the kernel does not depend upon it(it doesn't use multiboot or anything)

IPC is currently not designed..