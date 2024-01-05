#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int binary[1024];
int binary2[122];
int input;int bits;

int status;
int start=0;int end=3;
int getStringLength(char array[]){
	int size=0;
	int i=0;
	while(array[i]!='\0'){
		i++;
	}
	return i;
}
void reverse(int array[], int start, int end) 
{ 
    while (start < end) 
    { 
        int hold = array[start];  
        array[start] = array[end]; 
        array[end] = hold; 
        start++; 
        end--; 
    }  
}
int getArraySize(int array[]){
	int i=0;
	while(array[i]){
		i++;
	}
	return i;
}
void printArray(int array[],int size){
	int i=0;
	int j=0;
	if ((size)%8!=0)
	{
		size=size/8;
		size=size+1;
	}
	else{
		size=size/8;
	}
	while(i<size){
		for (int i = 0; i < 8; ++i)
		{
			printf("%d,",array[j] );
			j++;
		}
		printf("\n");
		i++;
	}
}
void convert(int input,int i){
	while(input>0){
		//check if remainder is divisible by 2, if it is store it in binary[]
		if (input%2==0)
		{
			binary[i]=0;
		}else{
			binary[i]=1;
		}
		input=input/2;
		i+=1;
	}
}
void combineArrays(int R[],int L[],int size){
	int r=size;
	for (int i = 0; i < size; ++i)
	{
		binary[i]=R[i];
	}
	for (int i = 0; i < size; ++i)
	{
		binary[r]=L[i];
		r++;
	}
}
int convertBinaryToChar(int array[], int size){
	int result=0;
	for (int i = 0; i < size; ++i)
	{
		result=result+(pow(2,i)*array[i]);
	}
	return result;
}
int printText(int array[],int size){
	int bufferArray[8];
	int p=0;
	int r=0;
	int t=0;
	while(p<size){
	for (int i = 0; i <8 ; ++i)
	{
		bufferArray[i]=array[r];
		r++;
	}
	printf("%c",convertBinaryToChar(bufferArray,8));
    //binary[t]=convertBinaryToChar(bufferArray,8);
	p=p+8;
	t++;
	}
}
void ArrayOut(int array[],int size){
	for (int i = 0; i < size; ++i)
	{
		printf("%c", array[i]);
	}
}
void copyArray(int array1[],int array2[],int size){
	for (int i = 0; i < size; ++i)
	{
		array1[i]=array2[i];
	}
}
//result=result+(pow(2,i)*array[i]);
