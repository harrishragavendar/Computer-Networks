#include <stdio.h>
#include <math.h>

int hamCalc(int position, int len,int *code)
{
    int count = 0, i, j;
    i = position - 1;
    while(i < len) 
    {
        for(j = i; j < i + position; j++) 
            if (code[j] == 1)
                count++;
        i = i + 2 * position;
    }
    return (count % 2 == 0);
}

void hamCode(int *data,int n,int redundant)
{
    int code[20],i,k=0,j=n-1,recData[20],parity[10],sum=0;
    for(i=0;i<n+redundant;i++)
    {
        if(i == (pow(2,k)-1))
        {
          code[i]=0;
          k++;
        }
        else
        {
          code[i]=data[j];
          j--;
        }
    }
    for(i=0;i<redundant;i++) 
    {
        int position = (int)pow(2, i);
        int value = hamCalc(position,n+redundant,code);
        code[position - 1] = value;
    }
  
    printf("\nHamming Code : ");
    for (i = n+redundant-1; i >=0; i--)
        printf("%d", code[i]);

    printf("\n\n==============\n");
    printf("   Receiver\n");
    printf("==============\n");
    printf("\nEnter the received data\n\n");
    for(i=n+redundant-1;i>=0;i--)
    {
        printf("Enter bit: ");
        scanf("%d",&recData[i]);
    }
    
    for (i = 0; i < redundant; i++) 
    {
        int position = (int)pow(2, i);
        int value = hamCalc(position, n+redundant,recData);
        parity[i]=value;
    }
  
    for(i=0;i<redundant;i++)
        sum+=(parity[i]*pow(2,i));
  
    if(sum!=0)
        printf("\nData is Lost.\n\nError at bit position : %d\n",sum);
    else
    {
        printf("\nNo Data Loss.\n");
        return;
    }

    if(recData[sum-1]==0)
        recData[sum-1]=1;
    else
        recData[sum-1]=0;

    printf("\nCorrected Data : ");
    for(i=n+redundant-1;i>=0;i--)
        printf("%d",recData[i]);
    printf("\n");
}

int main()
{
    int data[20], n, i, redundant;
    printf("=============\n");
    printf(" Transmitter\n");
    printf("=============\n");
    printf("\nEnter the length of the data: ");
    scanf("%d",&n);
    printf("\nEnter the data to be transmitted\n\n");
    for(i=0;i<n;i++)
    {
        printf("Enter bit: ");
        scanf("%d",&data[i]);
    }
    printf("\nData : ");
    for(i=0;i<n;i++)
        printf("%d",data[i]);
    for(i=0;i<n;i++)
    {
        if(pow(2,i)>=n+i+1)
	        break;
    }
    redundant=i;
    printf("\n\nNumber of redundant bits 'r' = %d \n",redundant);
    hamCode(data,n,redundant);
    return 0;
}
