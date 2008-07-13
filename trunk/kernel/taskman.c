#include <taskman.h>

process_list *current_process;
process_list *first_process; //this process is always the idle process

thread_list *current_thread;


int init_TaskMan(){
	first_process=malloc(sizeof(process_list); //our idle process
	first_process->process_node.threads=malloc(sizeof(thread_list));
	current_process=malloc(sizeof(process_list); //our kernel process
	current_process->process_node.threads=malloc(sizeof(thread_list));
	first_process->next=current_process; //link the two nodes together.
	current_process->next=first_process; //these lists are supposed to wrap around!
	//initalize everything for the processes
	first_process->thread_count=1;
	current_process->thread_count=1;
	
	first_process->base_address=0x200000; //both are kernel processes so..
	current_process->base_address=0x200000;
	
	first_process->size=0x100000;
	current_process->size=0x100000;
	
	first_process->CR3=0; //no paging for kernel processes
	current_process->CR3=0; 
	
	first_process->owner="System";
	current_process->owner="System";
	
	first_process->name="Idle Process";
	current_process->name="Alloy Kernel";
	
	first_process->
	
	
	
	
}

void IdleProcess(){
	for(;;){}
}




