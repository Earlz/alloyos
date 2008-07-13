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

