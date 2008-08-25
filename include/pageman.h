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

/**This has all the page management functions, eventually including x86 paging. --Ring 0 (some
functions Ring 3 permissible)**/



#ifndef PAGEMAN_H
#define PAGEMAN_H

#include <stdint.h>

#define NO_BIT 0xFFFFFFFF

#define OWNER_NONE 0 //no owner, usually only for free pages
#define OWNER_KERNEL 1 //owned by kernel, can not be paged out
#define OWNER_PAGEMAN 2 //owned by page manager, can not be paged out
#define OWNER_VIRTUAL 4 //is owned virtually (not by an actual process)
#define OWNER_RESERVED 8 //reserved for special use
#define OWNER_SPECIAL 16 //reserved for special use
#define OWNER_KERNEL_PAGEABLE 32 //owned by kernel, but can be paged out.
#define OWNER_USER 1024 //owned by userspace process then ORed with PID (PIDs are 20bit)

#define MEM_SIZE 32 //32mb assumed memory



extern volatile uint32_t current_memory_owner;

typedef struct{ //16 byte struct
	uint32_t size;
	uint32_t address;
	uint32_t owner;
	uint32_t attributes;
}page_struct;



void SetBits(uint32_t *map,uint32_t num,uint32_t count);
void UnsetBits(uint32_t *map,uint32_t num,uint32_t count);
void DefragmentPages();
void InitPageMan();
void* k_AllocPage_a(uint32_t size,uint32_t owner,uint32_t attributes);
void *k_AllocPage(uint32_t size,uint32_t owner);
void RemoveZeroPages();
int k_FreePage_a(void *address,uint32_t owner,uint32_t attributes);
int k_FreePage(void *address);
int k_CheckPages();




#endif

