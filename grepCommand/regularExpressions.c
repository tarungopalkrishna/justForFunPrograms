#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#define bufferSize 2000
void searchPattern(char *pattern,char *buffer)
{
	//printf(" The pattern to be searched is: %s\n", pattern);
	//printf(" The buffer is: %s", buffer);
	for(int i=0;i < strlen(buffer);i++){
		for (int j = 0; j < strlen(pattern); j++){
			printf(" i==%d j==%d %c==%c\n", i,j,*(buffer+i),*(pattern+j));
			if(*(buffer+i)==*(pattern+j)){
				printf(" It has matched. %c == %c YES!\n",*(buffer+i),*(pattern+j));
				i++;
				if(j == strlen(pattern) - 1){
					printf(" This has matched during the search : %s\n", buffer);
				}
			}
			else{
				break;
			}
		}
	}
}
int openFileToSearch(char *pattern,char *fileName)
{
	char *buffer;
	FILE *file;
	file = fopen(fileName,"r");
	if(file == NULL){
		printf(" The file %s was not able to open.\n", fileName);
	}
	else{
		buffer = (char*)malloc(bufferSize);
		while(fgets(buffer,bufferSize,file) != NULL){
			//printf(" The lenght of the characters read is: %ld\n", strlen(buffer));
			if(strlen(buffer) == bufferSize - 1){
				printf(" The prgram will not work for this line.\n");
				printf(" Enter 'y' to continue......");
				scanf("%s",buffer);
				continue;
			}
			searchPattern(pattern,buffer);
		}
	}
	fclose(file);
	free(buffer);
	return 0;
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
		returnString 	= (char*)malloc(size);
		strcpy(returnString,stringParser);
		/* This part of the code is not tested for multile cases*/
		while(count < n){
			stringParser 	= va_arg(argument,char*);
			size 			= size + strlen(stringParser);
			returnString 	= (char*)realloc(returnString,size);
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
int freeMemory(char *one,char *two,char *three,char *four,char *buffer)
{
	printf(" one   : %p\n", one);
	printf(" two   : %p\n", two);
	printf(" three : %p\n", three);
	printf(" four  : %p\n", four);
	printf(" buffer  : %p\n", buffer);
	free(one);
	free(two);
	free(three);
	free(four);
	free(buffer);
	return 0;
}
int main(int argc, char const *argv[])
{
	if(argc != 4){
		invalidMessage();
	}
	else{
		int newBytes;
		char *fileName,*currentDirectory,*pattern,*completePathName;
		char *buffer;
		buffer = (char*)malloc(bufferSize);
		if(buffer == NULL){
			printf(" Memory was not allocated to the buffer.\n");
			return 1;
		}
		strcpy(buffer,argv[1]);
		pattern = newAllocation(1,buffer);
		strcpy(buffer,argv[2]);
		currentDirectory = newAllocation(1,buffer);
		strcpy(buffer,"/");
		strcat(buffer,argv[3]);
		fileName = newAllocation(1,buffer);
		newBytes = strlen(currentDirectory) + strlen(fileName);
		completePathName = newAllocation(2,currentDirectory,fileName);
		if(openFileToSearch(pattern,completePathName) == 0){
			printf(" Pattern NOT found.\n");
		}
		if(freeMemory(fileName,currentDirectory,pattern,completePathName,buffer) != 0){
			printf(" There was an error freeing the allocated memory.\n");
		}
	}
	return 0;
}