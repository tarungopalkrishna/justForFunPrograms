#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../safeMemoryAllocation/salloc.h" /* This header file is defined by me for safe memory allocation and deallocation */
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
//Function was coppied from stackoverflow
char *strrev(char *str)
{
      char *p1, *p2;
      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
void charcmpi(char a,char b)
{

}
int optionContains(char a,char *options)
{
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
		char *reversePattern = NULL;
		if(optionContains('r',option+1) == 1){	
			buffer = (char*)smalloc(bufferSize);
			reversePattern = (char*)smalloc(sizeof(strlen(pattern)));
			//printf(" The pattern is: %s\n", pattern);
			strcpy(reversePattern,pattern);
			strrev(reversePattern);
			//printf(" The pattern is: %s and reverse pattern is: %s\n", pattern,reversePattern);
		}
		//printf("->%s<-\n", option);
		while(fgets(buffer,bufferSize,file) != NULL){
			if(strlen(buffer) == bufferSize - 1){
				printf(" The prgram will not work for this line.\n");
				printf(" Enter 'y' to continue......");
				scanf("%s",buffer);
				continue;
	 		}
			*(buffer + strlen(buffer) - 1) = '\0'; /* To remove the newline character at the end of the line*/
			//printf(" The buffer read from the file is: %s\n", buffer);
			if(optionContains('i',option+1) == 1){
				printf(" Contains i.\n");
			}
			if(optionContains('r',option+1) == 1){	//Is working as of 1/1/19
				//printf(" Contains r.\n");
				if(searchPattern(reversePattern,buffer) == 1){
					flag = 1;
				}
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
			//break;	
		}
		//printf(" The buffer is: %s\n", buffer);
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
		while(count < n){
			stringParser 	= va_arg(argument,char*);
			size 			= size + strlen(stringParser);
			returnString 	= (char*)srealloc(returnString,size);
			strcat(returnString,stringParser);
			count++;
		}
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
					pattern = newAllocation(1,buffer);
					strcpy(buffer,argv[2]);
					currentDirectory = newAllocation(1,buffer);
					strcpy(buffer,"/");
					strcat(buffer,argv[3]);
					fileName = newAllocation(1,buffer);
					newBytes = strlen(currentDirectory) + strlen(fileName);
					completePathName = newAllocation(2,currentDirectory,fileName);
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
		freeAllMemeory();
		if(getMemoryStatus() != 0){
			printf(" The memory was not correctly freed. Please fix the bug in the \"salloc.h\" header file.\n");
		}
	}
	return 0;
}