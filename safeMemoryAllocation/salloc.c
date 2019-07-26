#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __SAFE_ALLOC
#define __SAFE_ALLOC
#endif
/* 
	Using a doubly linked list to store the allocated space
	0 -> Success
	1 -> Failure
*/
#ifdef __SAFE_ALLOC
struct __memoryTable
{
	//int 	memoryId;
	char 	*pointerName;
	void 	*memoryAddress;
	unsigned int 	memorySize;		//Think later if you want to make this pointer variable.
	struct __memoryTable *__leftlink;
	struct __memoryTable *__rightlink;
};
struct __memoryTable *__memoryTableStart__ = NULL,*__memoryTableEnd__ = NULL;

// ALL THE FUNCTIONS
/* Functions local to the program which must not be used in a user defined program */
void *__getMemory(void *pointerAddress,unsigned int size,char *label);	//For the progam should not be used in your program.
unsigned int __pushLinkedList(void *pointerAddress,unsigned int size,char *label);	//Push into the linked list.
unsigned int __popLinkedList(void *pointerAddress);	//Pop from the linked list.
void __updateLinkedList(void *updateAddress,void *newMemoryAddress,unsigned int size); // To update if memory is reallocated
/* The functions that the programmer can use*/
unsigned int getMemoryStatus();	//Gets the currrent allocated addresses.
unsigned int getMemoryStatusTable(); //Gets the currrent allocated addresses in a tabular form.
void *smalloc(unsigned int size,char *label);	//allocated memory and push into the linked list.
//void *smalloc(unsigned int size);	//allocated memory and push into the linked list.
void *scalloc(unsigned int arraySize,unsigned int size,char *label);
void *srealloc(void *pointerAddress,unsigned int size);		//reallocates a new piece of memory and updates __memoryTable
unsigned int sfree(void *pointerAddress);	//free memory and pop it from the linked list.
unsigned int freeAllMemory();	//free all the allocated memory

// FUNCTION DEFINITIONS
void *__getMemory(void *pointerAddress,unsigned int size,char* label)/* Allocated a node for __memoryTable*/
{
	struct __memoryTable *temp;
	temp = (struct __memoryTable*)malloc(sizeof(struct __memoryTable));
	temp -> pointerName = strcpy(malloc(strlen(label)),label);
	temp -> memoryAddress = pointerAddress;
	temp -> memorySize = size;
	temp -> __leftlink = NULL;
	temp -> __rightlink = NULL;
	return temp;
}
unsigned int getMemoryStatus()
{
	unsigned int count = 0;
	struct __memoryTable *temp;
	if(__memoryTableStart__ == NULL){
		//printf(" No allocated memory.\n");
		return 0;
	}
	else{
		printf(" The memory table is:\n");
		temp = __memoryTableStart__;
		while(temp != NULL){
			count++;
			printf(" Memory Address: %p\n", temp -> memoryAddress);
			printf(" Memory lable  : %s\n", temp -> pointerName);
			printf(" Memory size   : %d\n", temp -> memorySize	);
			printf(" __leftlink    : %p\n", temp -> __leftlink);
			printf(" __rightlink   : %p\n", temp -> __rightlink);
			temp = temp -> __rightlink;
			printf("\n");
		}
		printf(" End of memory table.\n");
		return count;
	}
}
unsigned int getMemoryStatusTable()
{
    unsigned int count = 0;
	struct __memoryTable *temp;
	if(__memoryTableStart__ == NULL){
		//printf(" No allocated memory.\n");
		return 0;
	}
	else{
        char seperator[] = "+------+--------------------------+----------------------+----------------+";        
        char header[]    = "| SLNO |          LABEL           |    MEMROY ADDRESS    |      SIZE      |";

        void printLine(int slno,char *label,void *memAddr,int size){
            printf("+  %3d + %-25s+ %-20p + %14d +\n",slno,label,memAddr,size);
        }

        temp = __memoryTableStart__;
        printf("%s\n",seperator);
        printf("%s\n",header);
        printf("%s\n",seperator);
        while(temp != NULL){
            count++;
            printLine(count,temp->pointerName,temp->memoryAddress,temp->memorySize);
            printf("%s\n",seperator);
            temp = temp -> __rightlink;
        }
        return count;
    }
}


unsigned int __pushLinkedList(void *pointerAddress,unsigned int size,char *label){
	struct __memoryTable *temp;
	temp = __getMemory(pointerAddress,size,label);
	if(temp == NULL){
		//printf(" Cannot push to linked list due to insufficient memory.\n");
		return 1;
	}
	else{
		//printf(" I - __memoryTableStart__ = %p\n", __memoryTableStart__);
		//printf(" I - __memoryTableEnd__   = %p\n", __memoryTableEnd__);
		//printf(" The memory address to be inserted is: %p\n", temp);
		if(__memoryTableStart__ == NULL){
			__memoryTableStart__ = temp;
			__memoryTableEnd__   = temp;
		}
		else{
			temp -> __leftlink = __memoryTableEnd__;
			__memoryTableEnd__ -> __rightlink = temp;
			__memoryTableEnd__ = __memoryTableEnd__ -> __rightlink;
		}
		//printf(" O - __memoryTableStart__ = %p\n", __memoryTableStart__);
		//printf(" O - __memoryTableEnd__   = %p\n", __memoryTableEnd__);
		//getMemoryStatus();
		return 0;
	}
}
void free_node(struct __memoryTable *pointer)
{
	free(pointer->pointerName);
	free(pointer);
}
unsigned int __popLinkedList(void *pointerAddress) // Code can be optimizes to return a proper value
{
	struct __memoryTable *temp,*prev;
	if(__memoryTableStart__ == NULL){
		//printf(" The memory table is empty.\n");
		return 0;
	}
	else{
		//printf(" I - __memoryTableStart__ = %p\n", __memoryTableStart__);
		//printf(" I - __memoryTableEnd__   = %p\n", __memoryTableEnd__);
		temp = __memoryTableStart__;
		if(__memoryTableStart__ == __memoryTableEnd__){
			//printf(" 1) The memory getting deallocated is: %p\n", temp -> memoryAddress);
			free_node(temp);
			__memoryTableStart__ = NULL;
			__memoryTableEnd__ = NULL;
		}
		else{
			while(temp != NULL){
				if(temp -> memoryAddress == pointerAddress){	// I'm not checking for INVALID address condition.
					//printf(" 2) The memory getting deallocated is: %p\n", temp -> memoryAddress);
					if(temp == __memoryTableStart__){
						__memoryTableStart__ = __memoryTableStart__ -> __rightlink;
						__memoryTableStart__ -> __leftlink = NULL;
					}
					else if(temp == __memoryTableEnd__){
						__memoryTableEnd__ = __memoryTableEnd__ -> __leftlink;
						__memoryTableEnd__ -> __rightlink = NULL;
					}
					else{
						prev = temp -> __leftlink;
						prev -> __rightlink = temp -> __rightlink;
					}
					free_node(temp);
					break;
				}
				temp = temp -> __rightlink;
			}	
		}
		//getMemoryStatus();
		//printf(" O - __memoryTableStart__ = %p\n", __memoryTableStart__);
		//printf(" O - __memoryTableEnd__   = %p\n", __memoryTableEnd__);
		return 0;
	}
}
void __updateLinkedList(void *updateAddress,void *newMemoryAddress,unsigned int size)
{
	struct __memoryTable *temp;
	temp = updateAddress;
	temp -> memoryAddress = newMemoryAddress;
	temp -> memorySize = size;
}
void *smalloc(unsigned int size,char *label)
{
	void *pointer = NULL;
	pointer = malloc(size);
	if(pointer!=NULL){
		if(__pushLinkedList(pointer,size,label) == 1){
			//printf(" The push into the linked list was unsuccessful.\n");
			free_node(pointer);
		}
	}
	//printf(" The allocated memory location is: %p\n", pointer);
	return pointer;
}
/*
void *smalloc(unsigned int size)
{
	void *pointer = NULL;
	pointer = malloc(size);
	if(pointer!=NULL){
		if(__pushLinkedList(pointer,size,"no_label") == 1){
			//printf(" The push into the linked list was unsuccessful.\n");
			free_node(pointer);
		}
	}
	//printf(" The allocated memory location is: %p\n", pointer);
	return pointer;
}
*/
void *scalloc(unsigned int arraySize,unsigned int size,char *label)
{
	void *pointer = NULL;
	pointer = calloc(arraySize,size);
	if(pointer!=NULL){
		if(__pushLinkedList(pointer,size,"no_label") == 1){
			//printf(" The push into the linked list was unsuccessful.\n");
			free_node(pointer);
		}
	}
	//printf(" The allocated memory location is: %p\n", pointer);
	return pointer;	
}
/*
void *scalloc(unsigned int arraySize,unsigned int size)
{
	void *pointer = NULL;
	pointer = calloc(arraySize,size);
	if(pointer!=NULL){
		if(__pushLinkedList(pointer,size,"no_label") == 1){
			//printf(" The push into the linked list was unsuccessful.\n");
			free_node(pointer);
		}
	}
	//printf(" The allocated memory location is: %p\n", pointer);
	return pointer;	
}
*/
void* srealloc(void *pointerAddress,unsigned int size) /* Returns NULL if an error occured*/
{
	struct __memoryTable *temp;
	void *pointer;
	unsigned int flag = 0;
	if(pointerAddress == NULL){
		//printf(" The memoryAddress is null, you first need to allocate memory.\n");
		return NULL;
	}
	else{
		temp = __memoryTableStart__;
		while(temp != NULL){
			if(pointerAddress == temp -> memoryAddress){
				//printf(" Yes it is present in the memory table.\n");
				pointer = realloc(pointerAddress,size);
				__updateLinkedList(temp,pointer,size);
				flag = 1;
				break;
			}
			temp = temp -> __rightlink;
		}
		if(flag == 0){
			//printf(" Was not found in the memory table.\n");
			return NULL;
		}
		else if(flag == 1){
			return pointer;
		}
	}
}
unsigned int sfree(void *pointerAddress)
{
	if(pointerAddress!=NULL){
		__popLinkedList(pointerAddress);
		return 0;
	}
	else{
		//printf(" Pointer is NULL.\n");
		return 0;
	}
}
unsigned int freeAllMemory()
{
	struct __memoryTable *temp;
	if(__memoryTableStart__ == NULL){
		//printf(" No allocated memory.\n");
		return 0;
	}
	else{
		temp = __memoryTableStart__;
		while(temp != NULL){
			__popLinkedList(temp -> memoryAddress);
			temp = temp -> __rightlink;
		}
		return 0;
	}
	return 1;
}
//The following function takes a number and the same number of varibales concatenates them and allocates 
//new memory and returns the address. 
/* 
char *concat(int number,...)
{
	if(number > 0){
		int size = 0,count = 1;
		char *stringParser,*returnString;
		va_list argument;
		va_start(argument, number);
		stringParser 	= va_arg(argument,char*);
		size 			= size + strlen(stringParser);
		returnString 	= (char*)smalloc(size);
		strcpy(returnString,stringParser);
		// This part of the code is not tested for multile cases
		while(count < number){
			stringParser 	= va_arg(argument,char*);
			size 			= size + strlen(stringParser);
			returnString 	= (char*)srealloc(returnString,size);
			strcat(returnString,stringParser);
			count++;
		}
		// End of not tested code
		va_end(argument);
		return returnString;
	}
	else if(number == 0){
		printf(" case 0 still not bulit, sorry.\n");
		return NULL;
	}
	else{
		printf(" The first argument must be a value greater than or equal 1.\n");
		return NULL;
	}
}
*/
#endif
