#include<stdio.h>
void binaryAdd(int data1[], int data2[], int res[], int n)
{
	int carry;
	do
	{
		carry=0;
		for(int i=n-1;i>=0;i--)
		{
			res[i] = carry + data1[i] + data2[i];
			carry = (int)res[i] / 2;
			res[i] = res[i] % 2;
		}
		if(carry==1)
		{
			for(int i=0;i<n;i++)
			{
				data1[i] = res[i];
				data2[i] = 0;
			}
			data2[n-1] = 1;
		}
	}while(carry == 1);
}
int main()
{
	int n, data1[16], data1_cpy[16], data2[16], data2_cpy[16], sum[16], checksum[16], res[16], tot;
	//transmitter
	printf("Enter the number of bits : ");
	scanf("%d", &n);
	printf("Enter data 1\n");
	for(int i=0;i<n;i++)
	{
		printf("Enter bit %d: ",i+1);
		scanf("%d",&data1[i]);
		data1_cpy[i] = data1[i];
	}
	printf("Enter data 2\n");
	for(int i=0;i<n;i++)
	{
		printf("Enter bit %d: ",i+1);		
		scanf("%d",&data2[i]);
		data2_cpy[i] = data2[i];
	}
	binaryAdd(data1, data2, sum, n);
	printf("Sum : ");
	for(int i=0;i<n;i++)
	{
		printf("%d ",sum[i]);
	}
	printf("\nChecksum : ");
	for(int i=0;i<n;i++)
	{
		checksum[i] = !sum[i];
		printf("%d ",checksum[i]);
	}
	//receiver
	binaryAdd(data1_cpy, data2_cpy, sum, n);
	binaryAdd(sum, checksum, res, n);
	printf("\nSum : ");
	for(int i=0;i<n;i++)
	{
		tot += res[i];
		printf("%d ",res[i]);
	}
	if(tot == n)
	{
		printf("\nNo Data Loss\n");
	}
	else
	{
		printf("\nData Loss\n");
	}
	return 0;
}
