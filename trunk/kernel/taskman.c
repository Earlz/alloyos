#include <taskman.h>
#include <stdlib.h>
process_list *current_process;
process_list *first_process; //this process is always the idle process

thread_list *current_thread;

volatile int multitasking=0;

int init_TaskMan(){
	first_process=malloc(sizeof(process_list)); //our idle process
	first_process->process_node.threads=malloc(sizeof(thread_list));
	current_process=malloc(sizeof(process_list)); //our kernel process
	current_process->process_node.threads=malloc(sizeof(thread_list));
	first_process->next=current_process; //link the two nodes together.
	current_process->next=first_process; //these lists are supposed to wrap around!
	first_process->process_node.threads->next=first_process->process_node.threads;
	//initalize everything for the processes
	process *first_process_=&first_process->process_node;
	process *current_process_=&current_process->process_node;
	first_process_->thread_count=1;
	current_process_->thread_count=1;
	
	first_process_->base_address=0x200000; //both are kernel processes so..
	current_process_->base_address=0x200000;
	
	first_process_->size=0x100000;
	current_process_->size=0x100000;
	
	first_process_->CR3=0; //no paging for kernel processes
	current_process_->CR3=0; 
	
	first_process_->owner="System";
	current_process_->owner="System";
	
	first_process_->name="Idle Process";
	current_process_->name="Alloy Kernel";
	
	first_process_->base_priority=PRIORITY0;
	current_process_->base_priority=PRIORITY4;
	
	first_process_->attributes=KERNEL_PROCESS;
	current_process_->attributes=KERNEL_PROCESS;
	
	thread *it=&first_process->process_node.threads->thread_node; //idle thread
	thread *kt=&current_process->process_node.threads->thread_node; //kernel thread
	
	it->PID=(uint32_t)&first_process->process_node;
	it->priority=PRIORITY0;
	it->attributes=0;
	it->context=malloc(256);
	it->stack_size=256;
	it->context=it->context+256-sizeof(struct InterruptInfo);
	//the context pointer should be set to where ESP would be at the time of an interrupt
	//after the context info was pushed.
	it->context->ds=0x08;
	it->context->es=0x08;
	it->context->gs=0x08;
	it->context->fs=0x08;
	it->context->ss=0x08;
	it->context->cs=0x10;
	it->context->eflags=0x200; //all flags 0 except for IF
	it->context->useresp=((uint32_t)it->context)+256;
	//general registers are all undefined, ESP is not popped by popa either...
	it->context->eip=(uint32_t)&IdleProcess;
	
	//kernel thread's turn...
	kt->PID=(uint32_t)&current_process->process_node;
	kt->priority=PRIORITY4;
	kt->attributes=0;
	kt->context=malloc(4096);
	kt->stack_size=4096;
	kt->context=it->context+4096-sizeof(struct InterruptInfo);
	//the context pointer should be set to where ESP would be at the time of an interrupt
	//after the context info was pushed.
	kt->context->ds=0x08;
	kt->context->es=0x08;
	kt->context->gs=0x08;
	kt->context->fs=0x08;
	kt->context->ss=0x08;
	kt->context->cs=0x10;
	kt->context->eflags=0x200; //all flags 0 except for IF
	kt->context->useresp=((uint32_t)it->context)+4096;
	//general registers are all undefined, ESP is not popped by popa either...
	kt->context->eip=(uint32_t)&KernelProcessEntry;
	
	multitasking=1;
	
	for(;;){} //should wait until a timer IRQ for multitasking to kick in.
	
	return 1;
	
}

void IdleProcess(){
	for(;;){}
}

void KernelProcessEntry(){
	
	for(;;){}
}




void ScheduleTasks(){
	
	
}







