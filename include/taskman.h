#ifndef TASKMAN_H
#define TASKMAN_H

#include <idt.h>
#include <stdint.h>

typedef struct{
	struct InterruptInfo *context; //CPU state
							//NOTE!! the address of this should be reloaded as the ESP
	uint32_t PID; //owner process
	uint32_t attributes;
	uint8_t priority;
}thread;

typedef struct{
	thread thread_node;
	void *next;
}thread_list;

typedef struct{
	thread_list *threads;
	uint8_t thread_count;
	uint32_t base_address;
	size_t size;
	uint32_t CR3; //page directory stuff
	void *reserved_file_node; //this will be completed when files are implemented
	char *owner; //user name
	char *name; //process name
	uint8_t base_priority; //priority that threads are defaultly set to.
	uint32_t attributes;
	
}process;

typedef struct{
	process process_node;
	void *next;
}process_list;


//process attributes
#define KERNEL_PROCESS 1


#define PRIORITY_DEFAULT 0
//priority 0 is very small time slices, priority 6 is big time slices
#define PRIORITY0 1
#define PRIORITY1 2
#define PRIORITY2 3
#define PRIORITY3 4
#define PRIORITY4 5
#define PRIORITY5 6
#define PRIORITY6 7

#define PRIORITY_REALTIME 0xFF






#endif


