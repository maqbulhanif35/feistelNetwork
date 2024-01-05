#include<stdio.h>  
  


void shiftArray(int a[],int size,int pos){
    int dir=0;
    int temp;
    int N=size;
    while(pos)
    {  
        if(dir)  
        {  
            temp = a[0];  
            for(int i = 0; i < N - 1; i++)  
                a[i] = a[i + 1];  
  
            a[N - 1] = temp;  
        }  
        else  
        {  
            temp = a[N - 1];  
            for(int i = N - 1; i > 0; i--)  
                a[i] = a[i - 1];  
  
            a[0] = temp;  
        }  
  
        pos--;  
    }
}