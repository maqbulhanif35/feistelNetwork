#include <stdio.h>
#include <stdlib.h>
#include "decimal2binary.h"
#include "arrayShift.h"
//divide data into left and right blocks

int decimal[1024];


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
			array[i]=1+key;
		}else{array[i]=9+key;}
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
			func(X1,divide,i);
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
			func(X3,divide,i);
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
void decrypt(int R[],int L[],int divide,int key){
	int buffer[divide];

	int X0[divide];
	int X1[divide];
	int X2[divide];
	int X3[divide];
	int X4[divide];
	copyArray(X0,R,divide);
	copyArray(X1,L,divide);
	int pc=0;
	int tc=0;
	int i=key;
	do
	{
		if (tc==0)
		{
			//this part receives X0 and X1
			//it outputs X2 and X3
		    copyArray(buffer,X1,divide);	
			func(X1,divide,i);
	        XOR(X0,X1,divide);

	        copyArray(X2,buffer,divide);
	        copyArray(X3,X0,divide);
	        pc=1;
	        tc=1;
	        //it will have two outputs both of which will be fed to 
	        //the next round
	        //the first output we call it L and the second R
		}else{
			//this part receives X2 and X3
			//it outputs X0 and X1
			copyArray(buffer,X3,divide);
			func(X3,divide,i);
	        XOR2(X2,X3,divide);

	        copyArray(X0,buffer,divide);
	        copyArray(X1,X3,divide);
            tc=0;
	        pc=0;
	        
		}
		--i;
	}while(i>=0);
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
int main()
{
	//input
	int rounds;
	char string[1024];
	printf("Enter Text: ");
    scanf("%[^\n]",&string);
    printf("Enter rounds: ");
    scanf("%d",&rounds);
   
	int size=getStringLength(string);
	int numOfBits=(size*8);
	int divide=numOfBits/2;
	int L[divide];
	int R[divide];
	for (int i = 0; i <size ; ++i)
	{
		decimal[i]=(int)(string[i]);
	}
	int placeholder;
	for (int i = 0; i < size; ++i)
	{
		convert(decimal[i],placeholder);
		placeholder+=8;
	}
	//rounds to perform with this operation?Just 1 round then test it for n rounds
    populateHalves(binary,R,L,divide);
  
    encrypt(R,L,divide,rounds);
    printf("%s\n","Ciphertext-------");
    printText(binary,size*8);
    printf("\n");
  
    decrypt(R,L,divide,rounds);
    printf("Text=");
    printText(binary,size*8);
    





	return 0;
}