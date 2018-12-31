#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __SAFE_ALLOC
#define __SAFE_ALLOC
#endif
/* 
	Using a doubly linked list to store the allocated space
	Please keep in mind this program only support int,char,float,double.(Not quite sure)
	0 -> Success
	1 -> Failure
*/
#ifdef __SAFE_ALLOC
struct __memoryTable
{
	void 	*memoryAddress;
	int 	memorySize;		//Think later if you want to make this pointer variable.
	struct __memoryTable *__leftlink;
	struct __memoryTable *__rightlink;
};
struct __memoryTable *__memoryTableStart__ = NULL,*__memoryTableEnd__ = NULL;
// ALL THE FUNCTIONS
/* Functions local to the program which must not be used in a user defined program */
void *__getMemory(void *pointerAddress,unsigned int size); 		//For the progam should not be used in your program.
int __pushLinkedList(void *pointerAddress,unsigned int size);	//Push into the linked list.
int __popLinkedList(void *pointerAddress);						//Pop from the linked list.
/* The functions that the programmer can use*/
void getMemoryStatus();											//Gets the currrent allocated addresses.
void *smalloc(char *dataType,unsigned int size);				//allocated memory and push into the linked list.
int sfree(void *pointerAddress);								//free memory and pop it from the linked list.
int freeAllMemeory();											//free all the allocated memory
// FUNCTION DEFINITIONS
void *__getMemory(void *pointerAddress,unsigned int size)/* Allocated a node for __memoryTable*/
{
	struct __memoryTable *temp;
	temp = (struct __memoryTable*)malloc(sizeof(struct __memoryTable));
	temp -> memoryAddress = pointerAddress;
	temp -> memorySize = size;
	temp -> __leftlink = NULL;
	temp -> __rightlink = NULL;
	return temp;
}
void getMemoryStatus()
{
	struct __memoryTable *temp;
	if(__memoryTableStart__ == NULL){
		printf(" No allocated memory.\n");
	}
	else{
		temp = __memoryTableStart__;
		while(temp != NULL){
			printf(" Memory Address: %p\n", temp -> memoryAddress);
			printf(" __leftlink    : %p\n", temp -> __leftlink);
			printf(" __rightlink   : %p\n", temp -> __rightlink);
			temp = temp -> __rightlink;
		}
	}
	return;
}
int __pushLinkedList(void *pointerAddress,unsigned int size)
{
	struct __memoryTable *temp;
	temp = __getMemory(pointerAddress,size);
	if(temp == NULL){
		printf(" Cannot push to stack due to insufficient memory.\n");
		return 1;
	}
	else{
		if(__memoryTableStart__ == NULL){
			__memoryTableStart__ = temp;
			__memoryTableEnd__   = temp;
			getMemoryStatus();
			return 0;
		}
		else{
			temp -> __leftlink = __memoryTableEnd__;
			__memoryTableEnd__ -> __rightlink = temp;
			__memoryTableEnd__ = __memoryTableEnd__ -> __leftlink;
			getMemoryStatus();
			return 0;
		}
	}
}
int __popLinkedList(void *pointerAddress)
{
	struct __memoryTable *temp,*prev;
	if(__memoryTableStart__ == NULL){
		printf(" The memory table is empty.\n");
		return 0;
	}
	else{
		temp = __memoryTableStart__;
		if(__memoryTableStart__ == __memoryTableEnd__){
			free(temp);
			__memoryTableStart__ = NULL;
			__memoryTableEnd__ = NULL;
		}
		else{
			while(temp != NULL){
				if(temp -> memoryAddress == pointerAddress){	// I'm not checking for INVALID address condition.
					prev = temp -> __leftlink;
					prev -> __rightlink = temp -> __rightlink;
					free(temp);
					break;
				}
				temp = temp -> __rightlink;
			}	
		}
		getMemoryStatus();
		return 0;
	}
}
void *smalloc(char *dataType,unsigned int size)
{
	void *pointer = NULL;
	pointer = malloc(size);
	if(pointer!=NULL){
		if(__pushLinkedList(pointer,size) == 1){
			printf(" The push into the linked list was unsuccessful.\n");
			free(pointer);
		}
	}
	return pointer;
}
int sfree(void *pointerAddress)
{
	if(pointerAddress!=NULL){
		__popLinkedList(pointerAddress);
		return 0;
	}
	else{
		printf(" Pointer is NULL.\n");
		return 0;
	}
}
int freeAllMemeory()
{
	struct __memoryTable *temp;
	if(__memoryTableStart__ == NULL){
		printf(" No allocated memory.\n");
		return 0;
	}
	else{
		temp = __memoryTableStart__;
		while(temp != NULL){
			__popLinkedList(temp);
			temp = temp -> __rightlink;
		}
		return 0;
	}
}
#endif