#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../safeMemoryAllocation/salloc.h"
#define bufferSize 2000
#define maxArguments 5
/* 
	The case 'r' is a new addition which searches the pattern string in the reverse manner
	I'm sorry if there is already an option with that functionality
*/
/*
	Return values:
	0 -> successful run.
	1 -> Memeory was not allocated properly.
	2 -> File failed to open.
*/
int globalLineCounter = 0,globalOccurencesCounter = 0;
void charcmpi(char a,char b)
{

}
int optionContains(char a,char *options)
{
	//int flag = 0;
	for(int i=0;i<strlen(options);i++){
		if(a == *(options + i)){
			return 1;
		}
	}
	return 0;
}
int searchPattern(char *pattern,char *buffer)
{
	int flag = 0;
	static int lineCounter = 0;
	//printf(" The pattern to be searched is: %s\n", pattern);
	//printf(" The buffer is: %s", buffer);
	lineCounter++;
	for(int i=0;i < strlen(buffer);i++){
		for (int j = 0; j < strlen(pattern); j++){
			//printf(" Line number: %d i==%d j==%d %c==%c\n", lineCounter,i,j,*(buffer+i),*(pattern+j));
			if(*(buffer+i)==*(pattern+j)){
				//printf(" It has matched. %c == %c YES!\n",*(buffer+i),*(pattern+j));
				i++;
				if(j == strlen(pattern) - 1){
					if(flag == 0){
						globalLineCounter++;
						printf(" %d -> %s\n", lineCounter,buffer);
					}
					globalOccurencesCounter++;
					flag = 1;
				}
			}
			else{
				break;
			}
		}
	}
	return flag;
}
int openFileToSearch(char *pattern,char *fileName,char *option)
{
	int flag = 0;
	char *buffer = NULL;
	FILE *file;
	file = fopen(fileName,"r");
	if(file == NULL){
		printf(" The file %s was not able to open.\n", fileName);
		return -1;
	}
	else if(option == NULL){
		buffer = (char*)smalloc(bufferSize);
		while(fgets(buffer,bufferSize,file) != NULL){
			//printf(" The lenght of the characters read is: %ld\n", strlen(buffer));
			if(strlen(buffer) == bufferSize - 1){
				printf(" The prgram will not work for this line.\n");
				printf(" Enter 'y' to continue......");
				scanf("%s",buffer);
				continue;
			}
			*(buffer + strlen(buffer) - 1) = '\0'; /* To remove the newline character at the end of the line*/
			if(searchPattern(pattern,buffer) == 1){
				flag = 1;
			}
		}
	}
	else{
		buffer = (char*)smalloc(bufferSize);
		//printf("->%s<-\n", option);
		while(fgets(buffer,bufferSize,file) != NULL){
			if(strlen(buffer) == bufferSize - 1){
				printf(" The prgram will not work for this line.\n");
				printf(" Enter 'y' to continue......");
				scanf("%s",buffer);
				continue;
	 		}
			*(buffer + strlen(buffer) - 1) = '\0'; /* To remove the newline character at the end of the line*/
			if(optionContains('i',option+1) == 1){
				printf(" Contains i.\n");
			}
			if(optionContains('r',option+1) == 1){
				printf(" Contains r.\n");
			}
			if(optionContains('v',option+1) == 1){
				printf(" Contains v.\n");
			}
			if(optionContains('z',option+1) == 1){
				printf(" Contains 0.\n");
			}
			if(optionContains('z',option+1) == 1){
				printf(" Contains 0.\n");
			}
			if(optionContains('z',option+1) == 1){
				printf(" Contains 0.\n");
			}
			/*
			for(int i=1;i<strlen(option);i++){
				switch(*(option+i)){
					case 'v' :	printf(" Case v is working.\n");
								break;
					case 'i' :	printf(" Case i is working.\n");
								break;
					case 'r' :	printf(" Case r is working.\n");
								break;
					default  :	printf(" Okay\n");
				}
			}
			*/
			break;		
		}
	}
	fclose(file);
	sfree(buffer);
	if(flag == 1){
		return 1;
	}
	else{
		return 0;
	}
}
char *newAllocation(int n,...)
{
	if(n>0){
		int size = 0,count = 1;
		char *stringParser,*returnString;
		va_list argument;
		va_start(argument, n);
		stringParser 	= va_arg(argument,char*);
		size 			= size + strlen(stringParser);
		returnString 	= (char*)smalloc(size);
		strcpy(returnString,stringParser);
		/* This part of the code is not tested for multile cases*/
		//getMemoryStatus();
		while(count < n){
			//printf(" Inside working\n");
			stringParser 	= va_arg(argument,char*);
			//printf(" stringParser:%s\n", stringParser);
			size 			= size + strlen(stringParser);
			//printf(" size:%d\n", size);
			returnString 	= (char*)srealloc(returnString,size);
			strcat(returnString,stringParser);
			count++;
		}
		//getMemoryStatus();
		/* End of not tested code*/
		va_end(argument);
		return returnString;
	}
	else{
		printf(" The first argument must be a value greater than 1.\n");
		return NULL;
	}
}
void invalidMessage()
{
	printf(" Invalid number of arguments passed to sub program.\n");
	return;
}
/*
void freeMemory(char *one,char *two,char *three,char *four,char *buffer,char *five)
{
	printf(" one   : %p\n", one);
	printf(" two   : %p\n", two);
	printf(" three : %p\n", three);
	printf(" four  : %p\n", four);
	printf(" five  : %p\n", five);
	printf(" buffer  : %p\n", buffer);
	if (one != NULL){
		sfree(one);	
	}
	if (two != NULL){
		sfree(two);
	}
	if (three != NULL){
		sfree(three);
	}
	if (four != NULL){
		sfree(four);
	}
	if (five != NULL){
		sfree(five);
	}
	if (buffer != NULL){
		sfree(buffer);
	}
	return;
}
*/
int main(int argc, char const *argv[])
{
	if(argc > maxArguments){
		invalidMessage();
	}
	else{
		int newBytes,switchCase,searchReturnValue;
		char *fileName=NULL,*currentDirectory=NULL,*pattern=NULL,*completePathName=NULL,*option=NULL;
		char *buffer = NULL;
		//switchCase = checkIfHasOption(argc,*argv);
		buffer = (char*)smalloc(bufferSize);
		if(buffer == NULL){
			printf(" Memory was not allocated to the buffer.\n");
			return 1;
		}
		for (int i = 0; i < argc; ++i){
			//printf("%s\n", argv[i]);
			strcpy(buffer,argv[i]);
			//printf("%c\n", *(buffer));
			if(*(buffer) == '-'){
				//printf(" This is an option.\n");
				switchCase = 2;
				break;
			}
			switchCase = 1;
		}
		printf(" switchCase is: %d\n", switchCase);
		switch(switchCase){
			case 1 :strcpy(buffer,argv[1]);
					//printf(" Before pattern\n");
					pattern = newAllocation(1,buffer);
					//printf(" The pointer of pattern is: %p\n", pattern);
					//printf(" After pattern\n");
					strcpy(buffer,argv[2]);
					//printf(" Before currentDirectory\n");
					currentDirectory = newAllocation(1,buffer);
					//printf(" Before currentDirectory_1\n");
					strcpy(buffer,"/");
					//printf(" Before currentDirectory_2\n");
					strcat(buffer,argv[3]);
					//printf(" Before fileName\n");
					fileName = newAllocation(1,buffer);
					newBytes = strlen(currentDirectory) + strlen(fileName);
					//printf(" %s : %s\n", currentDirectory,fileName);
					completePathName = newAllocation(2,currentDirectory,fileName);
					//printf(" completePathName : %s\n", completePathName);
					break;
			case 2 :strcpy(buffer,argv[1]);
					option = newAllocation(1,buffer);
					strcpy(buffer,argv[2]);
					pattern = newAllocation(1,buffer);
					strcpy(buffer,argv[3]);
					currentDirectory = newAllocation(1,buffer);
					strcpy(buffer,"/");
					strcat(buffer,argv[4]);
					fileName = newAllocation(1,buffer);
					newBytes = strlen(currentDirectory) + strlen(fileName);
					completePathName = newAllocation(2,currentDirectory,fileName);
					//printf("%s - %s - %s - %s - %s - %d\n", option,pattern,currentDirectory,fileName,completePathName,newBytes);
					break;
			default:printf(" Something went horribally wrong!.\n");
					exit(0);
		}
		//printf("Send HELP\n");
		searchReturnValue = openFileToSearch(pattern,completePathName,option);
		if(searchReturnValue == 0){
			printf(" Pattern NOT found.\n");
		}
		else if(searchReturnValue != 2){
			printf(" The globalOccurencesCounter value is: %d\n", globalOccurencesCounter);
			printf(" The globalLineCounter value is: %d\n", globalLineCounter);
		}
		else{
			printf(" File \"%s\" not albe to open.\n", completePathName);
		}
		//printf(" Number of elemets left before clean: %d\n", getMemoryStatus());
		freeAllMemeory();
		//printf(" Number of elemets left after clean : %d\n", getMemoryStatus());
		//freeMemory(fileName,currentDirectory,pattern,completePathName,buffer,option);
	}
	return 0;
}