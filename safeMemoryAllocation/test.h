#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "salloc.c"
#ifdef __SAFE_ALLOC
// ALL THE FUNCTIONS
/* Functions local to the program which must not be used in a user defined program */
extern void *__getMemory(void *pointerAddress,unsigned int size);	//For the progam should not be used in your program.
extern unsigned int __pushLinkedList(void *pointerAddress,unsigned int size);	//Push into the linked list.
extern unsigned int __popLinkedList(void *pointerAddress);	//Pop from the linked list.
extern void __updateLinkedList(void *updateAddress,void *newMemoryAddress,unsigned int size); // To update if memory is reallocated
/* The functions that the programmer can use*/
extern unsigned int getMemoryStatus();	//Gets the currrent allocated addresses.
extern void *smalloc(unsigned int size);	//allocated memory and push into the linked list.
extern void *srealloc(void *pointerAddress,unsigned int size);		//reallocates a new piece of memory and updates __memoryTable
extern unsigned int sfree(void *pointerAddress);	//free memory and pop it from the linked list.
extern unsigned int freeAllMemeory();	//free all the allocated memory
#endif
