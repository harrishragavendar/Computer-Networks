#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	struct sockaddr_in cin;
	int cid;
	char echo[30];
	char ch;
	int len=0;
	int i=0;
	cid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(cid==-1)
	{
		perror("Socket Error\n");
	}
	else
	{
		memset(&cin,0,sizeof(cin));
		cin.sin_family=AF_INET;
		cin.sin_port=htons(30173);
		cin.sin_addr.s_addr=htonl(INADDR_ANY);
		int d=connect(cid,(struct sockaddr*)&cin,sizeof(cin));
		if(d<0)
			perror("Connection Failed");
		else
		{
			char filename[50];
			printf("Connected\n");
			printf("Enter the IP address to search in the server:");
			scanf("%[^\n]s",filename);
			char s1[50];
			int count=send(cid,filename,sizeof(filename),0);
			int c0=recv(cid,s1,sizeof(s1),0);
			if(strcmp(s1,"")!=0)
				printf("\nThe MAC Address is : %s \n",s1);
			else
				printf("IP Address not found in server.\n");
		}
	}
}