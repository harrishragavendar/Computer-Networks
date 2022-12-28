#include<stdio.h>
#define size 100
int bitStuff(int message[],int stuffed[],int n)
{
    //Initialize flag array
    int flag[] = {0,1,1,1,1,1,1,0};

    //Initialize stuffed array with -1
    for(int i=0;i<size;i++)
    {
        stuffed[i]=-1;
    }

    //Append starting flag in stuffed message
    for(int i=0;i<8;i++)
    {
        stuffed[i]=flag[i];
    }

    //Status variables
    int status,count;
    int j=7;

    //Stuffing 
    for(int i=0;i<n;i++)
    {
        //If 0 is encountered, set status as 1
        //and search for consecutive 1's by
        //setting counter to 0
        if(message[i]==0)
        {
            status=1;
            count=0;
        }
        //Increment counter if 1 is encountered
        else
        {
            count++;    
        }
        j=j+1;
        stuffed[j]=message[i];

        //If five consecutive 1's are present 
        //append one 0
        if(status==1 && count==5)	
		{
            j=j+1;
			stuffed[j]=0;
			status = 0;
			count = 0;
		}
    }
    //Points to the end of message string
    //after stuffing
    int stuff_length = j;

    //Append flag at the end
    for(int i=0;i<8;i++)
    {
        stuffed[j+i+1] = flag[i];
    }
    return stuff_length;
}
void destuff(int stuffed[],int destuffed[],int stuff_length)
{
    //status variables
    int j=0, count=0, flag=0;

    //Initialize destuffed array
	for(int i=0;i<size;i++)
    {
		destuffed[i]=-1;
    }

    //Destuffing
	for(int i=8;i<=stuff_length;i++)
	{
        //If 0 is encountered, then set flag and set count to 0
		if(stuffed[i] == 0)	
		{
			flag = 1;
			count = 0;
		}
        //If 1 is encountered, increment count
		else
        {
			count++;
        }
        //Skip the 0 that is present
        //after five consecutive 1's
		if(flag == 1 && count==5)
		{
			flag=0;
			count=0;
			destuffed[j]=stuffed[i];
            j++;
			i++;
		}
        //While five 1's are not seen
		else
        {
			destuffed[j]=stuffed[i];
            j++;
        }
	}
}

//Application Program
int main() 
{
    int message[size],stuffed[size],destuffed[size];
    int n,stuff_length;
    printf("Enter the message size: ");
    scanf("%d",&n);
    printf("Enter the message\n");
    for(int i=0;i<n;i++)
    {
        printf("Enter bit %d:",i+1);
        scanf("%d",&message[i]);
    }

    printf("\nMessage\n");
    for(int i=0;i<n;i++)
    {
        printf("%d",message[i]);
    }
    
    stuff_length = bitStuff(message,stuffed,n);

    printf("\nStuffed Message\n");
    for(int i=0;i<size;i++)
    {
        if(stuffed[i]==-1)
        {
            break;
        }
        printf("%d",stuffed[i]);
    }
    
    destuff(stuffed,destuffed,stuff_length);
    
    printf("\nDestuffed Message\n");
    for(int i=0;i<size;i++)
    {
        if(destuffed[i]==-1)
        {
            break;
        }
		printf("%d",destuffed[i]);
    }
    return 0;
}
