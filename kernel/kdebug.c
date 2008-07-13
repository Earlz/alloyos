#include <kdebug.h>
#include <stdint.h>
#include <base_dev/keyboard.h>

uint8_t *vram=(uint8_t *)0xB8000;

uint8_t kd_color=0x0F;

void kd_set_color(uint8_t color){
	kd_color=color;
}

uint8_t kd_get_color(){
	return kd_color;
}

void kd_putc_xy(char c,uint8_t x,uint8_t y){
	vram[(x+(y*80))*2]=c;
	vram[(x+(y*80))*2+1]=kd_color;
}

void kd_puts_xy(char *str,uint8_t x,uint8_t y){
	uint8_t i=0;
	while(str[i]!=0){
		kd_putc_xy(str[i],x+i,y);
		i++;
	}
}



void kd_cls(){
	uint32_t i;
	for(i=0;i<=((80*25*2));i++){
		*(uint32_t*)&vram[i]=0;
	}
}


void kd_waitkey(){
	kbd_GetKey();
}


