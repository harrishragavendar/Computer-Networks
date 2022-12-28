#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
	char MAC[50],getip[50],ip[50];
	int size=50,i,count=0;
	char *string = (char*)malloc(size);
	int sid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sid==-1)
		perror("\nSocket creation failed");
	else
	{
		printf("\nSocket created");
		struct sockaddr_in addrport;
		addrport.sin_family=AF_INET;
		addrport.sin_port=htons(30000);
		addrport.sin_addr.s_addr=inet_addr("127.16.16.200");
		int status=bind(sid,(struct sockaddr*)&addrport,sizeof(addrport));
		if(status==-1)
		{
			perror("\nBind failed");
			return 0;
		}
		printf("\nBinded successfully");
		struct sockaddr_in client_addr;
		client_addr.sin_family=AF_INET;
		client_addr.sin_port=htons(30000);
		client_addr.sin_addr.s_addr=inet_addr("127.16.16.200");
		socklen_t n =sizeof(client_addr);
		int count=recvfrom(sid,ip,(size_t)sizeof(ip),0,(struct sockaddr*)&client_addr,&n);
		FILE *ptr = fopen("DNS.txt","r");
		if(ptr==NULL)
			perror("\nNo such file found!");
		else
		{
			while(!feof(ptr))
			{
				int nof=getline(&string,&size,ptr);
				for(i=0;string[i]!=':';i++)
				{
					if(string[i]!=':')
					{
						getip[i]=string[i];
						count++;
					}
					else
						break;
				}
				if(strcmp(getip,ip)==0)
				{
					printf("\nMatch found for %s !! Sending it to client\nThe IP is: ",getip);
					int k=0;
					for(i=i+2;string[i]!='\n';i++)
					{
						MAC[k]=string[i];
						k++;
					}
					puts(MAC);
					int snd=sendto(sid,MAC,sizeof(MAC),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
					break;
				}
				else
				{
					memset(getip,'\0',sizeof(getip));
					if(feof(ptr))
					{
						printf("No Such DNS found in server.\n");
						strcpy(MAC,"");
						int snd=sendto(sid,MAC,sizeof(MAC),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
					}
				}
			}
		}
	}
}