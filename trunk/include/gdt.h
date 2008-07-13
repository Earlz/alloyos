#ifndef GDT_H
#define GDT_H
#include <stdint.h>


struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity; //has limit in tss
	unsigned char base_high;
}
__attribute__((packed));


struct gdt_entry_bits
{
	unsigned short limit_low;
	unsigned base_low : 24;
     //attribute byte split into bitfields
	unsigned char accessed :1;
	unsigned char read_write :1; //readable for code, writable for data
	unsigned char conforming_expand_down :1; //conforming for code, expand down for data
	unsigned char code :1; //1 for code, 0 for data
	unsigned char always_1 :1; //should be 1 for everything but TSS and LDT
	unsigned char DPL :2; //priveledge level
	unsigned char present :1;
     //and now into granularity
	unsigned char limit_high :4;
	unsigned char available :1;
	unsigned char always_0 :1; //should always be 0
	unsigned char big :1; //32bit opcodes for code, dword stack for data
	unsigned char gran :1; //1 to use 4k page addressing, 0 for byte addressing
	unsigned char base_high :8;
}
__attribute__((packed));


/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
}
__attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */

#define GDT_LIMIT 10


extern struct gdt_entry gdt[GDT_LIMIT];
extern struct gdt_ptr gp;
extern void gdt_flush(); //asm function

void GdtInstall();
uint16_t GdtSetGate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran);


#endif

