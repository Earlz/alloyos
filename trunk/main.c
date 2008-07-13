#include <stdint.h>
#include <kdebug.h>
#include <pageman.h>
#include <gdt.h>
#include <idt.h>
#include <stdlib.h>
#include <x86.h>
#include <base_dev/keyboard.h>
#include <base_dev/timer.h>
void *space[5];


void kmain( void* mbd, unsigned int magic ){	
	uint32_t i;
	stopints();
	kd_cls();
	kd_puts_xy("Codename: The Alloy Project",0,0);
	kd_puts_xy("Pre-Alpha Build v0.0.1",0,1);
	kd_puts_xy("Build Date: "__DATE__"",0,2);
	kd_puts_xy("Build Time: "__TIME__"",0,3);
	GdtInstall();
	InitPageMan();
	InitIdt();
	/**Initialize base devices**/
	kbd_Init();
	timer_Init();
	startints();
	
	kd_putc_xy('~',4,4);
	kd_putc_xy('!',5,5);
	for(;;){}
}



