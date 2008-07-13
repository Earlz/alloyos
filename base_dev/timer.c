#include <base_dev/timer.h>

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
	
	
}





