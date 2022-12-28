#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
 int n,n1,i,j,count=0,c;
 char *input_data;
 input_data = (char*)malloc(50*sizeof(char));
 printf("Enter the Input Data : ");
 scanf("%s",input_data);
 n=strlen(input_data);
 for(i=0;i<n;i++){
	 if(input_data[i]=='1')
		 count+=1;
 }
 if(count%2==1)
	 input_data[n]='1';
 printf("\nThe Sender data is %s",input_data);
 printf("\nEnter the bit index to change :");
 scanf("%d",&c);
 if(c!=-1){
	 if(input_data[c]=='0')
		 input_data[c]='1';
	 else
		 input_data[c]='0';
 }
 printf("\nThe Receiver data is %s",input_data);
 count=0;
 n=strlen(input_data);
 for(i=0;i<n;i++){
	 if(input_data[i]=='1')
		 count+=1;
 }
 if(count%2==1)
	 printf("\nThere is error in receiver");
 else
	 printf("\nThere is no error in receiver");
 return 1;
}