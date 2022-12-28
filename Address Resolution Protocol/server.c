#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
	struct sockaddr_in cin,client_addr;
	int sid;
	char MAC[50];
	char *string;
	int size=50;
	string=(char*)malloc(size);
	char getip[50];
	int i,count=0;
	sid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sid==-1)
	{
		perror("Socket Error\n");
	}
	else
	{
		printf("\nSocket Created");
		cin.sin_family=AF_INET;
		cin.sin_port=htons(30173);
		cin.sin_addr.s_addr=htonl(INADDR_ANY);
		if(bind(sid,(struct sockaddr*)&cin,sizeof(cin))!=-1);
		{
			printf("\nSocket Binded");
			if(listen(sid,0)!=-1)
			{
				printf("\nIn Listening state....\n");
				socklen_t n=sizeof(client_addr);
				int nsid=accept(sid,(struct sockaddr*)&client_addr,&n);
				if(nsid!=-1)
				{
					char ip[50];
					int count=recv(nsid,ip,sizeof(ip),0);
					FILE *ptr;
					ptr=fopen("MAC.txt","r");
					if(ptr==NULL)
					{
						perror("No such file found!");
					}
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
								printf("Match found !! Sending it to Client");
								int k=0;
								for(i=i+2;string[i]!='\n';i++)
								{
									MAC[k]=string[i];
									k++;
								}
								int snd=send(nsid,MAC,sizeof(MAC),0);
								break;
							}
							else
							{
								if(feof(ptr))
								{
									printf("IP Address not found in server.\n");
									strcpy(MAC,"");
									int snd=send(nsid,MAC,sizeof(MAC),0);
								}
							}
						}
					}
				}
			}
		}
	}
}