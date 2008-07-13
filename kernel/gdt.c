#include <gdt.h>


struct gdt_entry gdt[GDT_LIMIT];
struct gdt_ptr gp;

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */







/* Setup a descriptor in the Global Descriptor Table */
uint16_t GdtSetGate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran){
	/* Setup the descriptor base address */

	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
	return num;
}









/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */


void GdtInstall() {
	gp.limit = (sizeof(struct gdt_entry) * GDT_LIMIT) - 1;
	gp.base = (uint32_t) &gdt;
	GdtSetGate(0, 0, 0, 0, 0);

    //code segment; flat, 4GB limit, ring 0; intended for kernel only
	GdtSetGate(2, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    //data segment; flat, 4GB limit, ring 0; intended for kernel only
	GdtSetGate(1, 0, 0xFFFFFFFF, 0x92, 0xCF);



    //Application segments

	gdt_flush();
}



