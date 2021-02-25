#include <stdio.h>
 
 
 
void quickSort_int(int arr[],int first,int last){
   int i, j, pivot, temp;
  
 
   if(first<last){
      pivot=first;
      i=first;
      j=last;
 
      while(i<j){
         while(arr[i]<=arr[pivot]&&i<last)
            i++;
         while(arr[j]>arr[pivot])
            j--;
         if(i<j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
         }
      }
 
      temp=arr[pivot];
      arr[pivot]=arr[j];
      arr[j]=temp;
      quickSort_int(arr,first,j-1);
      quickSort_int(arr,j+1,last);
 
   }
}