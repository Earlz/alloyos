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

/**Kernel entry point and initialization --Ring 0**/


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



