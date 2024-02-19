#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "decimal2binary.h"
#include "arrayShift.h"
char name[264144];
int key;
void readFile(char* name,int array[],int size){
    FILE* file;
    file=fopen(name,"r");
    if (file==NULL)
    {
        printf("Error reading file!");
        exit(1);
    }
    fread(array, sizeof(int), size, file);

    
}
void populateHalves(int binary[],int R[],int L[],int size){
	int r=size;
	for (int i = 0; i < size; ++i)
	{
		R[i]=binary[i];
	}
	for (int i = 0; i < size; ++i)
	{
		L[i]=binary[r];
		r+=1;
	}
}

void XOR(int R[],int L[],int size){
	for (int i = 0; i < size; ++i)
	{
		R[i]=R[i] ^ L[i];
	}
}
void XOR2(int R[],int L[],int size){
	for (int i = 0; i < size; ++i)
	{
		L[i]=R[i] ^ L[i];
	}
}
//this is the function for the algorithm
//we will use bit shifting to shift the bits n number of times to the left
void func(int array[],int size,int key){
	shiftArray(array,size,key);
	for (int i = 0; i < size; ++i)
	{
		if (array[i]==0)
		{
			array[i]=9+key*2-32;
		}else{
			array[i]=19-key*2+14;
		}
	}
}
void encrypt(int R[],int L[],int divide,int key){
	int buffer[divide];
	//These are the ouput arrays for the loops
	int X0[divide];
	int X1[divide];
	int X2[divide];
	int X3[divide];
	int X4[divide];
	copyArray(X0,R,divide);
	copyArray(X1,L,divide);
	int pc=0;
	
	for (int i = 0; i <=key; ++i)
	{
		if (i%2==0)
		{
			//this part receives X0 and X1
			//it outputs X2 and X3
		    copyArray(buffer,X1,divide);	
			func(X1,divide,key);
	        XOR(X0,X1,divide);
	        copyArray(X2,buffer,divide);
	        copyArray(X3,X0,divide);
	        pc=1;
	        //it will have two outputs both of which will be fed to 
	        //the next round
	        //the first output we call it L and the second R
		}else{
			//this part receives X2 and X3
			//it outputs X0 and X1
			copyArray(buffer,X3,divide);
			func(X3,divide,key);
	        XOR2(X2,X3,divide);

	        copyArray(X0,buffer,divide);
	        copyArray(X1,X3,divide);
	        pc=0;
	        
		}
		
	}
	if (pc==1)
	{
		combineArrays(X3,X2,divide);
		copyArray(R,X3,divide);
		copyArray(L,X2,divide);
	}else{
		combineArrays(X1,X0,divide);
		copyArray(R,X1,divide);
		copyArray(L,X0,divide);
	}
}


int getI(char name[],int key){
	printf("Enter file to decrypt(Ensure it is an encrypted file): ");
	scanf("%s",name);
	printf("Enter the key: ");
	scanf("%d",&key);
	return key;
}
int main()
{  
	key=getI(name,key);
	printf("%d",key);
    
    int size=fileSize(name)/4;
    readFile(name,binary,size);
	printArray(binary,size);

    //decryption engine
	int numOfBits=(size);
	int divide=numOfBits/2;
	int L[divide];
	int R[divide];
    int placeholder=0;
    populateHalves(binary,R,L,divide);


	encrypt(R,L,divide,key);
	printText(binary,size);
    
                                      //it is in decimal convert it to binary
                                      //the encrypt function takes a binary input
									  //no the encrypt function does not take a binary input
    return 0;
}
