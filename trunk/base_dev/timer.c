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

/**kernel PIT functions. -- Ring 0*/



#include <base_dev/timer.h>
#include <taskman.h>


volatile uint32_t timer_ticks=0;

void timer_SetHz(uint32_t hz) /*100 means 100 timer ticks a second*/
{
	uint32_t divisor = 1193180 / hz;       /* Calculate our divisor */
	outportb(0x43, 0x36);             /* Set our command byte 0x36 */
	outportb(0x40, divisor);   /* Set low byte of divisor */
	outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}



int timer_Init(){
	timer_SetHz(TIMER_INTERVAL);
	return InstallInterruptHook(IRQ_BASE_INT+0,&timer_Irq0Handler);
}

volatile uint32_t timer2=0;

void timer_Irq0Handler(struct InterruptInfo *r){
	timer_ticks++;
	timer2++;
	kd_putc_xy(timer_ticks,78,24);
	if(timer2==100){
		timer2=0;
	}
	if(timer2==0){
		kd_putc_xy('|',79,24);
	}
	if(timer2==25){
		kd_putc_xy('/',79,24);
	}
	if(timer2==50){
		kd_putc_xy('-',79,24);
	}
	if(timer2==75){
		kd_putc_xy('\\',79,24);
	}
	
	if(multitasking==1){
		ScheduleTasks();
	}
	
	
}





