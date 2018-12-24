#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#define bufferSize 2000
int globalLineCounter = 0,globalOccurencesCounter = 0;
int searchPattern(char *pattern,char *buffer)
{
	int flag = 0;
	//printf(" The pattern to be searched is: %s\n", pattern);
	//printf(" The buffer is: %s", buffer);
	for(int i=0;i < strlen(buffer);i++){
		for (int j = 0; j < strlen(pattern); j++){
			//printf(" i==%d j==%d %c==%c\n", i,j,*(buffer+i),*(pattern+j));
			if(*(buffer+i)==*(pattern+j)){
				//printf(" It has matched. %c == %c YES!\n",*(buffer+i),*(pattern+j));
				i++;
				if(j == strlen(pattern) - 1){
					if(flag == 0){
						globalLineCounter++;
						printf(" %d -> %s\n", globalLineCounter,buffer);
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
int openFileToSearch(char *pattern,char *fileName)
{
	int flag = 0;
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
			*(buffer + strlen(buffer) - 1) = '\0'; /* To remove the newline character at the end of the line*/
			if(searchPattern(pattern,buffer) == 1){
				flag = 1;
			}
		}
	}
	fclose(file);
	free(buffer);
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
void freeMemory(char *one,char *two,char *three,char *four,char *buffer)
{
	//printf(" one   : %p\n", one);
	//printf(" two   : %p\n", two);
	//printf(" three : %p\n", three);
	//printf(" four  : %p\n", four);
	//printf(" buffer  : %p\n", buffer);
	free(one);
	free(two);
	free(three);
	free(four);
	free(buffer);
	return;
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
		else{
			printf(" The globalOccurencesCounter value is: %d\n", globalOccurencesCounter);
			printf(" The globalLineCounter value is: %d\n", globalLineCounter);
		}
		freeMemory(fileName,currentDirectory,pattern,completePathName,buffer);
	}
	return 0;
}