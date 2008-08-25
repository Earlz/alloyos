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

/**This include file has all of the structures and functions for OS-dependent kernel methods
of task switching.
**/


#ifndef TASKMAN_H
#define TASKMAN_H

#include <idt.h>
#include <stdint.h>

typedef struct{
	struct InterruptInfo *context; //CPU state
							//NOTE!! the address of this should be reloaded as the ESP
	uint32_t PID; //owner process
	uint32_t stack_size;
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

extern volatile int multitasking;

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


void IdleProcess();
void KernelProcessEntry();
void ScheduleTasks();



#endif


