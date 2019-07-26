#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include "salloc.c"
#ifdef __SAFE_ALLOC
// ALL THE FUNCTIONS
extern unsigned int getMemoryStatus();	//Gets the currrent allocated addresses.
unsigned int getMemoryStatusTable(); //Gets the currrent allocated addresses in a tabular form.
extern void *smalloc(unsigned int size,char *label);	//allocated memory and push into the linked list.
extern void *scalloc(unsigned int arraySize,unsigned int size,char *label);
extern void *srealloc(void *pointerAddress,unsigned int size);		//reallocates a new piece of memory and updates __memoryTable
extern unsigned int sfree(void *pointerAddress);	//free memory and pop it from the linked list.
extern unsigned int freeAllMemory();	//free all the allocated memory
//extern char *concat(int number,...); //Concatenates the number of arguments are returns the addres of newly allocated memory.
#endif
