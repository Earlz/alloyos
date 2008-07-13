#ifndef IDT_H
#define IDT_H
#include <stdint.h>
#define INTERRUPT_NORMAL 0
#define INTERRUPT_NO_ERR 1
#define INTERRUPT_IRQ_M 2
#define INTERRUPT_IRQ_S 3

/* Defines an IDT entry */
struct idt_entry {
	uint16_t base_lo;
	uint16_t sel;        /* Our kernel segment goes here! */
	uint8_t always0;     /* This will ALWAYS be set to 0! */
	uint8_t flags;       /* Set using the above table! */
	uint16_t base_hi;
}
__attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
}
__attribute__((packed));

struct InterruptInfo{
	uint32_t ds, es, fs, gs;      /* pushed the segs last */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
	uint32_t int_no, err_code;    /* our 'push byte #' and ecodes do this */
	uint32_t eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
}
__attribute__((packed));


extern void idt_load();
extern volatile struct idt_entry idt[256];
extern volatile struct idt_ptr idtp;

typedef void (*interrupt_hook)(struct InterruptInfo*);
extern volatile interrupt_hook int_hooks[];

extern void* int_template;
extern uint32_t int_template_size;



void idt_set_gate(uint8_t num, void (*base), uint16_t sel, uint8_t flags);
void *CreateInterruptStub(uint8_t num, uint8_t type);
void RemapIrqs(void);
int InstallInterruptHook(uint8_t num,interrupt_hook func);
void InitIdt();

#define IRQ_BASE_INT 32 //add this number to the IRQ number for the interrupt number

#define INT0_STACK_BASE 0x300000 //this area is for temporary interrupt stacks

extern uint8_t int_level;


#endif

