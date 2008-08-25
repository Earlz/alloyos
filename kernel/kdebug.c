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

/**kernel debug functions -- Ring 0**/

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






