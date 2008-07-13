#include <pageman.h>
#include <x86.h>


int liballoc_lock(){
	stopints();
	return 0;
}

int liballoc_unlock(){
	//startints();
	//not ready to start ints yet
	return 0;
}

void* liballoc_alloc(int num){
	return k_AllocPage(num,current_memory_owner);
}
int liballoc_free(void* ptr,int num){
	return k_FreePage(ptr);
}


	
