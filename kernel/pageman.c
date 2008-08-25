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


#include <stdint.h>
#include <kdebug.h>
#include <pageman.h>
#include <string.h>
/*bitmap functions required for page management*/

/*This is updated everytime memory needs to be owned by someone else, such as a thread or process switch*/
volatile uint32_t current_memory_owner=OWNER_KERNEL;

/**SetBits functions is fully tested and fairly well optimized**/
void SetBits(uint32_t *map,uint32_t num,uint32_t count){
	uint32_t i, int_num,bit_num;
	if(count==0){
		return;
	}
	int_num=num/32;
	bit_num=num%32;
	if(count==1){
		map[int_num]|=1<<bit_num;
		return;
	}
	if(count<=32){ /*complete tested for this switch off of count*/
		if(bit_num==0){
			map[int_num]|=(2<<(count-1))-1;
			return;
		}else{
			if((bit_num+count)>32){ //must be aligned on dword
				map[int_num]|=((2<<31)-1)<<bit_num;
				int_num++;
				count-=(32-bit_num);
				bit_num=0;
			}
			map[int_num]|=((2<<(count-1))-1)<<bit_num;
			return;
		}
		
	}else{//if setting more than 32 bits
		uint32_t int_max,bit_max;
		int_max=count/32;
		bit_max=(count%32);
		if(int_max==1){ //must check for unalignment for >32 <64 bits
			if(num%32!=0){
				int_max=0;
				bit_max+=32;
				bit_max-=(32-bit_num);
			}
		}
		//set bits to get dword alignment
		map[int_num]|=((2<<31)-1)<<bit_num;
		//set full dwords now
		for(i=1;i<int_max;i++){
			map[int_num+i]=0xFFFFFFFF;
		}
		//set remaining unaligned bits
		if((bit_max+bit_num)==0){return;}
		map[int_num+int_max]|=((1<<((bit_max+bit_num)))-1);
	}
}

/**UnsetBits uses the same base alogarithm as SetBits, it is fully tested, but
   if any bugs are found in SetBits, the bug will also be seen in UnsetBits**/
void UnsetBits(uint32_t *map,uint32_t num,uint32_t count){
	uint32_t i, int_num,bit_num;
	if(count==0){
		return;
	}
	int_num=num/32;
	bit_num=num%32;
	if(count==1){
		map[int_num]&=0xFFFFFFFF^(1<<bit_num);
		return;
	}
	if(count<=32){ /*complete tested for this switch off of count*/
		if(bit_num==0){
			map[int_num]&=0xFFFFFFFF^((2<<(count-1))-1);
			return;
		}else{
			if((bit_num+count)>32){ //must be aligned on dword
				map[int_num]&=0xFFFFFFFF^(((2<<31)-1)<<bit_num);
				int_num++;
				count-=(32-bit_num);
				bit_num=0;
			}
			map[int_num]&=0xFFFFFFFF^(((2<<(count-1))-1)<<bit_num);
			return;
		}
		
	}else{//if setting more than 32 bits
		uint32_t int_max,bit_max;
		int_max=count/32;
		bit_max=(count%32);
		if(int_max==1){ //must check for unalignment for >32 <64 bits
			if(num%32!=0){
				int_max=0;
				bit_max+=32;
				bit_max-=(32-bit_num);
			}
		}
		//set bits to get dword alignment
		map[int_num]&=0xFFFFFFFF^(((2<<31)-1)<<bit_num);
		//set full dwords now
		for(i=1;i<int_max;i++){
			map[int_num+i]=0;
		}
		//set remaining unaligned bits
		if((bit_max+bit_num)==0){return;}
		map[int_num+int_max]&=0xFFFFFFFF^((1<<((bit_max+bit_num)))-1);
	}
}



uint32_t FindUnsetBits(uint32_t *map, uint32_t count, size_t size){
	uint32_t i,j;
	if((count*32)>(size*32)){ //if there never was enough space
		return NO_BIT;
	}
	for(i=0;i<size;i++){
		if(map[i]!=0xFFFFFFFF){
			if(count==1){
				for(j=0;j<=31;j++){
					if((map[i]&(1<<j))!=0){
						return (i*32)+j;
					}
				}
				return NO_BIT;
			}
			if(count<=32){
				if(map[i]==0){ //if only it was always this easy...
					return i*32;
				}
				for(j=0;j<count;j++){
					
				}
				
				
			}
				
			
			
			
			
		}
		if((count*32)>((size-i)*32)){return 0xFFFFFFFF;} //if not enough space
	}
	
	
	
	return 0;
}

uint32_t FindSetBits(uint32_t *map,uint32_t count, size_t size){


	return 0;
}




volatile uint32_t count_free; //number of objects in list
volatile uint32_t count_used; //number of objects in list
volatile page_struct *free_pages;
volatile page_struct *used_pages;

void InitPageMan(){
	free_pages=(page_struct *)0x200000; //2meg
	used_pages=(page_struct *)0x280000; //2.5meg
	used_pages[0].size=0x80000/4096;
	used_pages[0].address=0x200000/4096;
	used_pages[0].owner=OWNER_PAGEMAN;
	used_pages[0].attributes=0;
	
	used_pages[1].size=0x80000/4096;
	used_pages[1].address=0x280000/4096;
	used_pages[1].owner=OWNER_PAGEMAN;
	used_pages[1].attributes=0;
	
	used_pages[2].size=0x100000/4096;
	used_pages[2].address=0;
	used_pages[2].owner=OWNER_RESERVED|OWNER_SPECIAL;
	used_pages[2].attributes=0;
	
	used_pages[3].size=0x100000/4096;
	used_pages[3].address=0x100000/4096;
	used_pages[3].owner=OWNER_KERNEL;
	used_pages[3].attributes=0;
	
	used_pages[4].size=0x100000/4096; /*0x3000 0000 to 0x4000 0000 is reserved for stacks and such*/ 
	used_pages[4].address=0x300000/4096;
	used_pages[4].owner=OWNER_KERNEL;
	used_pages[4].attributes=0;
	
	count_used=5;
	free_pages[0].size=0x100000*(MEM_SIZE-3)/4096;
	free_pages[0].address=0x400000/4096;
	free_pages[0].owner=OWNER_NONE;
	free_pages[0].attributes=0;
	count_free=1;
	
}



//size is how many pages
void* k_AllocPage_a(uint32_t size,uint32_t owner,uint32_t attributes){
	uint32_t i,address=0;
	char t=0;
	DefragmentPages();
	RemoveZeroPages();
	for(i=0;i<count_free;i++){
		if(free_pages[i].size>=size){
			free_pages[i].size-=size;
			address=free_pages[i].address;
			free_pages[i].address=address+size;
			used_pages[count_used].size=size;
			used_pages[count_used].address=address;
			used_pages[count_used].owner=owner;
			used_pages[count_used].attributes=attributes;
			count_used++;
			return (void*)(address*4096);
		}
		if(i==(count_free-1)){
			
			
			if(address==0xFFFFFFFF){
				if(t==1){
					kd_putc_xy('P',10,12);
				}
				return NULL;
			}
			uint32_t k;
			for(k=0;k<30;k++){
				RemoveZeroPages();
				DefragmentPages();
				
			}
			RemoveZeroPages();
			if(free_pages[0].size==0){
				kd_putc_xy('t',9,5);
			}
			if((k_CheckPages()!=0) || (count_free>10)){
				kd_putc_xy('n',8,5);
			}
			address=0xFFFFFFFF;
			i=0;
			t=1;
		}
	}
	if(t==1){
		kd_putc_xy('P',10,12);
	}
	return NULL;
}

void *k_AllocPage(uint32_t size,uint32_t owner){
	return k_AllocPage_a(size,owner,0);
}

int k_FreePage_a(void *address,uint32_t owner,uint32_t attributes){
	uint32_t add=((uint32_t)address)/4096;
	uint32_t i,size;
	for(i=0;i<count_used;i++){
		if(used_pages[i].address==add){
			size=used_pages[i].size;
			used_pages[i].size=0;
			used_pages[i].owner=OWNER_NONE;
			free_pages[count_free].size=size;
			free_pages[count_free].address=add;
			free_pages[count_free].owner=owner;
			free_pages[count_free].attributes=attributes;
			count_free++;
			return 0;
		}
	}
	return -1;
}

int k_FreePage(void *address){
	return k_FreePage_a(address,OWNER_NONE,0);
}


void DefragmentPages(){
	uint32_t i,j;
	uint32_t last_address;
	for(j=0;j<count_free;j++){
		if(free_pages[j].size==0){continue;} //if page is zeroed out, skip it
		last_address=free_pages[j].address+free_pages[j].size;
		for(i=0;i<count_free;i++){
			if(j==i){i++;} //skip this bit
			if(i==count_free){continue;}
			if(free_pages[i].size==0){continue;}
			if(free_pages[i].address==last_address){
				kd_putc_xy('a',3,5);
				if(free_pages[i].owner==free_pages[j].owner){
					kd_putc_xy('o',4,5);
					free_pages[j].size+=free_pages[i].size;
					free_pages[i].size=0; //zero out the defragged page
				}
			}
		}
	}
}

void RemoveZeroPages(){
	uint32_t i;
	for(i=0;i<count_free;i++){
		if(free_pages[i].size==0){
			memmove((char*)&free_pages[i],(char*)&free_pages[i+1],(count_free-i+1)*sizeof(page_struct));
			i--;
			count_free--;
		}
	}
	for(i=0;i<count_used;i++){
		if(used_pages[i].size==0){
			memmove((char*)&used_pages[i],(char*)&used_pages[i+1],(count_used-i+1)*sizeof(page_struct));
			i--;
			count_used--;
		}
	}


}

//This will calculate the total amount of space used and free pages are marked for
//and if it isn't what it should be, it returns -1, if it's right, it returns 0
int k_CheckPages(){
	uint32_t i;
	uint32_t total_size=0;
	for(i=0;i<count_free;i++){
		total_size+=free_pages[i].size;
	}
	for(i=0;i<count_used;i++){
		total_size+=used_pages[i].size;
	}
	if(total_size!=(0x100000*MEM_SIZE/4096)){
		return -1;
	}else{
		return 0;
	}
	
}








