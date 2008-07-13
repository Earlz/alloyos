#include <string.h>


void *memmove(char *str1,const char *str2,size_t count){
	size_t i;
	for(i=0;i<count;i++){
		str1[i]=str2[i];
	}
	return str1;
}

void *memcpy(char *str1,const char *str2,size_t count){
	size_t i;
	for(i=0;i<count;i++){
		str1[i]=str2[i];
	}
	return str1;
}

void *memset(char *str1,const char c,size_t count){
	size_t i;
	for(i=0;i<count;i++){
		str1[i]=c;
	}
	return str1;
}





