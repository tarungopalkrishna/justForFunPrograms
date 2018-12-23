#include <stdio.h>
#include <stdlib.h>
int* readArray(int *number)
{
	int *memoryPointer;
	printf(" Enter the number of elements you want to insert: ");
	scanf("%d",number);
	memoryPointer = (int*)malloc((*number)*sizeof(int));
	if(memoryPointer ==  NULL){
		printf(" Memory was not allocated.\n");
		return NULL;
	}
	printf(" Enter the array(leaving one space between number): ");
	for(int i=0;i<(*number);i++){
		scanf("%d",(memoryPointer+i));
	}
	return memoryPointer;
}
void showArray(int *inputArray,int arraySize)
{
	printf(" The array is:");
	for (int i = 0; i < arraySize; ++i){
		printf(" %d", *(inputArray+i));
	}
	printf("\n");
}
void findLeast(int *inputArray,int arraySize)
{
	int min,numberFromEnd;
	int temp,i,j;
	printf(" Enter which number from the least you want: ");
	scanf("%d",&numberFromEnd);
	for(j=0;j<numberFromEnd;j++){
		min = j;
		for (i = j+1; i < arraySize; i++){
			printf(" Is %d < %d?", (*(inputArray+i)), *(inputArray+min));
			if ((*(inputArray+i)) < *(inputArray+min)){
				printf(" Yes!\n");
				min = i;
			}
			else{
				printf(" No!\n");
			}
		}
		printf(" The least number this pass is: %d\n", *(inputArray+min));
		temp = *(inputArray + min);
		*(inputArray + min) = *(inputArray + j);
		*(inputArray + j) = temp;
		showArray(inputArray,arraySize);
	}
	printf(" The %drd number from the end is: %d\n", numberFromEnd,*(inputArray+numberFromEnd - 1));
}
int main()
{
	int *inputArray,arraySize;
	inputArray = readArray(&arraySize);
	findLeast(inputArray,arraySize);
	return 0;
}